#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

static int count = 0;

typedef struct _NODE
{
	int num;
	struct _NODE* next;
}NODE;

void create_list(NODE** head)
{
	if (count == 0)
	{
		NODE *p;
		int number, i;

		printf("Enter How many Elements to add:");
		scanf("%d", &number);

		printf ("Enter One by one %d elements", number);

		for (i = 0; i< number; i++)
		{
			if (i == 0)
			{
				*head = (NODE*) malloc(sizeof(NODE));
				p = *head;
			}
			else
			{
				p->next = (NODE*) malloc(sizeof(NODE));
				p = p->next;
			}
			scanf("%d", &p->num);
			count++;
		}
		p->next = NULL;
	}
	else
	{
		count = 0;
		printf ("Deleting Existing List Deleting...\n");
		NODE* p = *head;
		int number, i;

		while (p != NULL)
		{
			*head = p->next;
			free (p);
			p = *head;
		}
		printf("Enter How many Elements to add:");
		scanf("%d", &number);

		printf ("Enter One by one %d elements", number);

		for (i = 0; i< number; i++)
		{
			if (i == 0)
			{
				*head = (NODE*) malloc(sizeof(NODE));
				p = *head;
			}
			else
			{
				p->next = (NODE*) malloc(sizeof(NODE));
				p = p->next;
			}
			scanf("%d", &p->num);
			count++;
		}
		p->next = NULL;
	}
}

void print_list(NODE *head)
{
	NODE *p = head;
	int i = 1;

	if (count != 0)
	{
		printf ("List Contains:\n");
		while(p != NULL)
		{
			printf("Node %d :%d\n", i++, p->num);
			p = p->next;
		}
	}
	else
	{
		printf("List Is empty\n");
	}
}

void Free_List(NODE* head)
{
	NODE* p = head;

	while(p != NULL)
	{
		head = p->next;
		free(p);
		p = head;
	}
	printf ("Freed Memory\n");
}

void removeLoop(NODE* node, NODE* head)
{
	NODE* ptr1 = head;
	NODE* ptr2;

	while (1)
	{
		ptr2 = node;
		while (ptr2->next != node && ptr2->next != ptr1)
		{
			ptr2 = ptr2->next;
		}

		if (ptr2->next == ptr1)
			break;

		ptr1 = ptr1->next;
	}

	ptr2->next = NULL;
}

void isListCircular(NODE* head)
{
	NODE* fast = head;
	NODE* slow = head;

	if (head == NULL)
	{
		printf("List is not circular\n");
		return;
	}

	while(fast != NULL && fast->next  != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast)
		{
			printf("List is circular\n");
			removeLoop(slow, head);
			return;
		}
	}

	printf("List is not circular\n");
}

int main(int argc, char **argv)
{
	NODE* head = NULL;
	int option;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Welcome!\n");
	printf("Current Time is : %d-%d-%d %d:%d:%d\n", tm.tm_mday , tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

	do
	{
		printf("****************************\n");
		printf("Select Option From The Menu:\n");
		printf ("1.Create a List \n2.Print List\n3.Find If List is circular\n4.Exit\n");
		scanf ("%d", &option);

		switch (option)
		{
			case 1:
			{
				create_list(&head);
				break;
			}

			case 2:
			{
				print_list(head);
				break;
			}

			case 3:
			{
				isListCircular(head);
				break;
			}

			case 4:
			{
				Free_List(head);
				printf("Good Bye!, See U Again\n");
				break;
			}

			default:
			{
				printf("Select Correct Option From Menu");
				break;
			}
		}

	}while (option != 4);

	return 0;
}
