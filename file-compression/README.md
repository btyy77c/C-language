##File compression - Project from NC State Class

This program can compress and uncompress .txt files. 

##File compression

The program uses a file called "words.txt" to create an array of common English words, all English letters and all English punctuations. The program only works with common English language characters included on the "word array".  If, during the compression process, it runs into a character not on the "word array," it will produce an error message and stop.

This "word array" will be used to compare to the .txt file that needs to be compressed. 

After the "word array" is created, it will run through a given .txt file to begin the compression process.  The program will read each word/letter/punctuation in the given .txt file and index it according to what is matches on the "word array". Once the word is matched, it's "word array" index number is added to another array.  In the end, you would have an array of numbers that matched an index from the "word array" to a word/letter/puncuation found on the given .txt file. 

   For example, if the word array was ['the', 'of', ' '(space)], and the .txt file was 'of of the of', then the final array would be [1(of), 2(space), 1(of), 2(space), 0(the), 2(space), 1(of)]. 

The "word list" is used to ensure one indexed item requires no more than 7 binary bits of storage.  A byte can hold 8 bits so there is an extra 1 bit of memory not being used when the first word is indexed.  This is where the compression fun begins. 

The first word byte is created and added to the array.  The next word that is indexed will also only have 7 bits. To save memory, the program will remove the first binary bit and add it to the previous word. This means the new item is added with only 6 bits of it's byte included.

The 3rd word is going to follow the same process.  2 bits of it's binary code are removed and added to the previous byte in the array (remember, the 2nd word only had 6 bits).  The new word is then added to the array with only 5 bits included. 

This process continues on until the program reaches the end of the .txt file.  In the end, the array would not look like the example I used above.  Instead, you have a messy bunch of squished together binary bits that the computer can't read.  The program then saves this messy array as a .raw file.  

##Uncompress a file
To uncompress a file, the program would open the .raw file and read the file 7 bits at a time. 

The 7 bits would be a number which would then be compared to the index position in the "word array."  Each word/letter/puncuation that was found would then be added and saved to a new .txt file. 


##To Rum:
   1. Download all files in the file-compression folder. 
   2. Open your terminal and cd into the folder that contains all file-compression files
   3. Type into the command line "make" to compile the program.
   4. Add any .txt files you want to compress to the same folder as pack.c
   5. Enter in terminal: 
      ./pack <name of .txt file you want to compress> <name of .raw file you want to save it to>
      Example: ./pack filename.txt saveas.raw
      
      You now have a compressed file!  To uncompress the file
   6. Enter in terminal: 
      ./unpack <name of .raw file you want to uncompress> <name of .txt file you want to save it to>
      Example: ./unpack compressedfile.raw newfile.txt
