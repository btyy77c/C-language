# C-language
Projects in C

Reads from a .txt file.  Creates a graph of 255 X 255 and produces a pixel grayscale image wihtin the graph.  Saves the graph to .pgm

Example input file - input.txt
l x1 y1 x2 y2 100 //l means draw a line from coordinates x1,y1 to x2,y2 with the color hue of 100
c cx cy 5 100 //c means draw a circle around coordinates cx,cy with a radius of 5 in the color hue of 100

input_1.txt is lan example input file

To Run:
  Download all files and compile using Makefile
  $ ./drawing <name of txt file> <name of picture file>
  example: ./drawing input.txt output.pgm
