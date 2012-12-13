#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "functions.h"
#include "fetchUnit.h"
#include "decodeUnit.h"
#include "executeUnit.h"

FILE * program;
struct POP * head, *temp, *tail;
int decodedEnd = 0, procClock = 1, instructionsExcecuted = 0;
char * operation[] =  {"ADD","SUB","MUL","DIV","CMP","MOV","LDR","STR","B","BLT","BE","BGT","JMP","RTN","END","NOP"};


void fetch(void)
{
	int scalar = 0;
	printedFs = 0;
	printf("                    ");
	fflush(stdout);
	if (VERBOSE)
	{
		printf("\n");
	} else {
		printf("\r");
	}
	//printf("F: ");
	while (scalar < NSCALAR)
	{
		nextFetchedInstruction[scalar] = fetchUnit();
		if(nextFetchedInstruction[scalar] == NULL)
		{
			break;
		}
		scalar++;
	}
	while (printedFs < NSCALAR)
	{
	 	printf(" -");
	 	printedFs++;
	}
	(DEBUG) ? testFetch() : NULL;
}


void decode(void)
{
	int scalar = 0;
	struct POP * tmp;
	//printf("D: ");
	while (scalar < NSCALAR)
	{
		if (fetchedInstruction[scalar])
		{
			tmp = decodeUnit(fetchedInstruction[scalar], decodedEnd, tail);
			setIssueBuffer(tmp, dependancies);
		} else {
			printf(" -");
		}
		scalar++;
	}
	(DEBUG) ? testDecode() : NULL;
	issue();
}

void issue (void)
{
	//take instructions from the issue buffer and issue them as long as there are no dependancies.
	struct POP * forExecution;
	struct issueBuffer * tmp, *prev;
	int scalar = 0;

	tmp = issueBufferHead;
	// keep the previous pointer so we can join up the chain when rremoving an instruction
	prev = issueBufferHead;
	while (tmp != NULL)
	{
		//check for dependancies or NOP's
		if ((strcmp(tmp -> instructionForIssue -> opcode, "01111") == 0) || (tmp -> dependancies > 0))
		{
			prev = tmp;
			tmp = tmp -> next;
		} else {
			// no dependancies - issue instruction
			nextIssuedInstruction[scalar] = tmp -> instructionForIssue;
			scalar++;

			// remove instruction from buffer
			tmp = tmp -> next;
			prev -> next = tmp; 
		}
	}
	//printf("%d", scalar);
	while (scalar < NSCALAR)
	{
		// fill the execute bufffer with NOPS
		forExecution = malloc(sizeof(struct POP));
		forExecution -> opcode = "01111";
		nextIssuedInstruction[scalar] = forExecution;
		scalar++;
	}

	(DEBUG) ? testIssue() : NULL;
}

void dereference(void)
{
	// cycle through the issus buffer
	// if an instruction is ready for issue ( no dependancies)
	// then fulfill its arguments
	struct issueBuffer * tmp;
	char * tmpOpcode = malloc(sizeof(char)*5);
	tmp = issueBufferHead;
	while(tmp != NULL)
	{
		if ((tmp -> dependancies == 0) && (tmp -> decoded == 0))
		{
			tmpOpcode = tmp -> instructionForIssue -> opcode;
			if (strncmp(tmpOpcode, "000", 3) == 0) // aritmetics
			{
				tmp -> instructionForIssue -> op1 = registerBlock -> reg [tmp -> instructionForIssue -> op1];
				tmp -> instructionForIssue -> op2 = registerBlock -> reg [tmp -> instructionForIssue -> op2];
			}
			if (strncmp(tmpOpcode, "00100", 5) == 0) // cmp
			{
				tmp -> instructionForIssue -> reg1 = registerBlock -> reg [tmp -> instructionForIssue -> reg1];
				tmp -> instructionForIssue -> op1 = registerBlock -> reg [tmp -> instructionForIssue -> op1];			
			}
			if (strncmp(tmpOpcode, "00110", 5) == 0) // load store
			{
				tmp -> instructionForIssue -> op1 = registerBlock -> reg [tmp -> instructionForIssue -> op1];
			}
			if (strncmp(tmpOpcode, "010", 3) == 0) // branch
			{
				tmp -> instructionForIssue -> reg1 = registerBlock -> reg [tmp -> instructionForIssue -> reg1];
			}
			tmp-> decoded = 1;
		}
		tmp = tmp -> next;
	}

}

void execute(void)
{
	char * name, * endptr;
	int scalar = 0, i;
	while (scalar < NSCALAR)
	{
		if (issuedInstruction[scalar])
		{
			i = strtol(issuedInstruction[scalar]->opcode, &endptr, 2);
		    name = operation[i];
		    if(!finished)
			{
		    	printf(" %s", name);
		    }
		    executeUnit(issuedInstruction[scalar]);
		    instructionsExcecuted++;
		} else {
			if(!finished)
			{
		    	printf(" NOP");
		    }
		    NOPS++;
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
    	issuedInstruction[i] = nextIssuedInstruction[i];
    	i++;
    }
    registerBlock = nextRegisterBlock;
    copyIssueBuffer();
    checkDependancies();
    clearPipeline();
	fflush(stdout);
	if(!finished)
	{
    	printf(" Cycle:  %d", procClock++);
	}
}

void checkDependancies(void)
{
	int a, b, c, i, dependanciesFound; // a, b and c are for registers
	struct issueBuffer * tmp;

	tmp = issueBufferHead;
	for (i = 0; i < NUMREGISTERS; i++)
	{
		if (scoreBoard[i] > 0)
		{
			scoreBoard[i]--;
		}
	}
	if (scoreBFlags > 0)
	{
		scoreBFlags--;
	}
	while (tmp != NULL)
	{
		if (strcmp(tmp -> instructionForIssue -> opcode, "01111") != 0)
		{
			//instrution is not NOP
			a = tmp -> instructionForIssue -> reg1;
			b = tmp -> instructionForIssue -> op1;
			c = tmp -> instructionForIssue -> op2;

			if (strcmp(tmp-> instructionForIssue -> opcode, "00101") == 0)
			{
				//MOV is a special case
				b = -1;
			}

			// check for dependancies
			dependanciesFound = 0;
			
			// set dependancies flag
			if (scoreBoard[a] || scoreBoard[b] || scoreBoard[c])
			{
				tmp -> dependancies = 1;
				dependanciesFound = 1;
			}
			// if there is a compare, stall all branches after it. (REMAIN IN ORDER)
			if (strcmp(tmp-> instructionForIssue -> opcode, "00100") == 0)
			{
				if (scoreBFlags == 0)
				{
					scoreBFlags = 2;
				}
			}
			if (strncmp(tmp -> instructionForIssue -> opcode, "010", 3) == 0)
			{
				//stall  a branch
				if (scoreBFlags > 0)
				{
					tmp -> dependancies = 1;
					dependanciesFound = 1;
				}
			}

			// END is dependant on nothing else being in the buffer
			if (strcmp(tmp -> instructionForIssue -> opcode, "01110") == 0)
			{
				if (strcmp(issueBufferHead->next->instructionForIssue->opcode, "01110") != 0)
				{
					tmp -> dependancies = 1;
					dependanciesFound = 1;					
				}
			}
			if (dependanciesFound == 0)
			{
				tmp -> dependancies = 0;
			}
			
			//add dependancies to
			if (a >= 0 && scoreBoard[a] == 0)
			{
				scoreBoard[a] = 2;
			}
			if (b >= 0 && scoreBoard[b] == 0)
			{
				scoreBoard[b] = 2;
			}
			if (c >= 0 && scoreBoard[c] == 0)
			{
				scoreBoard[c] = 2;
			}
		}
		tmp = tmp -> next;
	}

	dereference();
	// j = 0;
	// printf("\n");
	// while (j < NUMREGISTERS)
	// {
	// 	i = scoreBoard[j];
	// 	printf("%d\n",i);
	// 	j++;
	// }
}

void copyIssueBuffer(void)
{
	struct issueBuffer * tmp;

	tmp = issueBufferHead;

	while (tmp->next != NULL)
	{
		tmp = tmp -> next;
	}
	tmp -> next = nextIssueBufferHead -> next;
	nextIssueBufferHead -> next = NULL;
}

void clearPipeline(void)
{
	int i = 0;

	while (i < NSCALAR)
	{
    	nextFetchedInstruction[i] = NULL;
    	nextDecodedInstruction[i] = NULL;
    	nextIssuedInstruction[i] = NULL;
    	i++;
    }
}

void clearInstructionIssue(void)
{
	int scalar = 0;

	while(scalar < NSCALAR)
	{
		issuedInstruction[scalar] = NULL;
		scalar++;
	}
	// THIS IS A HACK
	issueBufferHead -> next = NULL;
}

void setIssueBuffer(POP * toAdd, int dep)
{
	struct issueBuffer * buf, * tmp;

	tmp = malloc(sizeof(struct issueBuffer));
	tmp -> instructionForIssue = toAdd;
	tmp -> dependancies = dep;
	tmp -> decoded = 0;
	tmp -> next = NULL;

	buf = nextIssueBufferHead;

	while (buf->next != NULL)
	{
		buf = buf -> next;
	}
	buf -> next = tmp;
}

void init( char * argv[] )
{
	char * operand = malloc(sizeof(char)*32);
	int instNum = 1, verb, deb;	
	struct bitStream *BStail;
	//struct issueBuffer *tmp;

	finished = 0;
	fetchedAll = 0;
	dependancies = 0;
	branchesTaken = 0;
	predictedCorrect = 0;
	predictedIncorrect = 0;
	NOPS = 0;

	//start the issueBuffer
	//tmp = malloc(sizeof(struct issueBuffer));
	issueBufferHead = malloc(sizeof(struct issueBuffer));
	issueBufferHead -> instructionForIssue = malloc(sizeof(struct POP));
	issueBufferHead -> instructionForIssue -> opcode = "01111";
	issueBufferHead -> dependancies = 0;
	issueBufferHead -> next = NULL;

	nextIssueBufferHead = malloc(sizeof(struct issueBuffer));
	nextIssueBufferHead -> instructionForIssue = malloc(sizeof(struct POP));
	nextIssueBufferHead -> instructionForIssue -> opcode = "01111";
	nextIssueBufferHead -> dependancies = 0;
	nextIssueBufferHead -> next = NULL;
	//printf("%s, %s\n", issueBufferHead -> instructionForIssue -> opcode, issueBufferHead -> next);

	scoreBFlags = 0;
	memset(scoreBoard, 0, sizeof(scoreBoard));

	deb = atoi(argv[2]);
	verb = atoi(argv[2]);
	if (deb == 1)
	{
		DEBUG = 1;
	} else if (deb == 0)
	{
		DEBUG = 0;
	} else {
		printf("No Debug variable\n");
		exit(EXIT_FAILURE);
	}
	if (verb == 1)
	{
		VERBOSE = 1;
		printf("VERBOSE turned on\n");
	} else if (verb == 0)
	{
		VERBOSE = 0;
	} else {
		printf("No verbose variable\n");
		exit(EXIT_FAILURE);
	}

	//start registers
	registerBlock = malloc(sizeof(struct registers));
	nextRegisterBlock = registerBlock;
	//set registers to 0
	memset(registerBlock -> reg,0,NUMREGISTERS);
	registerBlock -> PC = 1;
	registerBlock -> FLAG_LT = false;
	registerBlock -> FLAG_E = false;
	registerBlock -> FLAG_GT = false;
	
	//start Memory
	memset(memory, 0,MEMORYSIZE);

	//open program and create instruction buffer
	//printf("%s\n", argv[1]);
	program = fopen(argv[1],"r+");
	if (!program)
	{
		printf("%s is not a recognised program!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

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
                if (VERBOSE)
                {
                    printf("%d:%s\n",BStemp->address, BStemp -> instruction);
                }
                BStemp -> next = NULL;

		BStail -> next = BStemp;

		BStail = BStemp;

		if (!strncmp(operand, "01110", 5))
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
	printf("\n");
	printf("PC: %d\n", registerBlock-> PC);
	while (i < NSCALAR)
	{
		if(nextFetchedInstruction[i])
		{
			printf("%d, %s\n", nextFetchedInstruction[i] -> address, nextFetchedInstruction[i] -> instruction);
		}
		i++;
	}
}

void testDecode(void)
{
	int i = 0;
	printf("\n");
	while (i < NSCALAR)
	{
		if(nextDecodedInstruction[i] != NULL);
		{
			//printf("%s\n", nextDecodedInstruction[i] -> opcode);
			fflush(stdout);
		}
		i++;
	}
}

void testIssue (void)
{
	struct issueBuffer * tmp;
	tmp = issueBufferHead;
	printf("\n Testing Issue Buffer\n");

	while (tmp -> next != NULL)
	{
		printf("%d, %s, %d\n", tmp -> instructionForIssue -> instructionAddress, tmp -> instructionForIssue -> opcode, tmp -> dependancies);
		fflush(stdout);
		tmp = tmp -> next;
	}
	printf("%d, %s, %d\n", tmp -> instructionForIssue -> instructionAddress, tmp -> instructionForIssue -> opcode, tmp -> dependancies);
	 fflush(stdout);

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
	printf("\n");
	while (j < NUMREGISTERS)
	{
		i = registerBlock -> reg[j];
		printf("%d\n",i);
		j++;
	}
	printf("| LT| E | GT| PC|\n| %d | %d | %d | %d |\n",registerBlock -> FLAG_LT,registerBlock -> FLAG_E,registerBlock -> FLAG_GT,registerBlock -> PC);
}

void stats(void)
{
    printf("\nStats:\n");
    printf("Instructions Excecuted:        %d\n", instructionsExcecuted);
    printf("Clock Cycles:                  %d\n", procClock);
    printf("Clock Cycles per Instruction:  %f\n", ((float)procClock/instructionsExcecuted));
    printf("Instructions per Clock Cycle:  %f\n", ((float)instructionsExcecuted/procClock));
    printf("NOP's:                         %d\n", NOPS);
}
