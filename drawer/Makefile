#variables
CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lm

# Drawing depends on these 2 objects.
drawing: drawing.o image.o

# Our objects depend on their own source files, and the headers
drawing.o: drawing.c image.h 

image.o: image.c image.h

# cleaing the files
clean:
	rm -f $@
	echo Clean done
