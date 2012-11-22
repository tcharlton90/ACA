#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

// TODO change read-in hack to strcmp
//	Branch predictor: not right or wrong, predicted taken or predicted not taken
//	Nice programs
//	Out of order
//	Register renaming unit
//	Other features (Rob...)
//	Hypothesis'
//	\r stuff and nice formatting

int main (int argc, char *argv[])
{
	char * tick = malloc(sizeof(char));

	printf("Starting up\n");

	init( argv );
	
	printf("Started Up\n");

	while (1)
	{
		if (((int) * tick == 120) || finished)
		{
			break;
		}

		fetch();
		decode();
		execute();
		cycleClock();
		//testinit();
		//test();
	}
	printf("\n\n");
	return 0;
}
