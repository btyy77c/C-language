/**
   @file comments.c
   @author Emily Ring (enring)
   @author David Sturgill (dbsturgi)

   This program reads text from standard input, looking for
   comments. At the end, it will report the total size of the
   input text, how many comments there were and what percent
   of the text was part of a comment.
 */
#include <stdio.h>
#include <stdlib.h>

/** Exit Status: Error processing file */
#define ERR 100

/** Exit status: terminated program due to problem */
#define TERM 101

/** Total count of characters. */
int totalChars = 0;

/** Total count of characters that are part of a comment. */
int commentChars = 0;

/** Total number of comments in the input. */
int commentCount = 0;

/** Current character being read from getchar() */
char current;

/** Previous character read from getchar(). Used to check for comment lines */
char previous;

/**
   Counts all chars in-between two comments '/ *' and '* /'
   Exists the method when it identifies a ‘* /’ comment end
   Exists the program if it reaches the end of the input file before the comment closes
 */
void processComment()
{
   //First count before entering the loop
   commentChars ++;
   totalChars ++;
   previous = current;
   current = getchar();

   //Loop that runs until it identifies the end of a comment '* /'
   do
   {
      //Exists the program if it reaches the end of the input file before the comment closes
      if ( current == EOF ){
        printf( "Unterminated comment\n" );
        exit( TERM );
      }
      
      //Counts total chars and comment chars
      commentChars ++;
      totalChars ++;

      //Reassigns chars to move through the file
      previous = current;
      current = getchar();
   } while ( !(current == '/' && previous == '*') ); //Stops when comment ends '* /'

   //Add 2 to count for first and last slash not counted when entering and leaving method
   commentChars += 2;
}

/**
   Program starting point,
   Counts number of chars in a file
   Runs the processComment method if a comment '/ *' is found
   @return 0 for a successful end or 100 if the file is empty
 */
int main()
{
   //grabs first char in file
   current = getchar();

   //Loop that runs through all characters on the list
   while ( current != EOF ){
      //If the loop sees the beginning of a comment '/ *' then it enters the
      // processComment method to conitue counting comment chars
      if ( previous == '/' && current == '*' ){
         commentCount ++;
         processComment();
      }
      
      //Increases count and reassigns chars
      previous = current;
      current = getchar();
      totalChars ++;
  }

  //Prints error message if file is empty
  if ( totalChars < 1 ){
     printf("Empty input\n");

     return ERR;

  } else { //Prints the number of counted chars and counted comments
     printf( "Input characters: %d\n", totalChars );

     //Calculates what percent of the file is comments and prints values
     double percent = 1.0 * commentChars / totalChars * 100;
      printf( "Comments: %d (%.2f%%)\n", commentCount, percent );

     return 0;
  }
}
