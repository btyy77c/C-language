/**
    @file wordlist.h
    @author Emily Ring
    @author David Sturgill

    Header file for the wordlist.h component, with functions supporting
    reading and creating files
*/

#ifndef _WORDLIST_H_
#define _WORDLIST_H_

#include <stdbool.h>

/** Maximum length of a word in wordlist. */
#define WORD_MAX 20

/** Maximum numbers of words in word array */
#define LIST_MAX 413

/** Number of arguments from user */
#define ARGS 4

/** Word type, used to store elements of the word list,
    with room for a word of up to 20 characters. */
typedef char Word[ WORD_MAX + 1 ];

/** Representation for the whole wordlist.  It contains
    the list of words as a resizable, dynamically allocated
    array, along with supporting fields for resizing. */
typedef struct {
  /** Number of words in the wordlist. */
  int len;

  /** Capacity of the wordlist, so we can know when we need to resize. */
  int capacity;

  /** List of words.  Should be sorted lexicographically once the word list
      has been read in. */
  Word *words;
} WordList;

/*
   Given a character, this function returns true if it's one of the 98 valid
   characters that can appear in a word of the wordlist or in the text file
   being compressed. This function is may be used internally while reading the
   word file, but it's also exposed in the header file so other components can
   use it.
*/
bool validChar( char ch );

/*
  This function is responsable for building the word list. It reads words form word file
  given as fname. After reading all the words from the word file, it adds single-character
  words for each of the 98 valid characters. Finally, it sorts the word list lexicographically
  so that the index of each word is its code.
*/
WordList *readWordList( char const *fname );

/*
  Given a word list, this function returns the best code for representing the sequence of characters
  at the start of the given string. (It returns the index of the longest word in the wordList that
  matches a prefix of the string.)
*/
int bestCode( WordList *wordList, char const *str );

/*
  This function frees the memory for the given wordList, including the dynamically allocated list of
  words inside and the wordList structure itself.
*/
void freeWordList( WordList *wordList );

#endif
