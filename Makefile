CC = gcc
flags = -Wall
others = functions.c executeUnit.c decodeUnit.c branch.c fetchUnit.c

all:
	$(CC) $(flags) Processor.c $(others) -o out.o
