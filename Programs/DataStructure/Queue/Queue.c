#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE
{
	int number;
	struct _NODE *next;
}NODE;

NODE* front = NULL;
NODE* rear = NULL;

void Insert()
{
	int count, i;
	printf("Enter count to insert data:");
	scanf("%d", &count);
	printf ("Enter %d data\n", count);

	for (i = 0; i < count; i++)
	{
		NODE* temp = (NODE*)malloc(sizeof(NODE));
		scanf("%d", &temp->number);

		if (front == NULL && rear == NULL)
		{
			temp->next = NULL;
			front = rear = temp;
		}
		else
		{
			temp->next = NULL;
			rear->next = temp;
			rear = temp;
		}
	}
}

void Delete()
{
	if (front == NULL)
	{
		printf ("Queue is empty\n");
	}
	else
	{
		NODE* p = front;
		front = front->next;
		free(p);
	}
}

void Display()
{
	if (front == NULL)
	{
		printf ("Queue is empty\n");
	}
	else
	{
		NODE* p  = front;
		for (p = front; p != NULL; p = p->next)
		{
			printf ("%d-->", p->number);
		}
		printf("\n");
	}
}

void FreeMemory()
{
	while (front != NULL)
	{
		NODE* p = front;
		front = front->next;
		free(p);
	}
}

int main(int argc, char **argv)
{
	int option;
	printf ("Queue using linklist\n");
	while(1)
	{
		printf("Select Option From Below\n");
		printf("1.Insert\n2.Delete\n3.Display\n4.Exit\n");
		scanf("%d", &option);

		switch(option)
		{
		case 1:
		{
			Insert();
			break;
		}
		case 2:
		{
			Delete();
			break;
		}
		case 3:
		{
			Display();
			break;
		}
		case 4:
		{
			FreeMemory();
			printf ("Good Bye!\n");
			return 0;
			break;
		}
		}

	}
	return 0;
}
