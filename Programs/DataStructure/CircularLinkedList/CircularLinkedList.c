#include <stdio.h>
#include <stdlib.h>

int count = 0;

typedef struct _NODE
{
	int num;
	struct _NODE* next;
}NODE;

NODE* CreateList(NODE* head)
{
	NODE* p;
	int number, i;

	if (count == 0)
	{
		printf ("Enter How many Elements:");
		scanf ("%d", &number);

		for (i = 0; i < number; i++)
		{
			if (i == 0)
			{
				head = (NODE*)malloc(sizeof(NODE));
				p = head;
			}
			else
			{
				p->next =  (NODE*)malloc(sizeof(NODE));
				p = p->next;
			}
			scanf("%d", &p->num);
			count++;
		}
		p->next = head;
	}
	else
	{
		printf ("Already Created\n");
	}
	return head;
}

NODE* Insert_at_begin(NODE* head)
{
	if (count != 0)
	{
		NODE* q = head;
		NODE* p = head;
		NODE* newNode = (NODE*)malloc(sizeof(NODE));

		printf ("Enter value to insert at begin:");
		scanf ("%d", &newNode->num);

		newNode->next = head;
		head = newNode;

		do
		{
			p = p->next;
		}while(p->next != q);

		p->next = head;
		count++;
	}
	else
	{
		printf("List is empty\n");
	}

	return head;
}

void Insert_at_end(NODE* head)
{
	if (count != 0)
	{
		NODE* q = head;
		NODE* p = head;
		NODE* newNode = (NODE*)malloc(sizeof(NODE));

		printf ("Enter value to insert at end:");
		scanf ("%d", &newNode->num);

		do
		{
			p = p->next;
		}while(p->next != q);

		newNode->next = p->next;
		p->next = newNode;
		count++;
	}
	else
	{
		printf("List is empty\n");
	}
}

NODE* Insert_with_key(NODE* head)
{
	if (count != 0)
	{
		int number;
		NODE* q = head;
		NODE* prev;
		NODE* p = head;
		NODE* newNode = (NODE*)malloc(sizeof(NODE));
		printf ("Enter value to insert:");
		scanf ("%d", &newNode->num);

		printf ("Insert before key:");
		scanf ("%d", &number);

		if (p->num == number) //* at begin
		{
			newNode->next = head;
			head = newNode;

			do
			{
				p = p->next;
			}while(p->next != q);

			p->next = head;
			count++;
		}
		else
		{
			while ((p->next != q) && (p->num != number))
			{
				prev = p;
				p = p->next;
			}
			if (p->next == q) //* at end and at middle
			{
				newNode->next = p->next;
				p->next = newNode;
				count++;
			}
			else           // * middle
			{
				newNode->next = prev->next;
				prev->next = newNode;
				count++;
			}
		}
	}
	else
	{
		printf ("List is empty\n\n");
	}
	return head;
}

NODE* delete(NODE* head)
{
	int number;
	NODE* p = head;
	NODE* q = head;
	NODE* prev;
	printf ("Enter value to delete:");
	scanf ("%d", &number);

	if (p->num == number)
	{
		head = p->next;
		free(p);
		p = head;

		do
		{
			p = p->next;
		}while(p->next != q);

		p->next = head;
	}
	else
	{
		while((p->next != q) && (p->num != number))
		{
			prev = p;
			p = p->next;
		}
		if (p->next == q)
		{
			NODE* tmp;
			tmp = prev;
			free(p);
			p = tmp;
			p->next = head;
		}
		else
		{
			prev->next = p->next;
			free(p);
		}
	}
	return head;
}

void reverse(NODE** headRef)
{
	NODE* result = NULL;
	NODE* current = *headRef;

	do
	{
		NODE* next = current->next; // tricky: note the next node
		current->next = result; // move the node onto the result
		result = current;
		current = next;
		if (current == *headRef)
		{
		  break;
		}
   }while(current != (*headRef));
	(*headRef)->next = result;
	*headRef = result;
}


void Display(NODE* head)
{
	if (count != 0)
	{
		NODE *p;
		p = head;
		do
		{
			printf ("%d-->", p->num);
			p = p->next;
		}while(p != head);
		printf("\n");
	}
	else
	{
		printf ("List is Empty\n\n");
	}
}

void Freememory(NODE* head)
{
	NODE* p = head;
	NODE* q = head;
	NODE* tmp;
	printf ("Freeing memory.....done\n");
	do
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}while (p != q);
}

int main(int argc, char **argv)
{
	NODE* head = NULL;
	int option;
	while (1)
	{
		printf ("Select Option\n");
		printf ("1.Create\n2.Insert at begin\n3.Insert at end\n4.delete\n5.reverse\n6.display\n7.Insert With key\n8.Exit\n");
		scanf ("%d", &option);

		switch(option)
		{
		case 1:
		{
			head = CreateList(head);
			break;
		}
		case 2:
		{
			head = Insert_at_begin(head);
			break;
		}
		case 3:
		{
			Insert_at_end(head);
			break;
		}
		case 4:
		{
			head = delete(head);
			break;
		}
		case 5:
		{
			reverse(&head);
			break;
		}
		case 6:
		{
			Display(head);
			break;
		}
		case 7:
		{
			head = Insert_with_key(head);
			break;
		}
		case 8:
		{
			Freememory(head);
			printf ("Good bye!");
			return 0;
			break;
		}
		}
	}
	return 0;
}
