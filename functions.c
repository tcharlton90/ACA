#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "functions.h"

FILE * program;
struct POP * head, *temp, *tail;
struct registers registerBlock;
struct bitStream *BShead , *BStemp;
int decodedEnd = 0;
char * operation[] =  {"ADD","SUB","MUL","DIV","CMP","MOV","LDR","STR","B","BLT","BE","BGT","JMP","RTN","END"};;

//-----------------------------//
//
// Pipeline stage results
struct bitStream * fetchedInstruction;
struct POP * decodedInstruction;
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

void decode(void)
{
	int op, instNum = 1;
	char twofourbitop[25];
	char twozerobitop[21];
	char fourbitop[5];
	char* endptr;
	char * operand = malloc((sizeof(char)*32));

	printf("Decoding\n");

	operand = fetchedInstruction->instruction;

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
		if (decodedEnd)
		{
			printf("Nothing to decode\n");
		} else {
			decodedEnd = 1;

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
		}
	}
	decodedInstruction = temp;
	
	//printf("%s\n", name);
}

void execute(void)
{
	char * name, * endptr;
	int j, i, k, l; // reg, op1, op2, tmp

	name = operation[strtol(decodedInstruction->opcode, &endptr, 2)];
	printf("Executing %s\n", name);
	//printf("%d\n",atoi(decodedInstruction->opcode));
	switch(atoi(decodedInstruction->opcode)){
		case 0: //ADD
			j = decodedInstruction->reg1;
			l = decodedInstruction->op1;
			i = registerBlock.reg[l];
			k = decodedInstruction->op2;
			registerBlock.reg[j] = i + k;
			break;
		case 1: //SUB
			j = decodedInstruction->reg1;
			l = decodedInstruction->op1;
			i = registerBlock.reg[l];
			k = decodedInstruction->op2;
			registerBlock.reg[j] = i - k;
			break;
		case 10: //MUL
			j = decodedInstruction->reg1;
			l = decodedInstruction->op1;
			i = registerBlock.reg[l];
			k = decodedInstruction->op2;
			registerBlock.reg[j] = i * k;
			break;
		case 11: //DIV
			j = decodedInstruction->reg1;
			l = decodedInstruction->op1;
			i = registerBlock.reg[l];
			k = decodedInstruction->op2;
			registerBlock.reg[j] = i / k;
			break;
		case 100: //CMP
			j = decodedInstruction->reg1;
			l = registerBlock.reg[j];
			i = decodedInstruction->op1;
			if (j > i)
			{
				registerBlock.FLAG_GT = true;
			} else if ( j == i)
			{
				registerBlock.FLAG_E = true;
			} else if ( j < i)
			{
				registerBlock.FLAG_LT = true;
			}
			break;
		case 101: //MOV
			//printf("moving %d to register %d\n", decodedInstruction->op1, decodedInstruction->reg1);
			i = decodedInstruction->op1;
			j = decodedInstruction->reg1;
			registerBlock.reg[j] = i;
			break;
		case 110: //LDR
			break;
		case 111: //STR
			break;
		case 1000: //B
			break;
		case 1001: //BLT
			break;
		case 1010: //BE
			break;
		case 1011: //BGT
			break;
		case 1100: //JMP
			break;
		case 1101: //RTN
			break;
		case 1110: //END
			break;
		default:
			break;
	}
}

void init(void)
{
	int instNum = 1;
	char * operand = malloc((sizeof(char)*32));
	char * comment = malloc((sizeof(char)*256));
	char * opcode;

	//set registers to 0
	memset(registerBlock.reg,0,NUMREGISTERS);
	registerBlock.PC = 1;

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
