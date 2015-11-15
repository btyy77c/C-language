/**
  @file wordlist.c
  @author Emily Ring
  @author David Sturgill

  Accepts a file, reading the characters in the file.  Then, creates
  a new array of words from the file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "wordlist.h"

/**
  Checks a single char to see if it falls within the acceptbale lists of chars for the program

  @param ch - char that will be checked against acceptable chars
  @return true is acceptable
*/
bool validChar( char ch ){
  if ( ( ch >= 0x20 && ch <= 0x7E ) ||
       ch == 0x09 ||
       ch == 0x0A ||
       ch == 0x0D ){
    return true;
  } else {
    fprintf(stderr, "Invalid character code: %hhx\n", ch );
    exit( EXIT_FAILURE );
    return false;
  }
}

/**
  Adds a neww word to an existing list of words

  @param wordlList - Struct that contains a list of words
  @param nextWord - New word that will be added to wordList
*/
void addWord( WordList *wordList, char *nextWord )
{
  //Checks if the amount of allocated memory can hold the new word.
  if ( wordList->len < wordList->capacity ){
    //Copy word
    strcpy(wordList->words[ wordList->len ], nextWord );
    
  //Memory need to be realloacted
  } else {
    //increase capacity
    wordList->capacity = wordList->capacity * 2;

    //increase wordList size
    wordList->words = ( Word * )realloc( wordList->words, wordList->capacity * sizeof( Word ) );

    //copy word to new list
    strcpy(wordList->words[ wordList->len ], nextWord );
  }

  //increase word count
  wordList->len += 1;
}

/**
  This function is responsable for building the word list. It reads words form word file
  given as fname. After reading all the words from the word file, it adds single-character
  words for each of the 98 valid characters. Finally, it sorts the word list lexicographically
  so that the index of each word is its code.

  @fname - name of the file that contains all lists from the word
  @return - Lists of words from fname, resorted.
*/
WordList *readWordList( char const *fname ){
  //initialize WordList
  WordList *wordList = (WordList *)malloc( sizeof ( Word ) );
  wordList->capacity = 1;
  wordList->len = 0;
  wordList->words = ( Word * )malloc( sizeof( wordList->capacity * sizeof( Word ) ) );

  //Opens file
  FILE *fp;
  if ( ( fp = fopen( fname, "r" ) ) == NULL  ){
    fprintf(stderr, "Invalid word file\n" );
    exit( EXIT_FAILURE );
  }

  //stores char from file before moving into words
  char nextWord[ WORD_MAX + 1 ];

  //Length of word in the file
  int length;

  //Counts the number of words that have been added to the file
  int count = 0;

  //Loop that runs through file
  while ( fscanf( fp, "%d", &length ) == 1 ){
    //space between number and word
    char ch = fgetc( fp );

    //Produces error if the word length is longer than 20
    if ( length > WORD_MAX ){
      fprintf(stderr, "Invalid word file\n");
      exit( EXIT_FAILURE );
    }

    //Produces error if there is more than 414 words in the list
    if ( count > LIST_MAX ){
      fprintf(stderr, "Invalid word file\n");
      exit( EXIT_FAILURE );
    }

    //Checks the characters in the word before adding the word to the file
    int i = 0;
    //Loop that runs through each char in the word
    while ( i < length ){
      ch = fgetc( fp );

      //Produces error if char is not in acceptable range
      if ( !validChar( ch ) ){
        fprintf(stderr, "Invalid word file\n");
        exit( EXIT_FAILURE );
      }

      //Adds char to new word, which will be added to the file
      nextWord[ i ] = ch;
      i++;
    }

    //Add null terminator to end of word
    nextWord[ length ] = '\0';

    //Words count
    count ++;

    //Adds word to the total list of words
    addWord( wordList, nextWord );
  }

  //Adds additional chars not included in the file list
  //add chars 0x20 - 0x7e
  for ( char i = '!'; i <= '~'; i++ ){
    strcpy( nextWord, &i );
    nextWord[ 1 ] = '\0';
    addWord( wordList, nextWord );
    count ++;
  }

  //add tab
  strcpy( nextWord, "\t");
  addWord( wordList, nextWord );

  //add new line
  strcpy( nextWord, "\n");
  addWord( wordList, nextWord );

  //add r
  strcpy( nextWord, "\r");
  addWord( wordList, nextWord );

  //add space
  strcpy( nextWord, " ");
  addWord( wordList, nextWord );

  //sort list lexographically
  qsort( (int *) wordList->words[0], wordList->len, sizeof ( Word ),
       (int (*)(const void*, const void*) ) strcmp);

  //Close file
  fclose(fp);

  return wordList;
}

/**
  Given a word list, this function returns the best code for representing the sequence of
  characters at the start of the given string. (It returns the index of the longest word
  in the wordList that matches a prefix of the string.)

  @param wordList - Struct that contain the total list of words for the program
  @param str - string that includes a list of word which willbe compared to wordList
  @return index of the wordList word that matches the first word in the str string
*/
int bestCode( WordList *wordList, char const *str ){
  //Checks the length of the string
  int len;
  if ( strlen(str) < WORD_MAX ){
    len = strlen(str);
  } else {
    len = WORD_MAX;
  }

  //variable which will hold bsearch variable
  int *best = NULL;

  //Copies a substring (Maximum of 20 chars at a time) from the total string
  char substr[ len + 1 ];
  memcpy( substr, str, len );
  substr[ len ] = '\0';

  //Loops through substring, check if the substring matches any words in the wordList
  while ( best == NULL ){
    best = (int *) bsearch( substr, wordList->words, wordList->len,
                    sizeof( Word ), (int (*)(const void*, const void*) ) strcmp );

    //Breaks when match is found
    if ( best != NULL ){
      break;
    }

    //Decreases subtring by one char and reruns bsearch check with new substring
    len --;
    memcpy( substr, str, len );
    substr[ len ] = '\0';
  }

  //Storing a number outside of wordlist range
  int final = LIST_MAX * 2;

  //Loop that runs through wordList, looking for the index of the string that matches the
  //substring found from bsearch above
  for ( int i = 0; i < wordList->len; i++ ){
    //Updates final to the index of the word that matches the substring
    if (strcmp(wordList->words[ i ], substr) == 0 ){
      final = i;
    }
  }

  //Returns index position of word that matches the substring
  return final;
}

/**
  This function frees the memory for the given wordList, including the dynamically allocated list of
  words inside and the wordList structure itself.

  @param wordList - Struct that holds the list of words for the program
*/
void freeWordList( WordList *wordList ){
  //frees words in wordList
  free( wordList->words );

  //Frees total struct
  free( wordList );
}
