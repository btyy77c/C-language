/**
   @file drawing.c
   @author Emily Ring (enring)

   This program accepts an input file and output file
   and draws a picture of the file use pgm
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/** FILES used for reading and writie the picture */
static FILE *read, *write;

//Max number for program drawing
#define MAX_VALUE 255

/**
   Accepts an int and check to make sure the int is equal to 3
   Used for checking to make sure the number of args from the user is correct

   @param check - int to be compared to 3
*/
void checkArgc(int check )
{
   if (check != 3 ){
      //Print error mesaage and exit
      fprintf( stderr, "usage: drawing <script_file> <image_file>\n" );
      exit( 1 );
   }
}

/**
   Accepts an int and checks to make sure the int is between 0 and 255
   Used for checking the radius and color values meet criteria.

   @param check - value that will be checked
*/
void checkDigit( int check )
{
   if ( check < 0 || check > MAX_VALUE ){
      //Print error message
      fprintf( stderr, "Invalid script file\n" );
      exit( 1 );
   }
}

/**
   Function which reads values from a file
   Function, then makes additional calls to draw pictures, after values are read

   @param image - array of chars which will be used to draw a picture
*/
void readFromFile( unsigned char image[ WIDTH ][ HEIGHT ] )
{
   //char which will be checked to see if the program is drawing a line or circle
   static char lineOrCircle;

   //ints which will store circle/line points and use the points to draw the image
   int x1, y1, x2, y2OrRadius, color;

   //Checks to make sure the char captured is not null
   if ( fscanf( read, "%c", &lineOrCircle ) == 1 ) {
      //checks if the char is l and then draws a line
      if ( lineOrCircle == 'l' ){

         //scans in additional values if 'l' is found
         fscanf( read, "%d %d %d %d %d", &x1, &y1, &x2, &y2OrRadius, &color);

         //checks to make sure color is between 0 and 255
         checkDigit( color );

         //calls an addittional method to draw a line, using the values
         drawLine( image, x1, y1, x2, y2OrRadius, color );

         //captures the '\n' line break char
         fscanf( read, "%c", &lineOrCircle );

         //call the method again to check for the next char
         readFromFile( image );

      //checks if the char is 'c' and moves forward with drawing a circle
      } else if ( lineOrCircle == 'c' ){
         //Captures additional values after c
         fscanf( read, "%d %d %d %d", &x1, &y1, &y2OrRadius, &color );

         //Checks to make sure radius and color are between 0 and 255
         checkDigit( y2OrRadius );
         checkDigit( color );

         //calls a function to draw a circle
         drawCircle( image, x1, y1, y2OrRadius, color );

         //reads next char to capture new line '\n' char
         fscanf( read, "%c", &lineOrCircle );

         //Calls function again to read next line
         readFromFile( image );

      //Reads any char that's not 'c' or 'l'
      } else {
         //Prints error and exits
         fprintf( stderr, "Invalid script file\n" );
         exit( 1 );
      }
   }
}

/**
   Main method that begins program.  Accepts two file inputs from user, reads and writes from
   those files, and calls additional methods to draw a picture

   @param argc - number of input calls from user
   @param argv - array of input calls from use

   @return 0 for sucessul exit status
*/
int main( int argc, char *argv[] )
{
   //Char array which is used to store the picture points
   unsigned char image[ WIDTH ][ HEIGHT ];

   //Check args to make sure user entered correct amount
   checkArgc( argc );

   //initialize reading file and check to make sure file can open
   if ( fopen( argv[ 1 ], "r" ) == NULL ){
      //Sends error if file cannot open
      fprintf( stderr, "Can't open file: %s\nusage: drawing <script_file> <image_file>\n",
         argv[1] );
      exit( 1 );

   } else {
      //creates read file
      read = fopen( argv[1], "r" );
   }

   //initialize writing file and check to make sure file can open
   if (fopen( argv[2], "w" ) == NULL ){
      //Sends error if file cannot open
      fprintf( stderr, "Can't open file: %s\nusage: drawing <script_file> <image_file>\n",
         argv[2] );
      exit( 1 );

   } else {
      //creates write file
      write = fopen( argv[2], "w" );
   }

   //Print fist 3 lines of file
   fprintf( write, "%s\n", "P2" );
   fprintf( write, "%d %d\n", MAX_VALUE, MAX_VALUE );
   fprintf( write, "%d\n", MAX_VALUE );

   //Create initial image
   clearImage( image, MAX_VALUE );

   //Read input and adjusts the picture
   readFromFile( image );

   //print final image
   saveImage( image, write );

   //closes files
   fclose( read );
   fclose( write );

   //end and return sucessful status
   return 0;
}
