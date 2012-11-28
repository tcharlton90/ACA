#include "stdio.h"
#include "stdlib.h"
#include "functions.h"
#include "string.h"

POP * decodeUnit (bitStream * fetchedInstruction, int decodedEnd, POP *tail)
{
	int op, opa, opb, opc, instructionNumber;
	char twotwobitop[24], fivebitop[5], * operand = malloc((sizeof(char)*32)), * endptr;
	struct POP * decodedInstruction, *temp;
	
	printf(" D");

	operand = fetchedInstruction->instruction;
	instructionNumber = fetchedInstruction->address;
	temp = malloc(sizeof(struct POP));
	temp -> opcode = "2";

	if(!strncmp(operand, "00000", 5))
	{
		//printf("found ADD\n");
		strncpy(fivebitop,operand+5,5);
		opa = strtol(fivebitop, &endptr, 2);

		strncpy(fivebitop,operand+10,5);
		opb = strtol(fivebitop, &endptr, 2);

		strncpy(fivebitop,operand+15,5);
		opc = strtol(fivebitop, &endptr, 2);

		if (registerBlock.scoreBoard[opa] || registerBlock.scoreBoard[opb] || registerBlock.scoreBoard[opc] )
		{
			return temp;
		} else {
			registerBlock.scoreBoard[opa] = 1;
			registerBlock.scoreBoard[opb] = 1;
			registerBlock.scoreBoard[opc] = 1;
		}

		temp -> opcode = "00000";

		temp -> instructionAddress = instructionNumber;

		temp -> reg1 = opa;

		temp -> op1 = opb;

		temp -> op2 = opc;

		temp -> Maddress = (-1);

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

		temp -> opcode = "00001";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op1 = op;

		strncpy(fivebitop,operand+15,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op2 = op;

		temp -> Maddress = (-1);

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

		temp -> opcode = "00010";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op1 = op;

		strncpy(fivebitop,operand+15,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op2 = op;

		temp -> Maddress = (-1);

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

		temp -> opcode = "00011";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op1 = op;

		strncpy(fivebitop,operand+15,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op2 = op;

		temp -> Maddress = (-1);

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
		
		temp -> opcode = "00100";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		strncpy(fivebitop,operand+10,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op1 = op;
		
		temp -> op2 = (-1);

		temp -> Maddress = (-1);

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("instNum: %d\n", temp -> instructionAddress);
		//printf("%d\n",temp -> op1);
		//printf("%d\n",temp->reg1);
	} else if (!strncmp(operand, "00101", 5))
	{
		//printf("found MOV\n");

		temp -> opcode = "00101";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		strncpy(twotwobitop,operand+10,22);
		op = strtol(twotwobitop, &endptr, 2);
		temp -> op1 = op;
		
		temp -> op2 = (-1);

		temp -> Maddress = (-1);

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

		temp -> opcode = "00110";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		strncpy(fivebitop, operand+ 10,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op1 = op;
		
		temp -> op2 = (-1);
		
		temp -> Maddress = (-1);
		
		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
	} else if (!strncmp(operand, "00111", 5))
	{
		//printf("found STR\n");

		temp -> opcode = "00111";

		temp -> instructionAddress = instructionNumber;
		
		strncpy(fivebitop,operand+5,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		strncpy(fivebitop, operand+ 10,5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> op1 = op;
		
		temp -> op2 = (-1);
		
		temp -> Maddress = (-1);
		
		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
	} else if (!strncmp(operand, "01000", 5))
	{
		//printf("found B\n");

		temp -> opcode = "01000";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		temp -> op1 = (-1);
		
		temp -> op2 = (-1);
		
		temp -> Maddress = (-1);
		//printf("Maddress op: %d\n", op);

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;

		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01001", 5))
	{
		//printf("found BLT\n");

		temp -> opcode = "01001";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		temp -> op1 = (-1);
		
		temp -> op2 = (-1);
		
		temp -> Maddress = (-1);
		//printf("Maddress op: %d\n", op);

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01010", 5))
	{
		//printf("found BE\n");

		temp -> opcode = "01010";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		temp -> op1 = (-1);
		
		temp -> op2 = (-1);
		
		temp -> Maddress = (-1);

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01011", 5))
	{
		//printf("found BGT\n");

		temp -> opcode = "01011";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		temp -> op1 = (-1);
		
		temp -> op2 = (-1);
		
		temp -> Maddress = (-1);

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01100", 5))
	{
		//printf("found JMP\n");

		temp -> opcode = "01100";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		temp -> op1 = (-1);
		
		temp -> op2 = (-1);
		
		temp -> Maddress = (-1);

		temp -> next = NULL;

		tail->next = temp;
		tail = temp;
		
		//printf("%d\n",temp->Maddress);
	} else if (!strncmp(operand, "01101", 5))
	{
		//printf("found RTN\n");

		temp -> opcode = "01101";

		temp -> instructionAddress = instructionNumber;

		strncpy(fivebitop, operand+5, 5);
		op = strtol(fivebitop, &endptr, 2);
		registerBlock.scoreBoard[op] = 1;
		temp -> reg1 = op;

		temp -> op1 = (-1);
		
		temp -> op2 = (-1);
		
		temp -> Maddress = (-1);

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
			
			temp -> opcode = "01110";

			temp -> instructionAddress = instructionNumber;
			
			temp -> reg1 = (-1);

			temp -> op1 = (-1);
			
			temp -> op2 = (-1);

			temp -> Maddress = (-1);

			temp -> next = NULL;

			tail->next = temp;
			tail = temp;
		}
	}
	decodedInstruction = temp;

	//printf("%s\n", name);
	return decodedInstruction;
}