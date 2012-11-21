#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

// TODO change read-in hack to strcmp
//	Branch predictor: not right or wrong, predicted taken or predicted not taken
//	Super-scaler
//	Out of order
//	Register renaming unit
//	Other features (Rob...)
//	Hypothesis'

int main (void)
{
	char * tick = malloc(sizeof(char));

	printf("Starting up\n");
	init();
	
	printf("Started Up\n");

	while (1)
	{
		//scanf("%c", tick);
		//printf("%d\n", (int) * tick);
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
