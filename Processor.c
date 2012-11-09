#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

// TODO change read-in hack to strcmp

int main (void)
{
	char * tick = malloc(sizeof(char));
	int clock = 1;

	printf("Starting up\n");
	init();
	
	printf("Started Up\n");

	while (1)
	{
		scanf("%c", tick);
		//printf("%d\n", (int) * tick);
		if ( (int) * tick == 120)
		{
			break;
		}

		fetch();
		printf("Clock cycle number %d\n\n", clock++);
		decode();
		printf("Clock cycle number %d\n\n", clock++);
		execute();
		//testinit();
		//test();
		printf("Clock cycle number %d\n", clock++);
	}
	return 0;
}
