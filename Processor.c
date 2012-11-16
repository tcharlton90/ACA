#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

// TODO change read-in hack to strcmp

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
	return 0;
}
