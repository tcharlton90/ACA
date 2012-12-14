#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

int predictions[100];

int branchPredict(int reg)
{
    // int address;
    // address = registerBlock -> reg[reg];
    // //printf("------------%d\n", address);
    // if (address > 0)
    // {
    // 	predictions[address] = 1;
    // 	return address;
    // }
    // predictions[address] = 0;
    // return 0;
    return 1;
} 

int getPred (int address)
{
	if (predictions[address] == 1)
	{
		return 1;
	} else {
		return 0;
	}
}