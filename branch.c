#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

int branchPredict(char * Maddress)
{
    char * endptr;
    int address;
    
    address = strtol(Maddress, &endptr, 2);
    return address;
} 