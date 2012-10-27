#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "functions.h"

void fetch(void)
{
	int success = 1;
	printf("Fetching\n");
	BStemp = BShead;
	while ( BStemp->address != registerBlock.PC)
	{
		//printf("%d\n", registerBlock.PC);
		if (BStemp->next == NULL)
	 	{
	 		success = 0;
	 		printf("Cannot fetch instruction\n");
	 		break;
	 	}
		BStemp = BStemp -> next;
	}
	//printf("%d - %s\n",BStemp -> address, BStemp -> instruction);
	fetchedInstruction = BStemp;
	if (success){registerBlock.PC++;}
	//printf("fetched instruction number %d\n", registerBlock.PC);
}