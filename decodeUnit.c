#include "stdio.h"
#include "stdlib.h"
#include "functions.h"
#include "string.h"

POP * decodeUnit (bitStream * fetchedInstruction, int decodedEnd, POP *tail)
{
	int op, instructionNumber;
	char twotwobitop[24], fivebitop[5], twozerobitop[20], * operand = malloc((sizeof(char)*32)), * endptr;
	struct POP * decodedInstruction, *temp;
	
	printf(" D");

	operand = fetchedInstruction->instruction;
	instructionNumber = fetchedInstruction->address;

	if(!strncmp(operand, "00000", 5))
	{
		//printf("found ADD\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "00000";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op1 = op;

		strncpy(fivebitop,operand+15,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op2 = op;

		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("reg1: %d\n",temp -> reg1);
		//printf("op1: %d\n",temp -> op1);
		//printf("op2: %d\n",temp -> op2);

	} else if (!strncmp(operand, "00001", 5))
	{
		//printf("found SUB\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "00001";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op1 = op;

		strncpy(fivebitop,operand+15,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op2 = op;

		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("reg1: %d\n",temp -> reg1);
		//printf("op1: %d\n",temp -> op1);
		//printf("op2: %d\n",temp -> op2)

	} else if (!strncmp(operand, "00010", 5))
	{
		//printf("found MUL\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "00010";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op1 = op;

		strncpy(fivebitop,operand+15,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op2 = op;

		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("reg1: %d\n",temp -> reg1);
		//printf("op1: %d\n",temp -> op1);
		//printf("op2: %d\n",temp -> op2);			

	} else if (!strncmp(operand, "00011", 5))
	{
		//printf("found DIV\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "00011";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op1 = op;

		strncpy(fivebitop,operand+15,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op2 = op;

		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("reg1: %d\n",temp -> reg1);
		//printf("op1: %d\n",temp -> op1);
		//printf("op2: %d\n",temp -> op2);

	} else if (!strncmp(operand, "00100", 5))
	{
		//printf("found CMP\n");

		temp = malloc(sizeof(struct POP));
		
		temp -> opcode = "00100";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op1 = op;
		
		temp -> op2 = 0;

		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("%d\n",temp -> op1);
		//printf("%d\n",temp->reg1);
	} else if (!strncmp(operand, "00101", 5))
	{
		//printf("found MOV\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "00101";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(twotwobitop,operand+10,22);
		op = strtol(twotwobitop, &endptr, 2);
		temp -> op1 = op;
		
		temp -> op2 = 0;

		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("%d, %s\n",temp -> op1, twofourbitop);
		//printf("%d\n",temp->reg1);
	} else if (!strncmp(operand, "00110", 5))
	{
		//printf("found LDR\n");
		// destination 4 -8 
		//memory address 8 - 28
		temp = malloc(sizeof(struct POP));

		temp -> opcode = "00110";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fivebitop, operand+ 10,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op1 = op;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;
		
		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
	} else if (!strncmp(operand, "00111", 5))
	{
		//printf("found STR\n");
		
		temp = malloc(sizeof(struct POP));

		temp -> opcode = "00111";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		strncpy(fivebitop, operand+ 10,5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> op1 = op;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;
		
		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
	} else if (!strncmp(operand, "01000", 5))
	{
		//printf("found B\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "01000";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		temp -> op1 = 0;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;
		//printf("Maddress op: %d\n", op);

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01001", 5))
	{
		//printf("found BLT\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "01001";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		temp -> op1 = 0;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;
		//printf("Maddress op: %d\n", op);

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01010", 5))
	{
		//printf("found BE\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "01010";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		temp -> op1 = 0;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01011", 5))
	{
		//printf("found BGT\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "01011";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		temp -> op1 = 0;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01100", 5))
	{
		//printf("found JMP\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "01100";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		temp -> op1 = 0;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01101", 5))
	{
		//printf("found RTN\n");

		temp = malloc(sizeof(struct POP));

		temp -> opcode = "01101";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		temp -> reg1 = op;

		temp -> op1 = 0;
		
		temp -> op2 = 0;
		
		temp -> Maddress = 0;

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01110", 5))
	{
		if (decodedEnd)
		{
			printf("Nothing to decode\n");
		} else {
			temp = malloc(sizeof(struct POP));
			
			temp -> opcode = "01110";

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