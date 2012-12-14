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
	char reg[5], * endptr;

	BStemp = BShead;

	tim.tv_sec = 0;
	tim.tv_nsec = SPEED;
	nanosleep(&tim , &tim2);

	if (fetchedAll)
	{
		if (registerBlock -> PC < fetchedAllAddress)
		{
			fetchedAll = 0;
		}
		printf(" -");
		printedFs++;
		return NULL;
	}

	while ( BStemp->address != registerBlock -> PC)
	{
		if (BStemp->next == NULL)
	 	{
	 		success = 0;
	 		printf(" -");
			printedFs++;
	 		break;
	 	}
		BStemp = BStemp -> next;
	}
	//printf("\n%d - %s\n",BStemp -> address, BStemp -> instruction);
	
	// If instruction is a branch
	if ((strncmp("010", BStemp->instruction, 3) == 0 || strncmp("110", BStemp->instruction, 3) == 0) && BRANCH)
	{
	    strncpy(reg, BStemp->instruction+5, 5);
	    target = branchPredict(strtol(reg, &endptr, 2));
	    if (target)
	    {	
			success = 0;
			registerBlock -> PC = strtol(reg, &endptr, 2);
	    }
	}
	if (success)
	{
		printf(" F");
		printedFs++;
		registerBlock -> PC++;
		if (registerBlock -> PC < 0)
		{
			registerBlock -> PC = endOfFile;
		}
	} else {
		printf(" -");
		printedFs++;
	}

	// check for END
	if (strncmp("01110", BStemp->instruction, 5) == 0)
	{
		fetchedAll = 1;
		fetchedAllAddress = registerBlock -> PC;
	}
	return BStemp;
}