#include "string.h"
#include "stdio.h"
#include "stdlib.h"

int branchPredict(char * Maddress)
{
    char * endptr;
    int address;
    
    address = strtol(Maddress, &endptr, 2);
    return address;
} 