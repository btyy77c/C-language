##Project from NC State Class

![alt tag](https://github.com/btyy77c/C-language/blob/master/mandelbrot/example.jpg)

This program generates a piece of a Mandelbrot graph. 

Don't know what a Mandelbrot graph is?  It's ok, neither did I before I took this class.  Here's a nice youtube video that help explained the graph to me:  
https://www.youtube.com/watch?v=8ma6cV6fw24


Program asks the user for 
   - Minimum real
   - Minimum imaginary
   - Size

The program creates a 2 dimensional array that is used as a graph sheet.  The program then uses a nested loop to calculate every single point on the graph.  After each point is calculated, it will print a char to represent that point on the graph. 

After the calculations are finished, a picture will be generated to show a piece of a Mandelbrot graph. 

##Example files

m_input_1.txt is an example input file. 
m_expected_1.txt is an example of the output file.

##To Run
   1. Download all files in the mandelbrot folder.
   2. Open your terminal and cd into the folder that contains all mandelbrot files
   3. Type into the command line "make" to compile the program.
   4. Add any .txt files you want to the same folder.  This program can run from the terminal so adding a .txt file is not required.

Run with a .txt file
   1 . Enter into your terminal ./mandelbrot < {name of .txt file} >| output.txt
   Example: ./mandelbrot < m_input_1.txt >| output.txt

Run without a .txt file
   1. Enter into the terminal ./mandelbrot
   2. Enter numbers into Minimum real, Minimum imaginary, and size.
