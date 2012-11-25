#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "functions.h"
#include "fetchUnit.h"
#include "decodeUnit.h"
#include "executeUnit.h"

FILE * program;
struct POP * head, *temp, *tail;
int decodedEnd = 0, procClock = 1, instructionsExcecuted = 0;
char * operation[] =  {"ADD","SUB","MUL","DIV","CMP","MOV","LDR","STR","B","BLT","BE","BGT","JMP","RTN","END"};


void fetch(void)
{
	int scalar = 0;

	printf("                    ");
	fflush(stdout);
	printf("\r");
	while (scalar < NSCALAR)
	{
		nextFetchedInstruction[scalar] = fetchUnit();
		if(nextFetchedInstruction[scalar] == NULL)
		{
			break;
		}
		scalar++;
	}
	//testFetch();
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
		    printf("Nothing to Decode.. ");
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
		    printf("Nothing to excecute.. ");
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
    printf("\nClock cycle number %d\n\n", procClock++);
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

void clearInstructionIssue(void)
{
	int scalar = 0;

	while(scalar < NSCALAR)
	{
		decodedInstruction[scalar] = NULL;
		scalar++;
	}
}

void init(void)
{
	char * operand = malloc((sizeof(char)*32));
	int instNum = 1;	
	struct bitStream *BStail;

	finished = 0;
	fetchedAll = 0;

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
	

	// sort out some structs to hold the program (linked lists)
	head = malloc(sizeof(struct POP));
	tail = head;
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

void testFetch(void)
{
	int i = 0;
	while (i < NSCALAR)
	{
		if(nextFetchedInstruction[i])
		{
			printf("%d, %s\n", nextFetchedInstruction[i] -> address, nextFetchedInstruction[i] -> instruction);
		}
		i++;
	}
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
	int i, j = 0;
	
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
