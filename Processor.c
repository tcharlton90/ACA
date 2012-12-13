#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

// TODO change read-in hack to strcmp
//	Branch predictor: not right or wrong, predicted taken or predicted not take
//	Cant make a read-in super-scaler
//	Make 32 registers
//	Move to instructions set V2
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
	printf("| FETCH |  DECODE |    EXCECUTE     |    CLOCK   |\n");
	while (1)
	{
		if (((int) * tick == 120) || finished)
		{
			break;
		}

		fetch();
		printf(" ");
		decode();
		printf("  ");
		execute();
		printf("   ");
		cycleClock();
		//testinit();
		(DEBUG) ? test() : NULL;
	}
	printf("\n");
	return 0;
}
