#include "stdbool.h"

#define NUMREGISTERS 16
#define MEMORYSIZE 4000
#define SPEED 5000000 //speed is delay in ns
#define NSCALAR 4

void fetch(void);

void decode(void);

void execute(void);

void cycleClock(void);

void clearPipeline(void);

void clearInstructionIssue(void);

void init( char * argv[]);

void testinit(void);

void test(void);

void stats(void);

void testFetch(void);

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

struct bitStream *BShead , *BStemp, * fetchedInstruction[NSCALAR], * nextFetchedInstruction[NSCALAR];
struct registers registerBlock;
struct POP * decodedInstruction[NSCALAR], * nextDecodedInstruction[NSCALAR];
int finished, fetchedAll, memory[MEMORYSIZE];