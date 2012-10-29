CC = gcc
others = functions.c executeUnit.c decodeUnit.c

all:
	$(CC) Processor.c $(others) -o out.o
