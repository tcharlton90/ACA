CC = gcc
others = functions.c

all:
	$(CC) Processor.c $(others) -o out.o
