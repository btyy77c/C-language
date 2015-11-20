/**
   @file image.h
   @author Emily Ring (enring)

   Header files for image.c to connect to drawing.c
*/

/** WIDTH or array */
extern const int WIDTH;

/** HEIGHT of array */
extern const int HEIGHT;

/**
   Prototye for adding one color the the image

   @param image - char array that holds image points
   @param color - color of image
*/
void clearImage( unsigned char image[ WIDTH ][ HEIGHT ], unsigned char color );

/**
   Prototype for printing the image to a file

   @param image - char array that holds image points
   @param outputFile - file to print out the image
*/
void saveImage( unsigned char image[ WIDTH ][ HEIGHT ], FILE *outputFile );

/**
   Prototype for drawing a line in the image

   @param image - char array that contains the points of the image
   @param x1 - x value at endpoint 1
   @param y1 - y value at endpoint 1
   @param x2 - x value at endpoint 2
   @param y2 - y value at endpoint 2
*/
void drawLine( unsigned char image[ WIDTH ][ HEIGHT ], int x1, int y1,
   int x2, int y2, unsigned char color );

/**
   Prototype for drawing a circle

   @param image - char array that hold the image pixels
   @param cx - center x point of the circle
   @param cy - center y point of the circle
   @param radius - radius of the circle
   @param color - color if the circle
*/
void drawCircle( unsigned char image[ WIDTH ][ HEIGHT ], int cx, int cy, int radius,
   unsigned char color );
