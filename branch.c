#include "string.h"
#include "stdio.h"

int branchPredict(char * Maddress)
{
    char* endptr;
    int address;
    
    //printf("%s\n", Maddress);
    address = strtol(Maddress, &endptr, 2);
    //printf("%d\n", address);
    return address;
} 