/**
   @file pack.c
   @author Emily Ring
   @author David Sturgill

   Accepts a txt file, reads from the file.  Then, compresses the file,
   using a list of words
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "wordlist.h"
#include "bits.h"

//Initial capacity for text file
#define CAPACITY_MIN 10

//Maximum capacity for text file
#define CAPACITY_MAX 1000000000

/**
   Internally, this function uses a resizable array to read the entire contents
   of the given file into a dynamically allocated string. It will return a pointer
   to a dynamically allocated, null terminated string containing the entire contents
   of the file. The caller is responsible for freeing this string. (this behavior shows
   one reason why we restrict the set of valid characters that can appear in a text file.
   In general, there's nothing to prevent arbitrary byte values, even '\0' from appearing
   in a file. By prohibiting certain characters, including '\0', we can use null-terminated
   strings to hold the contents of the file and words in the word list.)

   @param fp - file that contains the list of words which will be added to the string
   @return final string that lincludes all words from the file
*/
char *readFile( FILE *fp )
{
  //Initial capacity of the file
  int capacity = CAPACITY_MIN;
  //allocate memory for the string
  char *str = malloc( capacity );
  //Number of chars in the file
  int len = 0;
  //Char to be added to the file
  int ch;

  //Loop that pulls all the chars from the file
  while ( ( ch = fgetc( fp ) ) != EOF ){
    //check for valid ch. exit or move forward
    validChar( (char) ch );

    //Checks if string is still within allocated capacity
    if ( len < capacity - 1 ){
      //add char to curret string
      str[len] = (char) ch;

    //if string is too small
    } else if ( capacity < CAPACITY_MAX ){
      //increase string size
      capacity *= CAPACITY_MIN;
      //reallocates string in memory
      str = (char *)realloc( str, capacity * sizeof( char ) );

      //add char to new string
      str[len] = (char) ch;

    //file is too big for capacity
    } else {
      //Error - file is too long
      printf("Error. File is too long" );
      exit( EXIT_FAILURE );
    }
    //increase string length
    len++;
  }

  //add null termination at end of string
  str[ len++ ] = '\0';

  return str;
}

/**
  Start of program.  Accepts input from console with name of files to read and name of
  files to write.  Checks files for reading/writing.  Then, calls on other methods to read
  through the file and compress the file.

  @param argc - number of commands user submitted
  @param argv - string text for each command from user
  @return Sucessfull end of the program
*/
int main( int argc, char *argv[] )
{
  //Initial text file for our list of words
  char *wordFile = "words.txt";

  //Open file from agrs
  FILE *input;
  FILE *output;

  //Check to make sure user submitted correct number of arguments
  if ( argc < ( ARGS - 1 ) || argc > ARGS ){
    fprintf(stderr, "usage: pack <input.txt> <compressed.raw> [word_file.txt]\n" );
    exit( EXIT_FAILURE );
  }

  //4th argument is option.  If entered, use it to read the wordfile
  if ( argc == ARGS ) {
    wordFile = argv[ ARGS - 1 ];
  }

  //Create wordList for our "dictionary"
  WordList *wordList = readWordList( wordFile );

  //Open up reading file.  Produce error message if file cannot open
  if ( ( input = fopen( argv[ 1 ], "r" ) ) == NULL  ){
    fprintf(stderr, "Can't open file: %s\n", argv[ 1 ] );
    fprintf(stderr, "usage: pack <input.txt> <compressed.raw> [word_file.txt]\n" );
    exit( EXIT_FAILURE );
  //Open up writing file.  Produce error message if file cannot open
  } else if ( ( output = fopen( argv[ 2 ], "w" ) ) == NULL  ){
    fprintf(stderr, "Can't open file: %s\n", argv[ 2 ] );
    fprintf(stderr, "usage: pack <input.txt> <compressed.raw> [word_file.txt]\n" );
    exit( EXIT_FAILURE );
  }

//Testing for wordList
#ifdef DEBUG
  // Report the entire contents of the word list, once it's built.
  printf( "---- word list -----\n" );
  for ( int i = 0; i < wordList->len; i++ )
    printf( "%d == %s\n", i, wordList->words[ i ] );
  printf( "--------------------\n" );
#endif

  // Read the contents of the whole file into one big buffer.  This could be more
  // efficient, but it simplifies the rest of the program.
  char *buffer = readFile( input );

  // Write out codes for everything in the buffer.
  int pos = 0;

  //Container for leftover binary code
  PendingBits pending = { 0, 0 };

  //Loop through file, compressing one word at at time
  while ( buffer[ pos ] ) {
    // Get the next code.
    int code = bestCode( wordList, buffer + pos );

//Check to make sure file can be written
#ifdef DEBUG
    printf( "%d <- %s\n", code, wordList->words[ code ] );
#endif

    // Write out file and move ahead by the number of characters we just encoded.
    writeCode( code, &pending, output );
    pos += strlen( wordList->words[ code ] );
  }

  // Write out any remaining bits in the last, partial byte.
  flushBits( &pending, output );

  //free wordList
  freeWordList( wordList );

  //Close file
  fclose( input );
  fclose( output );

  //free array from memory
  free( buffer );

  //exit program
  return EXIT_SUCCESS;
}
