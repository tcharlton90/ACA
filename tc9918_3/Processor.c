#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

// TODO change read-in hack to strcmp
//	Branch predictor: not right or wrong, predicted taken or predicted not take
//	Register renaming unit
//	Other features (Rob...)
//	Hypothesis'

int main (int argc, char *argv[])
{
	char * tick = malloc(sizeof(char));

	printf("Starting up\n");

	init( argv );
	
	printf("Started Up\n");
	printf("| FETCH |  DECODE |  ISSUE  |   EXCECUTE     |    CLOCK   |\n");
	while (1)
	{
		if (((int) * tick == 120) || finished)
		{
			break;
		}

		fetch();
		printf(" ");
		decode();
		printf(" ");
		execute();
		printf("   ");
		if (!finished)
		{
			cycleClock();
		}
		//testinit();
		(DEBUG) ? test() : NULL;
	}
	printf("\n");
	return 0;
}
