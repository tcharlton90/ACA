#include "stdbool.h"

#define NUMREGISTERS 32
#define MEMORYSIZE 4000
#define SPEED 5000000 //speed is delay in ns
#ifndef NSCALAR
    #define NSCALAR 4
#endif

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

void testDecode(void);

void issue(void);

void testIssue(void);

void copyIssueBuffer(void);

void checkDependancies(void);

void dereference(void);

typedef struct POP{
	int instructionAddress;		// def
	char * opcode;				// def
	int reg1;					// def
	int op1;					// optional
	int op2;					// optional
	struct POP *next;
} POP;

struct registers {
		int PC;
		int LR;
		int reg[NUMREGISTERS];
		bool FLAG_E;
		bool FLAG_LT;
		bool FLAG_GT;
};

typedef struct bitStream{
	int address;
	char instruction[32];
	struct bitStream *next;
} bitStream;

typedef struct issueBuffer{
	struct POP * instructionForIssue;
	int dependancies;
	int decoded;
	struct issueBuffer * next;
} issueBuffer;

POP * getIssueBuffer (void);

void setIssueBuffer(POP * toAdd, int dep);

struct bitStream *BShead , *BStemp, * fetchedInstruction[NSCALAR], * nextFetchedInstruction[NSCALAR];
struct registers *registerBlock, *nextRegisterBlock;
struct POP * decodedInstruction[NSCALAR], * nextDecodedInstruction[NSCALAR], * issuedInstruction[NSCALAR], * nextIssuedInstruction[NSCALAR] ;
int endOfFile, penalty, finished, fetchedAll, fetchedAllAddress, printedFs, memory[MEMORYSIZE], dependancies, instructionsFetched, instructionsExcecuted, branchesTaken, predictedCorrect, predictedIncorrect, scoreBoard[NUMREGISTERS], scoreBFlags, NOPS, BRANCH, DEBUG, VERBOSE;
struct issueBuffer * issueBufferHead, * nextIssueBufferHead;