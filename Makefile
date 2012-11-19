CC = gcc
flags = -Wall
others = functions.c executeUnit.c decodeUnit.c branch.c

all:
	$(CC) $(flags) Processor.c $(others) -o out.o
