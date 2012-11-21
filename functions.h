#include "stdbool.h"

#define NUMREGISTERS 16
#define MEMORYSIZE 4000
#define SPEED 10000000 //speed is delay in ns
#define NSCALAR 4

void fetch(void);

void decode(void);

void execute(void);

void cycleClock(void);

void clearPipeline(void);

void clearInstructionIssue(void);

void init(void);

void testinit(void);

void test(void);

void stats(void);

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
		int scoreBoard[NUMREGISTERS];
		bool FLAG_E;
		bool FLAG_LT;
		bool FLAG_GT;
};

typedef struct bitStream{
	int address;
	char instruction[32];
	struct bitStream *next;
} bitStream;


struct registers registerBlock;

int finished;

int memory[MEMORYSIZE];

struct bitStream * fetchedInstruction[NSCALAR], * nextFetchedInstruction[NSCALAR];
struct POP * decodedInstruction[NSCALAR], * nextDecodedInstruction[NSCALAR];