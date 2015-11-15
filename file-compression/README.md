File compression - Project from NC State Class

Uses words.txt to identify common words.  Then, codes each word according to the index number from words.txt.  After coding the word, pushes the words’ binary code together to shorten the file and saves the file as .raw  The program has a second file which will uncompress the created .raw file.

The program only works with common English language characters.  It will produce an error message if it can’t identify the character.  


Compile:
   downlaod all files and compile using Makefile

Compress a file:
   Add the file you want to compress to the same folder as pack.c
   Enter in terminal: 
      ./pack <name of .txt file you want to compress> <name of .raw file you want to save it to>

Uncompress a file (uncompressing a file assumes you use .pack to compress the file.  It would not word for other compressed files):
   Add the file you want to uncompress to the same folder as unpack.c
   Enter in terminal: 
      ./unpack <name of .raw you want to uncompress> <name of .txt file you want to save it to>