CC = gcc
flags = -Wall
output = out.o
others = functions.c executeUnit.c decodeUnit.c branch.c fetchUnit.c

all:
	@$(CC) $(flags) Processor.c $(others) -o $(output)
	@echo "call as ./"$(output) "Program.txt DEBUG" 
