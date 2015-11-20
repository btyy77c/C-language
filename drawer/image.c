/**
   @file drawing.c
   @author Emily Ring (enring)

   Program that adjusts and prints and image using a char array
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/*Width of image and array */
const int WIDTH = 256;

/** Height of image and array */
const int HEIGHT = 256;

/**
  Given an image and a color value in the range 0 to 255, this function will set
  all the pixels of the image to the given color.

  @param char array which hold image values
  @param color - value of color for the image
*/
void clearImage( unsigned char image[ WIDTH ][ HEIGHT ], unsigned char color )
{
  //loop that runs through the program, assigning each value to color
   for ( int i = 0; i < HEIGHT; i++ ){
      for ( int j = 0; j < WIDTH - 1; j++ ){
         image[ j ][ i ] = color;
      }
   }
}

/**
  Given an image and an output file that's been opened for writing, this
  function will write the image to the output file in PGM format.

  @param char array which hold image values
  @param outputFile - file which will be used to write the the picture
*/
void saveImage( unsigned char image[ WIDTH ][ HEIGHT ], FILE *outputFile )
{
  //loop and inner loop that runs through all elements in the char array
   for ( int i = 0; i < HEIGHT - 1; i++ ){
      for ( int j = 0; j < WIDTH - 1; j++ ){
         //if imgae is the first in the line, no extra spaces are added
         if ( j == 0 ){
            //prints image, one char at a time
            fprintf( outputFile, "%3d", image[ j ][ i ] );

         } else {
            //Prints image, one char at a time.  Adds one space between chars
            fprintf( outputFile, " %3d", image[ j ][ i ] );
         }
      }
      //Prints new line at end of each inner loop if x values
      fprintf( outputFile, "%s", "\n" );
   }
}

/**
  Given an image, the endpoints of a line and a drawing color, this function
  will draw the given line into the image as described in the requirements section.

  @param char array which holds the image
  @param x1 - x value at endpoint 1
  @param y1 - y value at endpoint 1
  @param x2 - x value at endpoint 2
  @param y2 - y value at endpoint 2
*/
void drawLine( unsigned char image[ WIDTH ][ HEIGHT ], int x1, int y1,
   int x2, int y2, unsigned char color )
{
   //If x points are farther apart than y points
   if ( abs( x2 - x1 ) > abs( y2 - y1) ){
      //Uses x point distance for amount to increase the line
      int xIncrease = x2 - x1;

      //creates a double to increase the y points
      double yIncrease = ( double ) ( y2 - y1 ) / abs( xIncrease );

      //creates a ddouble point to increase y value
      double y = ( double ) y1;

      //for loop that increase x and y values from x1 to x2
      for ( int i = 0; i <= abs( xIncrease ); i++ ){
         // Rounds y value so it can be used as a point (int)
         y1 = round( y );

         //checks to make sure x and y values are between 0 and 255 for array limits
         if ( x1 >= 0 && x1 <= HEIGHT - 1 && y1 >= 0 && y1 <= HEIGHT - 1 ){
            //sets value from line to color
            image[ x1 ][ y1 ] = color;
         }

         //check to see if increase is positive or negative to know if x is
         //increaseing or decreasing
         if ( xIncrease > 0 ){
            //Increases the x value
            x1++;
         } else {
            //decreases the x value
            x1--;
         }

         //increases the y value
         y += yIncrease;
      }

   //If y distance is larger than x distance
   } else {
      // creates y increase value
      int yIncrease = y2 - y1;

      //creates x increase value
      double xIncrease = ( double ) ( x2 - x1 ) / abs( yIncrease );

      //creates a double to use for increasing the x value
      double x = ( double ) x1;

      //loop that runs through the line start and end points
      for ( int i = 0; i <= abs( yIncrease ); i++ ){
        //Rounds x value into a point to use for the image
        x1 = round( x );

        //Checks to make sire x and y values are within array limits
        if ( x1 >= 0 && x1 <= HEIGHT - 1 && y1 >= 0 && y1 <= HEIGHT - 1 ){
          //sets point at x and y value to color
          image[ x1 ][ y1 ] = color;
        }

        //checks to see if y value is increasing or decreaing
        if ( yIncrease > 0 ){
          //increases y point
          y1++;

        } else {
          //decreases y point
          y1--;
        }

        //increases x value
        x += xIncrease;
      }
   }
}

/**
  Given an image, the center location of a circle, the circle's radius and a drawing
  color, this function will draw a filled circle into the image as described in the
  requirements section.

  @param image - char array that hold the image pixels
  @param cx - center x point of the circle
  @param cy - center y point of the circle
  @param radius - radius of the circle
  @param color - color if the circle
*/
void drawCircle( unsigned char image[ WIDTH ][ HEIGHT ], int cx, int cy, int radius,
   unsigned char color )
{
  //Checks to make sure radius and color are above 0 and less than max length
  if ( radius > 0 && color >= 0 && color <= HEIGHT - 1 ){
    //creates starting and ending points for a square around the radius
    int yStart = cy - radius;
    int yEnd = cy + radius;
    int xStart = cx - radius;
    int xEnd = cx + radius;

    //create a loop that checks every point from square around radius
    for ( int y = yStart; y <= yEnd; y++ ){
      for ( int x = xStart; x <= xEnd; x++ ){
        //distance of radius from selected x and y values
        double distance = sqrt( pow( ( cx - x ), 2 ) + pow( ( cy - y ), 2 ) );

        //checks if the distance from center is larger than radius value
        if ( distance < radius ){
          //If distance is less than radius and x and y values are between 0 and 255,
          //assigns color to specific point in array
          if ( x >= 0 && x <= HEIGHT - 1 && y >= 0 && y <= HEIGHT - 1 ){
            image[ x ][ y ] = color;
          }
        }
      }
    }
  }
}
