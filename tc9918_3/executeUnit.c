#include "stdio.h"
#include "stdlib.h"
#include "functions.h"
#include "branch.h"

void executeUnit ( POP *decodedInstruction )
{
	int j, i, k; // reg, op1, op2
	switch(atoi(decodedInstruction->opcode)){
		case 0: //ADD
		    instructionsExcecuted++;
			j = decodedInstruction->reg1;
			i = decodedInstruction->op1;
			k = decodedInstruction->op2;
			nextRegisterBlock -> reg[j] = i + k;
			//printf("ADD: %d, %d, %d\n", registerBlock -> reg[j], i, k);
			break;
		case 1: //SUB
		    instructionsExcecuted++;
			j = decodedInstruction->reg1;
			i = decodedInstruction->op1;
			k = decodedInstruction->op2;
			nextRegisterBlock -> reg[j] = i - k;
			break;
		case 10: //MUL
		    instructionsExcecuted++;
			j = decodedInstruction->reg1;
			i = decodedInstruction->op1;
			k = decodedInstruction->op2;
			nextRegisterBlock -> reg[j] = i * k;
			break;
		case 11: //DIV
		    instructionsExcecuted++;
			j = decodedInstruction->reg1;
			i = decodedInstruction->op1;
			k = decodedInstruction->op2;
			nextRegisterBlock -> reg[j] = i / k;
			break;
		case 100: //CMP
		    instructionsExcecuted++;
			j = decodedInstruction->reg1;
			k = decodedInstruction->op1;
			//printf ("%d cmp %d\n",j,i);
			if (j > k)
			{
				nextRegisterBlock -> FLAG_GT = true;
				//printf("\nCMP: %d, %d\n", j, k);
			} else if ( j == k)
			{
				nextRegisterBlock -> FLAG_E = true;
				//printf("\nCMP: %d, %d\n", j, k);
			} else if ( j < k)
			{
				nextRegisterBlock -> FLAG_LT = true;
				//printf("\nCMP: %d, %d\n", j, k);
			}
			break;
		case 101: //MOV
		    instructionsExcecuted++;
			//printf("moving %d to register %d\n", decodedInstruction->op1, decodedInstruction->reg1);
			i = decodedInstruction->op1;
			j = decodedInstruction->reg1;
			nextRegisterBlock -> reg[j] = i;
			break;
		case 110: //LDR
		    instructionsExcecuted++;
			i = decodedInstruction->reg1;
			j = decodedInstruction->op1;
			nextRegisterBlock -> reg[i] = memory[registerBlock -> reg[j]];
			break;
		case 111: //STR
		    instructionsExcecuted++;
			i = decodedInstruction->reg1;
			j = registerBlock -> reg[decodedInstruction->op1];
			memory[j] = i;
			break;
		case 1000: //B
		    instructionsExcecuted++;
			i = decodedInstruction->reg1;
			nextRegisterBlock -> PC = i;
			clearPipeline();
			clearInstructionIssue();
			//clearInstructionIssue();
			//printf("%d\n",i);
			break;
		case 1001: //BLT
			instructionsExcecuted++;
			if (BRANCH)
			{
				i = getPred(decodedInstruction -> reg1);
				if ((i && registerBlock -> FLAG_LT) || (!i && !registerBlock -> FLAG_LT))
				{
					predictedCorrect++;
					break;
				} else {
					// branch prediction got it wrong
					if (i) //predicted taken, acturally not.
					{
						predictedIncorrect++;
						clearPipeline();
						clearInstructionIssue();
						nextRegisterBlock -> PC = decodedInstruction->instructionAddress+1;
						nextRegisterBlock -> FLAG_LT = false;
						//printf("------------------------\n");
					} else {
						// predicted not taken, actually was.
						predictedIncorrect++;
						clearPipeline();
						clearInstructionIssue();
						nextRegisterBlock -> PC = decodedInstruction -> reg1;
						nextRegisterBlock -> FLAG_LT = false;
					}
				}

			} else {
				i = decodedInstruction->reg1;
				if (registerBlock -> FLAG_LT)
				{
					//registerBlock -> PC = i;
					nextRegisterBlock -> PC = i;
					nextRegisterBlock -> FLAG_LT = false;
					clearPipeline();
					clearInstructionIssue();
				} 
			}
				//branch prediction got it wrong
				//clearPipeline();
				//clearInstructionIssue();
				//nextRegisterBlock -> PC = decodedInstruction->instructionAddress+1;
				//nextRegisterBlock -> FLAG_LT = false;
			
			//printf("%d\n",i);
			break;
		case 1010: //BE
		    instructionsExcecuted++;
			i = decodedInstruction->reg1;
			if (registerBlock -> FLAG_E)
			{
				nextRegisterBlock -> PC = i;
				nextRegisterBlock -> FLAG_E = false;
				clearPipeline();
				clearInstructionIssue();
			}
			//printf("%d\n",i);
			break;
		case 1011: //BGT
		    instructionsExcecuted++;
			i = decodedInstruction->reg1;
			{
				nextRegisterBlock -> PC = i;
				nextRegisterBlock -> FLAG_GT = false;
				clearPipeline();
				clearInstructionIssue();
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
			test();
			stats();
			//test();
			break;
		case 1111: //NOP
			NOPS++;
			break;
		case 11000: // bi

			break;
		case 11001: //BLTi
			instructionsExcecuted++;
			if (BRANCH)
			{
				i = getPred(decodedInstruction -> reg1);
				if (registerBlock -> FLAG_LT)
				{
					predictedCorrect++;
					nextRegisterBlock -> FLAG_LT = false;
					break;
				} else {
					// branch prediction got it wrong
					predictedIncorrect++;
					clearPipeline();
					clearInstructionIssue();
					nextRegisterBlock -> PC = decodedInstruction->instructionAddress+1;
					nextRegisterBlock -> FLAG_LT = false;
				}

			} else {
				i = decodedInstruction->reg1;
				if (registerBlock -> FLAG_LT)
				{
					//registerBlock -> PC = i;
					nextRegisterBlock -> PC = i;
					nextRegisterBlock -> FLAG_LT = false;
					clearPipeline();
					clearInstructionIssue();
				} 
			}
				//branch prediction got it wrong
				//clearPipeline();
				//clearInstructionIssue();
				//nextRegisterBlock -> PC = decodedInstruction->instructionAddress+1;
				//nextRegisterBlock -> FLAG_LT = false;
			
			//printf("%d\n",i);
			break;
		case 11010: // BGTi
			instructionsExcecuted++;
			if (BRANCH)
			{
				i = getPred(decodedInstruction -> reg1);
				if (registerBlock -> FLAG_GT)
				{
					predictedCorrect++;
					nextRegisterBlock -> FLAG_GT = false;
					break;
				} else {
					// branch prediction got it wrong
					predictedIncorrect++;
					clearPipeline();
					clearInstructionIssue();
					nextRegisterBlock -> PC = decodedInstruction->instructionAddress+1;
					nextRegisterBlock -> FLAG_GT = false;
				}

			} else {
				i = decodedInstruction->reg1;
				if (registerBlock -> FLAG_GT)
				{
					//registerBlock -> PC = i;
					nextRegisterBlock -> PC = i;
					nextRegisterBlock -> FLAG_GT = false;
					clearPipeline();
					clearInstructionIssue();
				} 
			}
			break;
		case 11011: //BEi
		instructionsExcecuted++;
			if (BRANCH)
			{
				i = getPred(decodedInstruction -> reg1);
				if (registerBlock -> FLAG_E)
				{
					predictedCorrect++;
					nextRegisterBlock -> FLAG_E = false;
					break;
				} else {
					// branch prediction got it wrong
					predictedIncorrect++;
					clearPipeline();
					clearInstructionIssue();
					nextRegisterBlock -> PC = decodedInstruction->instructionAddress+1;
					nextRegisterBlock -> FLAG_E = false;
				}

			} else {
				i = decodedInstruction->reg1;
				if (registerBlock -> FLAG_E)
				{
					//registerBlock -> PC = i;
					nextRegisterBlock -> PC = i;
					nextRegisterBlock -> FLAG_E = false;
					clearPipeline();
					clearInstructionIssue();
				} 
			}
			break;
		default:
			break;
	}
}