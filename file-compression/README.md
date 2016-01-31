##File compression - Project from NC State Class

This program can compress and uncompress .txt files. 

##File compression

The program uses a file called "words.txt" to create an array of common English words, all English letters and all English punctuations. The program only works with common English language characters included on the "word array".  If, during the compression process, it runs into a character not on the "word array," it will produce an error message and stop.

This "word array" will be used to compare to the .txt file that needs to be compressed. 

After the "word array" is created, it will run through a given .txt file to begin the compression process.  The program will read each word in the given .txt file and index it according to what it matches on the "word array". Once the word is matched, it's "word array" index number is added to a .raw file.  The goal is to end with a list of numbers that matched an index from the "word array" to a word on the given .txt file. 

   For example: 
   - the word array contains ['the', 'of', ' '(space)]
   - the .txt file contains 'of of the of'
   - then the final .raw file would be '1 2 1 2 0 2 1'. 

The "word list" is used to ensure one indexed item requires no more than 7 binary bits of storage.  A byte can hold 8 bits so there is an extra 1 bit of memory not being used when the first number is created.  This is where the compression fun begins. 

Word1 is created and saved as a char which only contains 7 bits.  The next word that is indexed will also only have 7 bits. To save memory, the program will remove the first binary bit from word2 and add it to word1. Now, word1 has 8 bits and word2 has 6 bits. Since word1 has 8 bits, it is full and is added to the .raw file. The program does not add word2 to the .raw file yet since is still has some memory space (2 bits).  

The 3rd word is going to follow the same process.  2 bits of it's binary code are removed and added to word2 (remember, the 2nd word only had 6 bits).  Word2 is now full and is added to the .raw file.  Word3 is held onto since it only has 5 bits has room for more bits. 

This process continues on until the program reaches the end of the .txt file.  In the end, the .raw file would not actually resemble the example I used above.  Instead, you have a messy bunch of squished together binary bits that the computer can't read.

##Uncompress a file
To uncompress a file, the program would open the .raw file and read the file 7 bits at a time. 

The 7 bits would be a number which would then be compared to the index position in the "word array."  Each word that was found would then be added and saved to a new .txt file. 


##To Rum:
   1. Download all files in the file-compression folder. 
   2. Open your terminal and cd into the folder that contains all file-compression files
   3. Type into the command line "make" to compile the program.
   4. Add any .txt files you want to compress to the same folder as pack.c
   5. Enter in terminal: 
      ./pack <name of .txt file you want to compress> <name of .raw file you want to save it to>
      Example: ./pack filename.txt saveas.raw
      
      Your .raw file should appear!  To uncompress the file
   6. Enter in terminal: 
      ./unpack <name of .raw file you want to uncompress> <name of .txt file you want to save it to>
      Example: ./unpack compressedfile.raw newfile.txt
