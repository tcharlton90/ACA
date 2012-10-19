#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "functions.h"

FILE * program;

void initFetch(void)
{
	printf("Initiating fetch unit\n");
}

void initDecode(void)
{
	printf("Initiating Decode Unit\n");	
}

void initExecute(void)
{
	printf("Initiating Execute Unit\n");
}

void fetch(void)
{
	printf("Fetching\n");
}

void decode(void)
{
	printf("Decoding\n");
}

void execute(void)
{
	printf("Executing\n");
}

void init(void)
{
	char * operand = malloc((sizeof(char)*32));
	char * comment = malloc((sizeof(char)*256));
	char * opcode;
	int op;
	char twofourbitop[25];
	char twozerobitop[21];
	char fourbitop[5];
	struct POP * head = malloc(sizeof(struct POP));
	struct POP *tail, *temp;

	program = fopen("testProgramMC.txt","r+");
	tail = head;
	temp = malloc(sizeof(struct POP));

	//show start of fetch
	printf("Loading program...\n");
	

	//read the first 32 characters, loading the whole insruction
	while (fscanf(program, "%32s", operand) != 0)
	{
		printf("op: %s\n", operand);

		//check for comment
		//while (memchr(operand, '/', 3))
		//{
			//printf("found a comment!\n");
			//fscanf(program,"%[^/]s", comment);
			//printf("comment: %s\n", comment);
			//read the end of comment deliminator
			//fscanf(program, "%1s", comment);
			//take next three characters
			//fscanf(program, "%3s", operand);
			//printf("op: %s\n", operand);
		//}
	
		//printf("op: %s\n", operand);
		if(!strncmp(operand, "0000", 4))
		{
			printf("found ADD\n");
			temp = tail;
			temp -> opcode = "ADD";

			strncpy(fourbitop,operand+4,4);
			op = atoi(fourbitop);
			temp -> reg1 = op;

			strncpy(fourbitop,operand+8,4);
			op = atoi(fourbitop);
			temp -> op1 = op;

			strncpy(twozerobitop,operand+12,20);
			op = atoi(twozerobitop);
			temp -> op2 = op;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("reg1: %d\n",temp -> reg1);
			//printf("op1: %d\n",temp -> op1);
			//printf("op2: %d\n",temp -> op2);			

		} else if (!strncmp(operand, "0001", 4))
		{
			printf("found SUB\n");
		} else if (!strncmp(operand, "0010", 4))
		{
			printf("found MUL\n");
		} else if (!strncmp(operand, "0011", 4))
		{
			printf("found DIV\n");
		} else if (!strncmp(operand, "0100", 4))
		{
			printf("found CMP\n");
		} else if (!strncmp(operand, "0101", 4))
		{
			printf("found MOV\n");
			temp = tail;
			temp -> opcode = "MOV";

			strncpy(fourbitop,operand+4,4);
			op = atoi(fourbitop);
			temp -> reg1 = op;

			strncpy(twofourbitop,operand+8,24);
			op = atoi(twofourbitop);
			temp -> op1 = op;
			
			temp -> op2 = 0;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("%d\n",temp -> op1);
			//printf("%d\n",temp->reg1);
		} else if (!strncmp(operand, "0110", 4))
		{
			printf("found LDR\n");
		} else if (!strncmp(operand, "0111", 4))
		{
			printf("found STR\n");
		} else if (!strncmp(operand, "1000", 4))
		{
			printf("found B\n");
		} else if (!strncmp(operand, "1001", 4))
		{
			printf("found BLT\n");
		} else if (!strncmp(operand, "1010", 4))
		{
			printf("found BE\n");
		} else if (!strncmp(operand, "1011", 4))
		{
			printf("found BGT\n");
		} else if (!strncmp(operand, "1100", 4))
		{
			printf("found JMP\n");
		} else if (!strncmp(operand, "1101", 4))
		{
			printf("found RTN\n");
		} else if (!strncmp(operand, "1110", 4))
		{
			printf("found END\n");
			fclose(program);
			break;
		}
	}
}
