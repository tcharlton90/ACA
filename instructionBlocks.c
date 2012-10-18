#include "functions.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct _POP{
	int opcode;
	int reg1;
	int op1;
	int op2;
	struct _POP *next;
} POP;