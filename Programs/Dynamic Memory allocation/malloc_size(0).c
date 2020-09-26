#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	// Allocate a memory of size 0 using malloc
	int* ptr = (int*) malloc(0);
	if(ptr == NULL)
	{
		printf("Pointer is null\n");
	}
	else
	{
		printf("Pointer is not null\n");
	}

	// The pointer points to either a valid memory location or null pointer
	// This is implementation dependent
	free(ptr);

	return 0;
}
