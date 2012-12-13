CC = gcc
flags = -Wall
output = out.o
others = functions.c executeUnit.c decodeUnit.c branch.c fetchUnit.c


s=4


all:
	$(CC) $(flags) Processor.c $(others) -o $(output) -DNSCALAR=$(s)
	@echo "call as ./"$(output) "Program.txt DEBUG" 
