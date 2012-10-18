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
	char * operand = malloc((sizeof(char)*3));
	char * comment = malloc((sizeof(char)*256));
	struct POP * head = malloc(sizeof(struct POP));
	program = fopen("testProgram.txt","r+");

	//show start of fetch
	printf("Loading program...\n");
	

	//read the first 3 characters, looking for opcode
	fscanf(program, "%3s", operand);
	printf("op: %s\n", operand);

	//check for comment
	while (memchr(operand, '/', 3))
	{
		//printf("found a comment!\n");
		fscanf(program,"%[^/]s", comment);
		//printf("comment: %s\n", comment);
		//read the end of comment deliminator
		fscanf(program, "%1s", comment);
		//take next three characters
		fscanf(program, "%3s", operand);
		//printf("op: %s\n", operand);
	}

	//printf("op: %s\n", operand);
	if(!strcmp(operand, "ADD"))
	{
		printf("found an ADD\n");
	} else if (!strcmp(operand, "SUB"))
	{
		printf("found an SUB\n");
	} else if (!strcmp(operand, "MUL"))
	{
		printf("found an MUL\n");
	} else if (!strcmp(operand, "DIV"))
	{
		printf("found an DIV\n");
	} else if (!strcmp(operand, "CMP"))
	{
		printf("found an CMP\n");
	} else if (!strcmp(operand, "MOV"))
	{
		printf("found an MOV\n");
	} else if (!strcmp(operand, "LDR"))
	{
		printf("found an LDR\n");
	} else if (!strcmp(operand, "STR"))
	{
		printf("found an STR\n");
	} else if (!strcmp(operand, "B"))
	{
		printf("found an B\n");
	} else if (!strcmp(operand, "BLT"))
	{
		printf("found an BLT\n");
	} else if (!strcmp(operand, "BE"))
	{
		printf("found an BE\n");
	} else if (!strcmp(operand, "BGT"))
	{
		printf("found an BGT\n");
	} else if (!strcmp(operand, "JMP"))
	{
		printf("found an JMP\n");
	} else if (!strcmp(operand, "RTN"))
	{
		printf("found an RTN\n");
	} else if (!strcmp(operand, "END"))
	{
		printf("found an END\n");
		fclose(program);
	}

}