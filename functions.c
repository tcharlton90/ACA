#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "functions.h"
#include "decodeUnit.h"
#include "executeUnit.h"
#include "branch.h"

FILE * program;
struct POP * head, *temp, *tail;
struct bitStream *BShead , *BStemp;
int decodedEnd = 0, procClock = 1, instructionsExcecuted = 0;
char * operation[] =  {"ADD","SUB","MUL","DIV","CMP","MOV","LDR","STR","B","BLT","BE","BGT","JMP","RTN","END"};

struct timespec tim, tim2;

//-----------------------------//
//
// Pipeline stage results
struct bitStream * fetchedInstruction[NSCALAR], * nextFetchedInstruction[NSCALAR];
struct POP * decodedInstruction[NSCALAR], * nextDecodedInstruction[NSCALAR];
//
//
//
//
//
//
//
//-----------------------------//

void fetch(void)
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
		 		printf("Cannot fetch instruction.. %d\n", procClock);
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

void decode(void)
{
	int scalar = 0;
	while (scalar < NSCALAR)
	{
		if (fetchedInstruction[scalar])
		{
		    nextDecodedInstruction[scalar] = decodeUnit(fetchedInstruction[scalar], decodedEnd, tail);
		} else {
		    printf("Nothing to Decode.. %d                                 \n", procClock);
		}
		scalar++;
	}
}

void execute(void)
{
	char * name, * endptr;
	int scalar = 0;
	while (scalar < NSCALAR)
	{
		if (decodedInstruction[scalar])
		{
		    name = operation[strtol(decodedInstruction[scalar]->opcode, &endptr, 2)];
		    printf("Executing %s.. ", name);
		    //printf("%d\n",atoi(decodedInstruction[NSCALAR]->opcode));
		    executeUnit(decodedInstruction[scalar]);
		    instructionsExcecuted++;
		} else {
		    printf("Nothing to excecute.. %d\n", procClock);
		}
		scalar++;
	}
}

void cycleClock (void)
{
    int i = 0;
	while (i < NSCALAR)
	{
    	fetchedInstruction[i] = nextFetchedInstruction[i];
    	decodedInstruction[i] = nextDecodedInstruction[i];
    	i++;
    }
    clearPipeline();
	fflush(stdout);
    printf("\nClock cycle number %d\n", procClock++);
}

void clearPipeline(void)
{
	int i = 0;
	while (i < NSCALAR)
	{
    	nextFetchedInstruction[i] = NULL;
    	nextDecodedInstruction[i] = NULL;
    	i++;
    }
}

void init(void)
{
	char * operand = malloc((sizeof(char)*32));
	
	int instNum = 1;
	finished = 0;
	//set registers to 0
	memset(registerBlock.reg,0,NUMREGISTERS);
	registerBlock.PC = 1;
	registerBlock.FLAG_LT = false;
	registerBlock.FLAG_E = false;
	registerBlock.FLAG_GT = false;
	
	//start Memory
	memset(memory, 0,MEMORYSIZE);

	//open program and create instruction buffer
	program = fopen("testProgramMC.txt","r+");
	
	head = malloc(sizeof(struct POP));
	tail = head;

	//show start of fetch
	//printf("Loading program...\n");
	
	struct bitStream *BStail;
	
	BShead = malloc(sizeof(struct bitStream));
	BStail = BShead;

	//read the first 32 characters, loading the whole insruction
	while (fscanf(program, "%32s", operand) != 0)
	{
	 	BStemp = malloc(sizeof(struct bitStream));

		BStemp -> address = instNum++;

		strcpy(BStemp -> instruction, operand);
		printf("%d:%s\n",BStemp->address, BStemp -> instruction);
		BStemp -> next = NULL;

		BStail -> next = BStemp;

		BStail = BStemp;

		if (!strncmp(operand, "1110", 4))
	 	{
	 		printf("...program loaded.\n");
	 		fclose(program);
	 		break;
	 	}
	}
	instNum = 1;
}

void testinit(void)
{
	temp = malloc(sizeof(struct POP));
	temp = head;
	printf("-------------STARTING TEST------------\n");
	while(1)
	{
		printf("-----testing------\n");
		if (temp -> instructionAddress != 0)
		{
			printf("InstAdress: %d\n", temp -> instructionAddress);
		}
		if (temp -> opcode != NULL)
		{
			printf("opcode: %s\n", temp -> opcode);
		}
		if (temp -> reg1 >= 0)
		{
			printf("register 1: %d\n", temp -> reg1);
		}
		if (temp -> op1 >= 0)
		{
			printf("operand 1: %d\n", temp -> op1);
		}
		if (temp -> op2 >= 0)
		{
			printf("operand 2: %d\n", temp -> op2);
		}
		if (temp -> Maddress > 0)
		{
			printf("Memory Adress: %d\n", temp -> Maddress);
		}
		if (temp -> next == NULL)
		{
			break;
		}
		temp = temp -> next;
	}
}

void test (void)
{
	int i;
	int j = 0;
	while (j < NUMREGISTERS)
	{
		i = registerBlock.reg[j];
		printf("%d\n",i);
		j++;
	}
	printf("| LT| E | GT|\n| %d | %d | %d |\n",registerBlock.FLAG_LT,registerBlock.FLAG_E,registerBlock.FLAG_GT);
}

void stats(void)
{
    printf("\nStats:\n");
    printf("Instructions Excecuted:        %d\n", instructionsExcecuted);
    printf("Clock Cycles:                  %d\n", procClock);
    printf("Clock Cycles per Instruction:  %f\n", ((float)procClock/instructionsExcecuted));
    printf("Instructions per Clock Cycle:  %f\n", ((float)instructionsExcecuted/procClock));
}
