#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

int branchPredict(char * reg)
{
    int address;
    
    address = registerBlock.reg[reg];
    return address;
} 