compc = gcc
comp+ = g++
flags = -Wall -g
output = out.o
others = functions.c executeUnit.c decodeUnit.c branch.c fetchUnit.c


s=4


c:
	@$(compc) $(flags) Processor.c $(others) -o $(output) -DNSCALAR=$(s)
	@echo "call as ./"$(output) "Program.txt BRANCH DEBUG VERBOSE"

comp: 
	@$(comp+) compiler.cpp -o comp.o
	@echo "call as ./"comp.o "livermore.txt"

clean:
	@rm out.o
	@rm comp.o