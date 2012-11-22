#include "stdio.h"
#include "stdlib.h"
#include "string.h"

FILE * program;
char * branchDest[500];

int lookupBranchDest (char * label)
{
	int i = 1;
	while (i < 500)
		if (!strcmp(label,branchDest[i]))
		{
			return i;
		}

	return 0;
}

int main (int argc, char *argv[])
{
	char * line, * command, * tmp;
	int lineNumber = 1;

	program = fopen(argv[1],"r+");
	line = malloc((sizeof(char)*32));
	command = malloc((sizeof(char)*32));
	tmp = malloc((sizeof(char)*32));

	if (!program)
	{
		printf("%s is not a recognised program!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fscanf(program, "%[^\n]", line) != 0)
	{
		printf("%s\n", line);

		//take out labels
		sscanf(line,  "%s", command);
		tmp = strchr(command, ':');
		//printf("%s", tmp);
		//fflush(stdout);
		if (tmp != NULL)
		{
			branchDest[lineNumber] = command;
			sscanf(line,  "%[^\n]", line);
		}

		printf("%s\n", line);

		fscanf(program, "%[\n]", line);
		lineNumber++;
	}

	return 0;
}