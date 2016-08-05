#include <stdio.h>
#include <stdlib.h>

int uninitialized;
int initialized = 777;

int
main(int ac, char **av)
{
	printf("Uninitialized variable holds %d\n", uninitialized);
	printf("Initialized variable holds %d\n", initialized);
	uninitialized = 1234;
	printf("Uninitialized variable now holds %d\n", uninitialized);
	initialized = 4321;
	printf("Initialized variable now holds %d\n", initialized);

	return 0;
}
