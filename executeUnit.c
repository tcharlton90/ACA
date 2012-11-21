#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

void executeUnit ( POP *decodedInstruction )
{

	int j, i, k, l; // reg, op1, op2, tmp
	switch(atoi(decodedInstruction->opcode)){
		case 0: //ADD
			j = decodedInstruction->reg1;
			i = registerBlock.reg[decodedInstruction->op1];
			k = registerBlock.reg[decodedInstruction->op2];
			registerBlock.reg[j] = i + k;
			//printf("ADD: %d, %d, %d\n", registerBlock.reg[j], i, k);
			break;
		case 1: //SUB
			j = decodedInstruction->reg1;
			i = registerBlock.reg[decodedInstruction->op1];
			k = registerBlock.reg[decodedInstruction->op2];
			registerBlock.reg[j] = i - k;
			break;
		case 10: //MUL
			j = decodedInstruction->reg1;
			i = registerBlock.reg[decodedInstruction->op1];
			k = registerBlock.reg[decodedInstruction->op2];
			registerBlock.reg[j] = i * k;
			break;
		case 11: //DIV
			j = decodedInstruction->reg1;
			i = registerBlock.reg[decodedInstruction->op1];
			k = registerBlock.reg[decodedInstruction->op2];
			registerBlock.reg[j] = i / k;
			break;
		case 100: //CMP
			l = decodedInstruction->reg1;
			j = registerBlock.reg[l];
			i = decodedInstruction->op1;
			k = registerBlock.reg[i];
			//printf ("%d cmp %d\n",j,i);
			if (j > k)
			{
				registerBlock.FLAG_GT = true;
				//printf("%d,%d\n",j , k);
			} else if ( j == k)
			{
				registerBlock.FLAG_E = true;
				//printf("%d,%d\n",j , k);
			} else if ( j < k)
			{
				registerBlock.FLAG_LT = true;
				//printf("%d,%d\n",j , k);
			}
			break;
		case 101: //MOV
			//printf("moving %d to register %d\n", decodedInstruction->op1, decodedInstruction->reg1);
			i = decodedInstruction->op1;
			j = decodedInstruction->reg1;
			registerBlock.reg[j] = i;
			break;
		case 110: //LDR
			i = decodedInstruction->reg1;
			j = decodedInstruction->Maddress;
			registerBlock.reg[i] = memory[j];
			break;
		case 111: //STR
			i = decodedInstruction->reg1;
			j = decodedInstruction->Maddress;
			registerBlock.reg[j] = memory[i];
			break;
		case 1000: //B
			i = decodedInstruction->Maddress;
			registerBlock.PC = i;
			clearPipeline();
			//printf("%d\n",i);
			break;
		case 1001: //BLT
			i = decodedInstruction->Maddress;
			if (registerBlock.FLAG_LT)
			{
				//registerBlock.PC = i;
				registerBlock.FLAG_LT = false;
				//clearPipeline();
			} else {
				//branch prediction got it wrong
				clearPipeline();
				registerBlock.PC = decodedInstruction->instructionAddress+1;
				registerBlock.FLAG_LT = false;
			}
			//printf("%d\n",i);
			break;
		case 1010: //BE
			i = decodedInstruction->Maddress;
			if (registerBlock.FLAG_E)
			{
				registerBlock.PC = i;
				registerBlock.FLAG_E = false;
				clearPipeline();
			}
			//printf("%d\n",i);
			break;
		case 1011: //BGT
			i = decodedInstruction->Maddress;
			if (registerBlock.FLAG_GT)
			{
				registerBlock.PC = i;
				registerBlock.FLAG_GT = false;
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
		default:
			break;
	}

}