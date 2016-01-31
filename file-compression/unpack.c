/**
   @file unpack.c
   @author Emily Ring
   @author David Sturgill

   Accepts a txt file, reads from the file.  Then, uncompresses the file,
   using a list of words
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "wordlist.h"
#include "bits.h"

/**
   Start of program.  Accepts input from console with name of files to read and name of
  files to write.  Checks files for reading/writing.  Then, calls on other methods to read
  through the file and uncompress the file.

  @param argc - number of commands user submitted
  @param argv - string text for each command from user
  @return Sucessfull end of the program
*/
int main( int argc, char *argv[] )
{
  //Default file which contains the "dictionary" of words
  char *wordFile = "words.txt";

  //Open file from agrs
  FILE *input;
  FILE *output;

  //Check to make sure user entered the correct number of arguments
  if ( argc < ( ARGS - 1 ) || argc > ARGS ){
    fprintf(stderr, "usage: unpack <compressed.raw> <output.txt> [word_file.txt]\n" );
    exit( EXIT_FAILURE );
  }

  //Optional input.  If user enters optional file name, program will use it
  if ( argc == ARGS ) {
    wordFile = argv[ ARGS - 1 ];
  }

  //Create wordList for our "dictionary"
  WordList *wordList = readWordList( wordFile );

  //Open file for reading.  Procduces error if file cannot open.
  if ( ( input = fopen( argv[ 1 ], "r" ) ) == NULL  ){
    fprintf(stderr, "Can't open file: %s\n", argv[ 1 ] );
    fprintf(stderr, "usage: unpack <compressed.raw> <output.txt> [word_file.txt]\n" );
    exit( EXIT_FAILURE );
  //Open file for writing.  Produces error if file cannot open.
  } else if ( ( output = fopen( argv[ 2 ], "w" ) ) == NULL  ){
    fprintf(stderr, "Can't open file: %s\n", argv[ 2 ] );
    fprintf(stderr, "usage: unpack <compressed.raw> <output.txt> [word_file.txt]\n" );
    exit( EXIT_FAILURE );
  }

  //Variable to hold leftover binary code
  PendingBits pending = { 0, 0 };

  //Loop that runs through file, writting letters to the writer file
  int number;
  //Continues to call method until method returns -1
  while ( (number = readCode( &pending, input ) ) != -1 ){
    //Prints words unless number is -1 or -2
    if ( number != -1 &&  number != -2 ){
      fprintf(output, "%s", wordList->words[ number ] );
    }
  }

  //free wordList
  freeWordList( wordList );

  //Close file
  fclose( input );
  fclose( output );

  return EXIT_SUCCESS;
}
