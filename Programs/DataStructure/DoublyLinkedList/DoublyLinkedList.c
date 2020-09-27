#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE
{
	int data;
	struct _NODE* next;
	struct _NODE* prev;
}NODE;

NODE* head = NULL;
NODE* tail = NULL;

void Insert()
{
	int count, i;
	printf ("Enter How many Elements:");
	scanf ("%d", &count);

	printf("Enter %d elements\n", count);

	for (i = 0; i < count; i++)
	{
		NODE* newNOde = (NODE*)malloc(sizeof(NODE));
		scanf("%d", &newNOde->data);

		if (head == NULL)
		{
			newNOde->next = NULL;
			newNOde->prev = NULL;
			head = tail = newNOde;
		}
		else
		{
			tail->next = newNOde;
			newNOde->next = NULL;
			newNOde->prev = tail;
			tail = newNOde;
		}
	}
}

void Display()
{
	int option;
	printf ("how to display list? 1. Forward 2. Backward");
	scanf("%d", &option);
	switch (option)
	{
	case 1:
	{
		printf("In forward Direction\n");
		NODE* p = head;

		while (p != NULL)
		{
			printf("%d-->", p->data);
			p = p->next;
		}
		printf("\n");
		break;
	}
	case 2:
	{
		printf("In backward Direction\n");
		NODE* p = tail;

		while(p != NULL)
		{
			printf("%d-->", p->data);
			p = p->prev;
		}
		printf("\n");
		break;
	}
	}
}

int main(int argc, char **argv)
{
	int option;

	printf("Doubly linklist\n");

	while(1)
	{
		printf ("Select Option\n");
		printf ("1.Insert\n2.display\n3.Exit\n");
		scanf ("%d", &option);

		switch (option)
		{
		case 1:
		{
			Insert();
			break;
		}
		case 2:
		{
			Display();
			break;
		}
		case 3:
		{
			printf("Good Bye");
			return 0;
			break;
		}
		}
	}

	return 0;
}
