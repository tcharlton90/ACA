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
	char Maddress[20];

	BStemp = BShead;

	tim.tv_sec = 0;
	tim.tv_nsec = SPEED;
	nanosleep(&tim , &tim2);

	printf("Fetching.. ");

	if (fetchedAll)
	{
		printf("Cannot fetch instruction.. ");
		return NULL;
	}

	while ( BStemp->address != registerBlock.PC)
	{
		if (BStemp->next == NULL)
	 	{
	 		success = 0;
	 		printf("Cannot fetch instruction.. ");
	 		break;
	 	}
		BStemp = BStemp -> next;
	}
	//printf("\n%d - %s\n",BStemp -> address, BStemp -> instruction);
	
	// If instruction is a branch
	if (strncmp("10", BStemp->instruction, 2) == 0)
	{
	    strncpy(Maddress, BStemp->instruction+4, 20);
	    target = branchPredict(Maddress);
	    if (target)
	    {
		success = 0;
		registerBlock.PC = target;
	    }
	}
	
	if (success)
	{
		registerBlock.PC++;
	}

	// check for END
	if (strncmp("1110", BStemp->instruction, 4) == 0)
	{
		fetchedAll = 1;
	}
	return BStemp;
}