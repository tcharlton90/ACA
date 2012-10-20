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
	testinit();
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
		decode();
		execute();
		printf("Finished clock cycle number %d\n\n", clock++);
	}
	return 0;
}
