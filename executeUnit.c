#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

void executeUnit ( POP *decodedInstruction )
{
	int j, i, k; // reg, op1, op2
	switch(atoi(decodedInstruction->opcode)){
		case 0: //ADD
			j = decodedInstruction->reg1;
			i = decodedInstruction->op1;
			k = decodedInstruction->op2;
			registerBlock -> scoreBoard[j] = 0;
			registerBlock -> scoreBoard[i] = 0;
			registerBlock -> scoreBoard[k] = 0;
			nextRegisterBlock -> reg[j] = i + k;
			//printf("ADD: %d, %d, %d\n", registerBlock -> reg[j], i, k);
			break;
		case 1: //SUB
			j = decodedInstruction->reg1;
			i = decodedInstruction->op1;
			k = decodedInstruction->op2;
			registerBlock -> scoreBoard[j] = 0;
			registerBlock -> scoreBoard[i] = 0;
			registerBlock -> scoreBoard[k] = 0;
			nextRegisterBlock -> reg[j] = i - k;
			break;
		case 10: //MUL
			j = decodedInstruction->reg1;
			i = decodedInstruction->op1;
			k = decodedInstruction->op2;
			registerBlock -> scoreBoard[j] = 0;
			registerBlock -> scoreBoard[i] = 0;
			registerBlock -> scoreBoard[k] = 0;
			nextRegisterBlock -> reg[j] = i * k;
			break;
		case 11: //DIV
			j = decodedInstruction->reg1;
			i = decodedInstruction->op1;
			k = decodedInstruction->op2;
			registerBlock -> scoreBoard[j] = 0;
			registerBlock -> scoreBoard[i] = 0;
			registerBlock -> scoreBoard[k] = 0;
			nextRegisterBlock -> reg[j] = i / k;
			break;
		case 100: //CMP
			j = decodedInstruction->op1;
			k = decodedInstruction->op2;
			registerBlock -> scoreBoard[j] = 0;
			registerBlock -> scoreBoard[k] = 0;
			//printf ("%d cmp %d\n",j,i);
			if (j > k)
			{
				nextRegisterBlock -> FLAG_GT = true;
				//printf("%d,%d\n",j , k);
			} else if ( j == k)
			{
				nextRegisterBlock -> FLAG_E = true;
				//printf("%d,%d\n",j , k);
			} else if ( j < k)
			{
				nextRegisterBlock -> FLAG_LT = true;
				//printf("%d,%d\n",j , k);
			}
			break;
		case 101: //MOV
			//printf("moving %d to register %d\n", decodedInstruction->op1, decodedInstruction->reg1);
			i = decodedInstruction->op1;
			j = decodedInstruction->reg1;
			registerBlock -> scoreBoard[j] = 0;
			registerBlock -> scoreBoard[i] = 0;
			nextRegisterBlock -> reg[j] = i;
			break;
		case 110: //LDR
			i = decodedInstruction->reg1;
			j = decodedInstruction->op1;
			registerBlock -> scoreBoard[j] = 0;
			registerBlock -> scoreBoard[i] = 0;
			nextRegisterBlock -> reg[i] = memory[registerBlock -> reg[j]];
			break;
		case 111: //STR
			i = decodedInstruction->reg1;
			j = registerBlock -> reg[decodedInstruction->op1];
			registerBlock -> scoreBoard[j] = 0;
			registerBlock -> scoreBoard[i] = 0;
			memory[j] = i;
			break;
		case 1000: //B
			i = registerBlock -> reg[decodedInstruction->op1];
			nextRegisterBlock -> PC = i;
			registerBlock -> scoreBoard[i] = 0;
			clearPipeline();
			//clearInstructionIssue();
			//printf("%d\n",i);
			break;
		case 1001: //BLT
			i = registerBlock -> reg[decodedInstruction->op1];
			registerBlock -> scoreBoard[i] = 0;
			if (registerBlock -> FLAG_LT)
			{
				//registerBlock -> PC = i;
				nextRegisterBlock -> FLAG_LT = false;
			} else {
				//branch prediction got it wrong
				clearPipeline();
				clearInstructionIssue();
				nextRegisterBlock -> PC = decodedInstruction->instructionAddress+1;
				nextRegisterBlock -> FLAG_LT = false;
			}
			//printf("%d\n",i);
			break;
		case 1010: //BE
			i = registerBlock -> reg[decodedInstruction->op1];
			registerBlock -> scoreBoard[i] = 0;
			if (registerBlock -> FLAG_E)
			{
				nextRegisterBlock -> PC = i;
				nextRegisterBlock -> FLAG_E = false;
				clearPipeline();
			}
			//printf("%d\n",i);
			break;
		case 1011: //BGT
			i = registerBlock -> reg[decodedInstruction->op1];
			registerBlock -> scoreBoard[i] = 0;
			{
				nextRegisterBlock -> PC = i;
				nextRegisterBlock -> FLAG_GT = false;
				clearPipeline();
			}
			//printf("%d\n",i);
			break;
		case 1100: //JMP
			break;
		case 1101: //RTN
			break;
		case 1110: //END
			printf("\n");
			finished = 1;
			stats();
			//test();
			break;
		case 1111: //NOP
			NOPS++;
			break;
		default:
			break;
	}
}