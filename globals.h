#include "stdio.h"

FILE * program;
struct POP * head, *temp, *tail;
struct registers registerBlock;
struct bitStream *BShead , *BStemp;
int decodedEnd = 0;
char * operation[] =  {"ADD","SUB","MUL","DIV","CMP","MOV","LDR","STR","B","BLT","BE","BGT","JMP","RTN","END"};;

//-----------------------------//
//
// Pipeline stage results
struct bitStream * fetchedInstruction;
struct POP * decodedInstruction;
//
//
//
//
//
//
//
//-----------------------------//