void initFetch(void);

void initDecode(void);

void initExecute(void);

void fetch(void);

void decode(void);

void execute(void);

void init(void);

typedef struct POP{
	int opcode;
	int reg1;
	int op1;
	int op2;
	struct POP *next;
} POP;