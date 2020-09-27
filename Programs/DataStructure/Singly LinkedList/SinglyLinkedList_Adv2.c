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

void findMiddleElement_method1(NODE* head)
{
	/* In this method first traverse through the list, find the total number of nodes
	 * After that, traverse again till total number for nodes / 2
	 */
	if (head)
	{
		NODE* ptr = head;
		int noOfNodes = 0, i = 0;
		while(ptr)
		{
			ptr = ptr->next;
			noOfNodes++;
		}

		ptr = head;
		while (i < (noOfNodes / 2))
		{
			ptr = ptr->next;
			i++;
		}

		printf("Middle Element is : %d at node %d\n", ptr->num, i+1);
	}
	else
	{
		printf("Create a list first\n");
	}
}

void findMiddleElement_method2(NODE* head)
{
	if (head)
	{
		NODE* fast = head;
		NODE* slow = head;

		while ((fast->next != NULL) && (fast->next->next != NULL))
		{
			fast = fast->next->next;
			slow = slow->next;
		}

		printf("Middle Element is : %d\n", slow->num);
	}
	else
	{
		printf("Create a list first\n");
	}
}

void findMiddleElement_method3(NODE* head)
{
	if (head)
	{
		int cnt = 0;
		NODE* mid = head;
		NODE* ptr = head;

		while (ptr)
		{
			if (cnt & 1)
			{
				mid = mid->next;
			}
			++cnt;
			ptr = ptr->next;
		}

		printf("Middle Element is : %d\n", mid->num);

	}
	else
	{
		printf("Create a list first\n");
	}
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
		printf ("1.Create a List \n2.Print List\n3.Find Middle Element Method1\n4.Find Middle Element Method2\n5.Find Middle Element Method3\n6.Exit\n");
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
				findMiddleElement_method1(head);
				break;
			}

			case 4:
			{
				findMiddleElement_method2(head);
				break;
			}

			case 5:
			{
				findMiddleElement_method3(head);
				break;
			}

			case 6:
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

	}while (option != 6);

	return 0;
}

