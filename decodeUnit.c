#include "stdio.h"
#include "stdlib.h"
#include "functions.h"
#include "string.h"

POP * decodeUnit (bitStream * fetchedInstruction, int decodedEnd, POP *tail)
{
	int op, instructionNumber;
	char twofourbitop[24], fourbitop[4], twozerobitop[20], * operand = malloc((sizeof(char)*32)), * endptr;
	struct POP * decodedInstruction, *temp;
	
	printf(" D");

	operand = fetchedInstruction->instruction;
	instructionNumber = fetchedInstruction->address;

	if(!strncmp(operand, "0000", 4))
	{
		//printf("found ADD\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "0000";

		temp -> instructionAddress = instructionNumber; 

		strncpy(fourbitop,operand+4,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fourbitop,operand+8,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> op1 = op;

		strncpy(fourbitop,operand+12,4);
		op = strtol(fourbitop, &endptr, 2);
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

		temp -> instructionAddress = instructionNumber;

		strncpy(fourbitop,operand+4,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fourbitop,operand+8,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> op1 = op;

		strncpy(fourbitop,operand+12,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> op2 = op;

		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("reg1: %d\n",temp -> reg1);
		//printf("op1: %d\n",temp -> op1);
		//printf("op2: %d\n",temp -> op2)

	} else if (!strncmp(operand, "0010", 4))
	{
		//printf("found MUL\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "0010";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fourbitop,operand+4,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fourbitop,operand+8,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> op1 = op;

		strncpy(fourbitop,operand+12,4);
		op = strtol(fourbitop, &endptr, 2);
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

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fourbitop,operand+4,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fourbitop,operand+8,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> op1 = op;

		strncpy(fourbitop,operand+12,4);
		op = strtol(fourbitop, &endptr, 2);
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

		temp -> instructionAddress = instructionNumber;
		
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

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fourbitop,operand+4,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(twofourbitop,operand+8,(24*sizeof(char)));
		op = strtol(twofourbitop, &endptr, 2);
		temp -> op1 = op;
		
		temp -> op2 = 0;

		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("%d, %s\n",temp -> op1, twofourbitop);
		//printf("%d\n",temp->reg1);
	} else if (!strncmp(operand, "0110", 4))
	{
		//printf("found LDR\n");
		// destination 4 -8 
		//memory address 8 - 28
		temp = malloc(sizeof(struct POP));

		temp -> opcode = "0110";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fourbitop,operand+4,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fourbitop, operand+ 8,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> op1 = op;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;
		
		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
	} else if (!strncmp(operand, "0111", 4))
	{
		//printf("found STR\n");
		
		temp = malloc(sizeof(struct POP));

		temp -> opcode = "0111";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fourbitop,operand+4,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fourbitop, operand+ 8,4);
		op = strtol(fourbitop, &endptr, 2);
		temp -> op1 = op;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;
		
		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
	} else if (!strncmp(operand, "1000", 4))
	{
		//printf("found B\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "1000";

		temp -> instructionAddress = instructionNumber;

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

		temp -> instructionAddress = instructionNumber;

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

		temp -> instructionAddress = instructionNumber;

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

		temp -> instructionAddress = instructionNumber;

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

		temp -> instructionAddress = instructionNumber;

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

		temp -> instructionAddress = instructionNumber;

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
			temp = malloc(sizeof(struct POP));
			
			temp -> opcode = "1110";

			temp -> instructionAddress = instructionNumber;
			
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
	return decodedInstruction;
}