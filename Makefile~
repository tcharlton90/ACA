CC = gcc
flags = -Wall
output = out.o
others = functions.c executeUnit.c decodeUnit.c branch.c fetchUnit.c

S=2

all:
	$(CC) $(flags) Processor.c $(others) -o $(output) -DNSCALAR=$(S)
	@echo "call as ./"$(output) "Program.txt DEBUG" 
