![alt tag](https://github.com/btyy77c/C-language/blob/master/drawer/output.jpg)

##Project from NC State Class

Creates a graph of 255 X 255 and opens a requested .txt file.  The .txt file will have a list of line and circle commands the program will use to draw lines and circles on the graph. After all lines and circles have been added, the program will save the graph as a .pgm file.

##Example drawing commands that would be included in the .txt file: 
   l x1 y1 x2 y2 100 //means draw a line (l) from coordinates x1,y1 to coordinates x2,y2 with the color hue of 100

   c cx cy 5 100 //means draw a circle (c) around the point cx,cy with a radius of 5 in the color hue of 100
   
   An example .txt file is also included and is labeled "input.txt"

##To Run:
   1. Download all files in the program
   2. open your terminal and cd into the folder that contains all drawer files
   3. enter into the command line ./drawing <name of input file.txt> <name of output file .pgm>   
      example run: ./drawing input.txt output.pgm
