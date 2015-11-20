/**
   @file mandelbrot.c
   @author Emily Ring (enring)
   @author David Sturgill (dbsturgi)

   This program accepts a complex number and size and creates a
   Mandelbrot graph from the user input
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Dwell cut-off for drawing with ' ' */
#define LEVEL_1 10

/** Dwell cut-off for drawing with '.' */
#define LEVEL_2 20

/** Dwell cut-off for drawing with ':' */
#define LEVEL_3 30

/** Dwell cut-off for drawing with '-' */
#define LEVEL_4 40

/** Dwell cut-off for drawing with '=' */
#define LEVEL_5 50

/** Dwell cut-off for drawing with '+' */
#define LEVEL_6 60

/** Dwell cut-off for drawing with '*' */
#define LEVEL_7 70

/** Dwell cut-off for drawing with '#' */
#define LEVEL_8 80

/** Dwell cut-off for drawing with '%' */
#define LEVEL_9 90

/** Number of spaces included on the x plane of the graph */
#define X_SPACES 69

/** Number of spaces included on the y plane of the graph */
#define Y_SPACES 34

/** Maximum number for magintude to process */
#define MAG_MAX 2.0

/** Invalid exit status */
#define INVAL 100

/**
   Calculates the magnitude of a complex number
   @param a - real part of the number
   @param b - imaginary part of the numer
   @return magintude of the number
 */
double magnitude( double a, double b )
{
   return sqrt( a * a + b * b );
}

/**
   Multiplies 2 complex numbers and returns the Real Value
   @param a - Real number for first value
   @param b - Imaginary number for first value
   @param c - Real number for second value
   @param d - Imaginary number for second value
   @return the Real Value when the two complex numbers are multiplied
 */
double multiplyReal(double a, double b, double c, double d)
{
   return a * c - b * d;
}

/**
   Multiplies 2 complex numbers and returns the Imaginary Value
   @param a - Real number for first value
   @param b - Imaginary number for first value
   @param c - Real number for second value
   @param d - Imaginary number for second value
   @return the Imaginary Value when the two complex numbers are multiplied
 */
double multiplyImag(double a, double b, double c, double d)
{
   return a * d + b * c;
}

/**
   This function takes a complex number, given as real and imaginary parts.
   It computes the dwell of the given number as described in the requirements
   and returns it as an integer. Since values with a dwell of 90 or greater all
   get drawn the same, this function will stop iterating when the dwell reaches
   90 and just return 90 to indicate that the point is in the Mandelbrot set.
   @param cReal Real value for complex number
   @param cImag Imaginary value for complex number
   @return char representing how many iterations it took for the value to pass 2
 */
int testPoint( double cReal, double cImag )
{
   //Z complex number used to calculate the dwell
   double zReal = cReal;
   double zImag = cImag;

   //start dwell at 0
   int dwll = 0;

   //Loop that runs until dwell exceeds 2, or dwell hits 90
   while ( dwll <=  LEVEL_9 ){
      //Z = Z * Z + C
      double newZReal = multiplyReal( zReal, zImag, zReal, zImag ) + cReal;
      double newZImag = multiplyImag( zReal, zImag, zReal, zImag ) + cImag;
      zReal = newZReal;
      zImag = newZImag;

      //Stops the while loop if Z's magintude is greater than 2
      if ( magnitude( zReal, zImag ) > MAG_MAX ){
         break;
      }

      //increases dwell count
      dwll ++;
   }
   
   return dwll;
}

/**
   The requirements define a mapping between ranges of dwell values and the
   symbol used for drawing. This function implements that mapping. It takes the
   dwell as a parameter and returns the corresponding character.
   @param - Number associated with DWELL symbol
   @return dwell character that will be used to draw the picture
 */
char dwellSymbol( int dwell )
{
   if ( dwell < LEVEL_1 ){
      return ' ';
   } else if ( dwell >= LEVEL_1 && dwell < LEVEL_2 ){
      return '.';
   } else if ( dwell >= LEVEL_2 && dwell < LEVEL_3 ){
      return ':';
   } else if ( dwell >= LEVEL_3 && dwell < LEVEL_4 ){
      return '-';
   } else if ( dwell >= LEVEL_4 && dwell < LEVEL_5 ){
      return '=';
   } else if ( dwell >= LEVEL_5 && dwell < LEVEL_6 ){
      return '+';
   } else if ( dwell >= LEVEL_6 && dwell < LEVEL_7 ){
      return '*';
   } else if ( dwell >= LEVEL_7 && dwell < LEVEL_8 ){
      return '#';
   } else if ( dwell >= LEVEL_8 && dwell < LEVEL_9 ){
      return '%';
   } else {
      return '@';
   }
}

/**
   Given copies of the user's input values, this function will draw
   the sampled region of the complex plane, using a 70 by 35 rectangle
   of ASCII characters.
   @param minReal - Starting point and Real value of the complex number
   @param minImag - Imaginary value of the complex number
   @param size - maximum range used to compute Mandelbrot graph
 */
void drawFigure( double minReal, double minImag, double size )
{
   //increment sizes used to increase each complex point along the grid
   double incrReal = size / X_SPACES;
   double incrImag = size / Y_SPACES;

   //loop that runs through the grid.  Caclulates imaginzary number and real number
   for ( int i = Y_SPACES; i >= 0; i-- ){ // imaginary number count
      for ( int j = 0; j <= X_SPACES; j++ ){ //real number count
         //calculates the increase of imaginzary and real number along the plane and puts
         //a char value to represent the number
         putchar( dwellSymbol( testPoint( incrReal * j + minReal, incrImag  * i + minImag ) ) );
      }
      //puts a space between lines of the grid
      putchar( '\n' );
   }
}

/**
   Program starting point, obtains a complex number and size from the user,
   then calls on drawFigure method to create the user's image
   @return 0 if program ends successfully or 100 if input is invalid
 */
int main()
{
   //Real number, Imaginary number and size values for the program
   double minReal, minImag, size;

   //Obtains real number from user. Checks for invalid input
   printf( "Minimum real: " );
   int check = scanf( "%lf", &minReal );
   if ( check == 0 ){
      printf( "Invalid input\n" );
      exit( INVAL );
   }

   //Obtains real number from user. Checks for invalid input
   printf( "Minimum imaginary: " );
   check = scanf( "%lf", &minImag );
   if ( check == 0 ){
      printf( "Invalid input\n" );
      exit( INVAL );
   }

   //Obtains size from user. Checks for invalid input
   printf( "Size: " );
   scanf( "%lf", &size );
   if ( size == 0 ){
      printf( "Invalid input\n" );
      exit( INVAL );
   }

   //calls the method drawFigure to draw the picture
   drawFigure( minReal, minImag, size );

   return 0;
}
