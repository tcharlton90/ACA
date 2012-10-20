#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "functions.h"

FILE * program;
struct POP * head, *temp;
struct registers registerBlock;

char * operation[] =  {"ADD","SUB","MUL","DIV","CMP","MOV","LDR","STR","B","BLT","BE","BGT","JMP","RTN","END"};

//-----------------------------//
//
// Pipeline stage results
struct POP * fetchedInstruction;
//struct POP * decodedI
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
	int success = 1;
	printf("Fetching\n");
	temp = head;
	while (temp->instructionAddress != registerBlock.PC)
	{
		if (temp->next == NULL)
		{
			success = 0;
			printf("Cannot fetch instruction\n");
			break;
		}
		temp = temp->next;
	}
	fetchedInstruction = temp;
	registerBlock.PC++;
	//printf("fetched instruction number %d\n", registerBlock.PC);
}

void decode(void)
{
	char* endptr;
	char * name;
	printf("Decoding\n");
	name = operation[strtol(fetchedInstruction->opcode, &endptr, 2)];
	//printf("%s\n", name);
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
	int op, instNum = 1;
	char twofourbitop[25];
	char twozerobitop[21];
	char fourbitop[5];
	struct POP *tail;
	char* endptr;

	//set registers to 0
	memset(registerBlock.reg,0,NUMREGISTERS);
	registerBlock.PC = 1;
	//open program and create instruction buffer
	program = fopen("testProgramMC.txt","r+");
	head = malloc(sizeof(struct POP));
	tail = head;
	

	//show start of fetch
	printf("Loading program...\n");
	

	//read the first 32 characters, loading the whole insruction
	while (fscanf(program, "%32s", operand) != 0)
	{
		//printf("op: %s\n", operand);

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
			//printf("found ADD\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "0000";

			temp -> instructionAddress = instNum++; 

			strncpy(fourbitop,operand+4,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> reg1 = op;

			strncpy(fourbitop,operand+8,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> op1 = op;

			strncpy(twozerobitop,operand+12,20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> op2 = op;

			temp -> Maddress = 0;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("instNum: %d\n", temp -> instructionAddress);
			//printf("reg1: %d\n",temp -> reg1);
			//printf("op1: %d\n",temp -> op1);
			//printf("op2: %d\n",temp -> op2);			

		} else if (!strncmp(operand, "0001", 4))
		{
			//printf("found SUB\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "0001";

			temp -> instructionAddress = instNum++;

			strncpy(fourbitop,operand+4,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> reg1 = op;

			strncpy(fourbitop,operand+8,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> op1 = op;

			strncpy(twozerobitop,operand+12,20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> op2 = op;

			temp -> Maddress = 0;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("instNum: %d\n", temp -> instructionAddress);
			//printf("reg1: %d\n",temp -> reg1);
			//printf("op1: %d\n",temp -> op1);
			//printf("op2: %d\n",temp -> op2);			

		} else if (!strncmp(operand, "0010", 4))
		{
			//printf("found MUL\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "0010";

			temp -> instructionAddress = instNum++;
			
			strncpy(fourbitop,operand+4,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> reg1 = op;

			strncpy(fourbitop,operand+8,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> op1 = op;

			strncpy(twozerobitop,operand+12,20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> op2 = op;

			temp -> Maddress = 0;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("instNum: %d\n", temp -> instructionAddress);
			//printf("reg1: %d\n",temp -> reg1);
			//printf("op1: %d\n",temp -> op1);
			//printf("op2: %d\n",temp -> op2);			

		} else if (!strncmp(operand, "0011", 4))
		{
			//printf("found DIV\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "0011";

			temp -> instructionAddress = instNum++;
			
			strncpy(fourbitop,operand+4,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> reg1 = op;

			strncpy(fourbitop,operand+8,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> op1 = op;

			strncpy(twozerobitop,operand+12,20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> op2 = op;

			temp -> Maddress = 0;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("instNum: %d\n", temp -> instructionAddress);
			//printf("reg1: %d\n",temp -> reg1);
			//printf("op1: %d\n",temp -> op1);
			//printf("op2: %d\n",temp -> op2);			

		} else if (!strncmp(operand, "0100", 4))
		{
			//printf("found CMP\n");

			temp = malloc(sizeof(struct POP));
			
			temp -> opcode = "0100";

			temp -> instructionAddress = instNum++;
			
			strncpy(fourbitop,operand+4,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> reg1 = op;

			strncpy(twofourbitop,operand+8,24);
			op = strtol(twofourbitop, &endptr, 2);
			temp -> op1 = op;
			
			temp -> op2 = 0;

			temp -> Maddress = 0;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("instNum: %d\n", temp -> instructionAddress);
			//printf("%d\n",temp -> op1);
			//printf("%d\n",temp->reg1);
		} else if (!strncmp(operand, "0101", 4))
		{
			//printf("found MOV\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "0101";

			temp -> instructionAddress = instNum++;
			
			strncpy(fourbitop,operand+4,4);
			op = strtol(fourbitop, &endptr, 2);
			temp -> reg1 = op;

			strncpy(twofourbitop,operand+8,24);
			op = strtol(twofourbitop, &endptr, 2);
			temp -> op1 = op;
			
			temp -> op2 = 0;

			temp -> Maddress = 0;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("instNum: %d\n", temp -> instructionAddress);
			//printf("%d\n",temp -> op1);
			//printf("%d\n",temp->reg1);
		} else if (!strncmp(operand, "0110", 4))
		{
			//printf("found LDR\n");
		} else if (!strncmp(operand, "0111", 4))
		{
			//printf("found STR\n");
		} else if (!strncmp(operand, "1000", 4))
		{
			//printf("found B\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "1000";

			temp -> instructionAddress = instNum++;

			temp -> reg1 = 0;

			temp -> op1 = 0;
			
			temp -> op2 = 0;
			
			strncpy(twozerobitop, operand+4, 20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> Maddress = op;
			//printf("Maddress op: %d\n", op);

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;

			//printf("%d\n",temp->Maddress);
		} else if (!strncmp(operand, "1001", 4))
		{
			//printf("found BLT\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "1001";

			temp -> instructionAddress = instNum++;

			temp -> reg1 = 0;

			temp -> op1 = 0;
			
			temp -> op2 = 0;
			
			strncpy(twozerobitop, operand+4, 20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> Maddress = op;
			//printf("Maddress op: %d\n", op);

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;
			
			//printf("%d\n",temp->Maddress);
		} else if (!strncmp(operand, "1010", 4))
		{
			//printf("found BE\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "1010";

			temp -> instructionAddress = instNum++;

			temp -> reg1 = 0;

			temp -> op1 = 0;
			
			temp -> op2 = 0;
			
			strncpy(twozerobitop, operand+4, 20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> Maddress = op;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;
			
			//printf("%d\n",temp->Maddress);
		} else if (!strncmp(operand, "1011", 4))
		{
			//printf("found BGT\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "1011";

			temp -> instructionAddress = instNum++;

			temp -> reg1 = 0;

			temp -> op1 = 0;
			
			temp -> op2 = 0;
			
			strncpy(twozerobitop, operand+4, 20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> Maddress = op;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;
			
			//printf("%d\n",temp->Maddress);
		} else if (!strncmp(operand, "1100", 4))
		{
			//printf("found JMP\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "1100";

			temp -> instructionAddress = instNum++;

			temp -> reg1 = 0;

			temp -> op1 = 0;
			
			temp -> op2 = 0;
			
			strncpy(twozerobitop, operand+4, 20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> Maddress = op;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;
			
			//printf("%d\n",temp->Maddress);
		} else if (!strncmp(operand, "1101", 4))
		{
			//printf("found RTN\n");

			temp = malloc(sizeof(struct POP));

			temp -> opcode = "1101";

			temp -> instructionAddress = instNum++;

			temp -> reg1 = 0;

			temp -> op1 = 0;
			
			temp -> op2 = 0;
			
			strncpy(twozerobitop, operand+4, 20);
			op = strtol(twozerobitop, &endptr, 2);
			temp -> Maddress = op;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;
			
			//printf("%d\n",temp->Maddress);
		} else if (!strncmp(operand, "1110", 4))
		{
			printf("...program loaded.\n");
			fclose(program);

			temp = malloc(sizeof(struct POP));
			
			temp -> opcode = "1110";

			temp -> instructionAddress = instNum++;
			
			temp -> reg1 = 0;

			temp -> op1 = 0;
			
			temp -> op2 = 0;

			temp -> Maddress = 0;

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;
			break;
		}
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
