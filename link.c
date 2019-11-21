#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef	char DATA;

struct linked_list {
	DATA d;
	struct linked_list *next;
};

typedef	struct linked_list ELEMENT;
typedef	ELEMENT *LINK;


/* List creation using recursion. */
LINK string_to_list(char s[])
{
	LINK head;

	if (s[0] == '\0')	/* base case */
		return NULL;
	else {
		head = malloc(sizeof(ELEMENT));
		head->d = s[0];
		head->next = string_to_list(s + 1);
		return head;
	}
}

/* Count a list iteratively. */
int count(LINK head)
{
	int cnt = 0;
	for ( ; head != NULL; head = head->next)
		cnt++;
	return cnt;
}

/* Print a list recursively. */
void print_list(LINK head)
{
	if (head == NULL)
		printf("NULL");
	else {
		printf("%c --> ", head->d);
		print_list(head->next);
	}
}

/* Concatenate list a and b with a as head. */
void concatenate(LINK a, LINK b)
{
	assert(a != NULL);
	if (a->next == NULL)
		a->next = b;
	else
		concatenate(a->next, b);
}

/* Inserting an element in a linked list. */
void insert(LINK p1, LINK p2, LINK q)
{
	assert(p1->next == p2);
	p1->next = q;
	q->next = p2;
}

// p 다음꺼 delete
void delete(LINK p){
    LINK q = p->next;
    if(p->next->next == NULL)
        p->next = NULL;
    else
        p->next = p->next->next;
    
    free(q);
}

void free_all(LINK h){
    LINK p = h->next;
    free(h);
    if(p != NULL) free_all(p);
    else free(p);
}

int main()
{
	LINK h;
	h = string_to_list("ABC");
        delete(h->next);
	printf("The list h is\n");
	print_list(h);
	printf("\nThis list has %d elements.\n", count(h));

	/* insert new LINK(X) between h and h->next */
	insert(h, h->next, string_to_list("X"));
	printf("The list h is(after insert 'X')\n");
	print_list(h);


	LINK a, b;
	a = string_to_list("STAR");
	b = string_to_list("BUCKS");
	printf("\n\nThe list a is\n");
	print_list(a);
	printf("\nThe list b is\n");
	print_list(b);

	concatenate(a, b);
	
	printf("\nThe list a is(after concat)\n");
	print_list(a);
	printf("\nThe list b is(after concat)\n");
	print_list(b);
	printf("\n");

        free_all(h);
        print_list(h);

	return 0;
}
