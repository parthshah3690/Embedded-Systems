#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE
{
	int number;
	struct _NODE* next;
}NODE;


NODE* Push(NODE* top)
{
	int count, i;
	printf ("Enter number of elements to push");
	scanf ("%d", &count);

	for (i = 0; i < count; i++)
	{
		NODE* tmp = (NODE*)malloc(sizeof(NODE));
		scanf ("%d", &tmp->number);
		if (top == NULL)
		{
			tmp->next = NULL;
			top = tmp;
		}
		else
		{
			tmp->next = top;
			top = tmp;
		}
	}
	return top;
}

NODE* Push_with_key(NODE* top)
{
	int number;
	NODE* p = top;
	if (top == NULL)
	{
		printf ("List is empty\n");
	}
	else
	{
		NODE* temp =(NODE*)malloc(sizeof(NODE));

		printf("Enter Value to insert:");
		scanf("%d", &temp->number);

		printf ("Enter Key");
		scanf("%d",&number);

		if (p->number == number) // at begin
		{
			temp->next = p->next;
			p->next = temp;
		}
		else
		{
			NODE* prev;
			while ((p != NULL) && (p->number != number))
			{
				prev = p;
				p = p->next;
			}
			if (p == NULL) //* at end
			{
				temp->next = NULL;
				prev->next = temp;
			}
			else              //* middle
			{
				temp->next = p->next;
				p->next = temp;
			}
		}
	}
	return top;
}

NODE* Pop(NODE* top)
{
	if (top == NULL)
	{
		printf ("List is empty\n");
	}
	else
	{
		NODE* tmp = top;
		top = tmp->next;
		free(tmp);
	}
	return top;
}

NODE* Pop_value(NODE* top)
{
	int number;
	NODE* p = top;
	if (top == NULL)
	{
		printf ("List is empty\n");
	}
	else
	{
		printf ("Enter value to delete:");
		scanf("%d",&number);

		if (p->number == number) //* first element
		{
			top = p->next;
			free(p);
		}
		else
		{
			NODE* prev;
			while ((p != NULL) && (p->number != number))
			{
				prev = p;
				p = p->next;
			}
			if (p == NULL)
			{
				printf ("Number is not in the list");
			}
			else
			{
				prev->next = p->next;
				free(p);
			}
		}

	}
	return top;
}

void Display(NODE* top)
{
	NODE* p = top;
	while (p != NULL)
	{
		printf ("%d-->", p->number);
		p = p->next;
	}
	printf("\n");
}

void FreeMemory(NODE* top)
{
	while(top != NULL)
	{
		NODE* tmp = top;
		top = tmp->next;
		free(tmp);
	}

	printf ("Free Memory....Done\n");
}


int main(int argc, char **argv)
{
	NODE* top = NULL;
	printf ("Stack Using LinkList\n");
	int option;

	while(1)
	{
		printf("Select Option From Below\n");
		printf("1.Push\n2.Pop\n3.Push with key\n4.Pop value\n5.Display\n6.Quit\n");
		scanf ("%d", &option);

		switch(option)
		{
		case 1:
		{
			top = Push(top);
			break;
		}

		case 2:
		{
			top = Pop(top);
			break;
		}

		case 3:
		{
			top = Push_with_key(top);
			break;
		}

		case 4:
		{
			top = Pop_value(top);
			break;
		}

		case 5:
		{
			Display(top);
			break;
		}

		case 6:
		{
			FreeMemory(top);
			printf ("Good Bye!\n");
			return 0;
			break;
		}
		}
	}
	return 0;
}
