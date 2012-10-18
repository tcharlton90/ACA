#include "stdio.h"
#include "stdlib.h"
#include "functions.h"

// TODO change read-in hack to strcmp

struct registers {
		int PC;
		int reg[16];
};

int main (void)
{
	char * tick = malloc(sizeof(char));
	int clock = 0;

	printf("Starting up\n");
	init();
	initFetch();
	printf("Started Fetch\n");
	initDecode();
	printf("Started Decode\n");
	initExecute();
	printf("Started Execute\n");
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
