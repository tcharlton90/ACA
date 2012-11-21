#include "stdio.h"
#include "stdlib.h"
#include "functions.h"
#include "string.h"
#include "branch.h"
#include "time.h"

struct timespec tim, tim2;

void fetchUnit(void)
{
	int success = 1, target = 0, scalar = 0;
	char Maddress[20];
	BStemp = BShead;
	printf("                    ");
	fflush(stdout);
	tim.tv_sec = 0;
	tim.tv_nsec = SPEED;
	nanosleep(&tim , &tim2);
	printf("\r");
	while (scalar < NSCALAR)
	{
		printf("Fetching.. ");
		while ( BStemp->address != registerBlock.PC)
		{
			//printf("%d\n", registerBlock.PC);
			if (BStemp->next == NULL)
		 	{
		 		success = 0;
		 		printf("Cannot fetch instruction.. \n");
		 		break;
		 	}
			BStemp = BStemp -> next;
		}
		//printf("\n%d - %s\n",BStemp -> address, BStemp -> instruction);
		
		// If instruction is a branch
		if (strncmp("10", BStemp->instruction, 2) == 0)
		{
		    //printf("BRANCHING\n");
		    //printf("%s\n", BStemp->instruction+4);
		    strncpy(Maddress, BStemp->instruction+4, 20);
		    target = branchPredict(Maddress);
		    if (target)
		    {
			success = 0;
			registerBlock.PC = target;
		    }
		}
		
		nextFetchedInstruction[scalar] = BStemp;
		if (success)
		{
			//printf("fetched instruction number %d\n", registerBlock.PC);
			registerBlock.PC++;
		}

		// check for END
		if (strncmp("1110", BStemp->instruction, 4) == 0)
		{
			break;
		}
		
		scalar++;
	}
}