#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int* ptr = NULL;
	int n;

	printf("Enter the number of elements:");
	scanf("%d", &n);

	ptr = (int*) calloc(n, sizeof(int));
	if(!ptr)
	{
		printf("memory allocation fails\n");
	}
	else
	{
		printf("Memory successfully allocated using calloc.\n");
		for (int i = 0; i < n; i++)
		{
			ptr[i] = i * i;
		}

		printf("Elements of the array are : ");

		for(int i = 0; i < n; i++)
		{
			printf("%d ", ptr[i]);
		}

		printf("\nFreeing the allocated memory\n");

		free(ptr);
	}

	return 0;
}
