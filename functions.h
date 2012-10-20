#define NUMREGISTERS 16

void fetch(void);

void decode(void);

void execute(void);

void init(void);

void testinit(void);

typedef struct POP{
	int instructionAddress;
	char * opcode;
	int reg1;
	int op1;
	int op2;
	int Maddress;
	struct POP *next;
} POP;

struct registers {
		int PC;
		int LR;
		int reg[NUMREGISTERS];
};
