#include "stdio.h"
#include "stdlib.h"
#include "functions.h"
#include "string.h"
#include "branch.h"
#include "time.h"

struct timespec tim, tim2;

bitStream * fetchUnit(void)
{
	int success = 1, target = 0;
	char reg[4];

	BStemp = BShead;

	tim.tv_sec = 0;
	tim.tv_nsec = SPEED;
	nanosleep(&tim , &tim2);

	if (fetchedAll)
	{
		printf(" -");
		return NULL;
	}

	while ( BStemp->address != registerBlock.PC)
	{
		if (BStemp->next == NULL)
	 	{
	 		success = 0;
	 		printf(" -");
	 		break;
	 	}
		BStemp = BStemp -> next;
	}
	//printf("\n%d - %s\n",BStemp -> address, BStemp -> instruction);
	
	// If instruction is a branch
	if (strncmp("010", BStemp->instruction, 3) == 0)
	{
	    strncpy(reg, BStemp->instruction+4, 4);
	    target = branchPredict(atoi(reg));
	    if (target)
	    {
		success = 0;
		registerBlock.PC = target;
	    }
	}
	
	if (success)
	{
		printf(" F");
		registerBlock.PC++;
	} else {
		printf(" -");
	}

	// check for END
	if (strncmp("01110", BStemp->instruction, 5) == 0)
	{
		fetchedAll = 1;
	}
	return BStemp;
}