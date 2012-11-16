CC = gcc
others = functions.c executeUnit.c decodeUnit.c branch.c

all:
	$(CC) Processor.c $(others) -o out.o
