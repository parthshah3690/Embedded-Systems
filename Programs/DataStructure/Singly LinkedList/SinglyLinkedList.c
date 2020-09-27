#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

void insert_into_list(NODE** head)
{
	if (count != 0)
	{
		NODE* newNode;
		NODE* p = *head;

		newNode = (NODE*)malloc(sizeof(NODE));
		printf ("Enter Value To Insert:");
		scanf("%d", &newNode->num);

		while(p->next != NULL)
		{
			p = p->next;
		}
		newNode->next = NULL;
		p->next = newNode;
		count++;
	}
	else
	{
		printf ("Please create List first\n");
	}
}

void insert_into_list_with_key(NODE** head)
{
	if (count != 0)
	{
		NODE* newNode, *q;
		int value;
		newNode = (NODE*)malloc(sizeof(NODE));

		NODE* p = *head;

		printf ("Enter Value To Insert:");
		scanf("%d", &newNode->num);

		printf ("Enter value before insert data");
		scanf("%d", &value);

		if (p != NULL)
		{
			if (p->num == value) //* add at beginning
			{
				newNode->next = p;
				*head = newNode;
			}
			else
			{
				while ((p != NULL) && (p->num != value))
				{
					q = p;
					p = p->next;
				}
				if (p == NULL) //* at at end
				{
					q->next = newNode;
					newNode->next = NULL;
				}
				else if (p->num == value) //* add at middle
				{
					q->next = newNode;
					newNode->next = p;
				}
			}
			count++;
		}
	}
	else
	{
		printf ("Please create List first\n");
	}
}

void delete(NODE* head)
{
	if (count != 0)
	{
		NODE* q;
		NODE* p = head;
		int value;
		printf("Enter Value to delete");
		scanf("%d", &value);

		if (p != NULL)
		{
			if (p->num == value)//* at beginning
			{
				head = p->next;
				free(p);
			}
			else
			{
				while((p != NULL) && (p->num != value))
				{
					q = p;
					p = p->next;
				}
				if (p == NULL) // at end
				{
					q->next = NULL;
				}
				else if(p->num  == value)
				{
					q->next = p->next;
					free(p);
				}
			}
		}
		count--;
	}
	else
	{
		printf ("Please create List first\n");
	}
}

void write_to_file(NODE* head)
{
	NODE* p = head;
	FILE* fp;

	if ((fp = fopen("write_link.txt", "w+")) == NULL)
	{
		printf("Cannot open file\n");
		return;
	}
	printf("Writing to file...\n");
	while(p != NULL)
	{
		fprintf(fp, "%d\n", p->num);
		p = p->next;
	}
	fclose(fp);
}

void read_from_file(NODE* head)
{
	if (count != 0)
	{
		NODE* newNode;
		NODE* p = head;
		int value;

		FILE* fp;
		if ((fp = fopen("read_link.txt", "r+")) == NULL)
		{
			printf("Cannot open file\n");
			return;
		}

		while(p->next != NULL)
		{
			p = p->next;
		}

		while(!feof(fp))
		{
			newNode = (NODE*)malloc(sizeof(NODE));
			fscanf(fp, "%d", &value);
			newNode->num = value;
			newNode->next = NULL;

			p->next = newNode;
			p = p->next;
			count++;
		}
	}
	else
	{
		printf ("Please create List first\n");
	}
}

NODE* reverse_list(NODE* head)
{
	NODE* p = head;
	NODE* newNode = NULL;

	while(p)
	{
		NODE* next = p->next;
		p->next = newNode;
		newNode = p;
		p = next;
	}
	return newNode;
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
		printf("List Is empty");
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
		printf("Select Option From The Menu:\n");
		printf ("1.Create\n2.Insert\n3.Insert With Key\n4.Reverse List\n5.Delete\n6.Print List\n7.Write To File\n8.Read From File\n9.Exit\n");
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
				insert_into_list(&head);
				break;
			}

			case 3:
			{
				insert_into_list_with_key(&head);
				break;
			}

			case 4:
			{
				head = reverse_list(head);
				print_list(head);
				break;
			}
			case 5:
			{
				delete(head);
				print_list(head);
				break;
			}

			case 6:
			{
				print_list(head);
				break;
			}

			case 7:
			{
				write_to_file(head);
				break;
			}

			case 8:
			{
				read_from_file(head);
				break;
			}

			case 9:
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

	}while (option != 9);

	return 0;
}

