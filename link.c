#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef	char	DATA;

struct linked_list {
	DATA *d;
	struct linked_list *next;
};

typedef	struct linked_list ELEMENT;
typedef	ELEMENT *LINK;


/////////////////////////////////////////////////////////
//s라는 문자열로 생성된 linked list 반환
LINK string_to_list(char s[]) {
	LINK head;
	if (s[0] == '\0')	/* base case */
		return NULL;
	else {
		head = malloc(sizeof(ELEMENT));
		head->d = s;
		head->next = NULL;
		return head;
	}
}


////////////////////////////////////////////////////////
//linked list의 길이 반환
int count(LINK head)
{
	if (head == NULL)
		return 0;
	else
		return (1 + count(head->next));
}

////////////////////////////////////////////////////////
//linked list의 값 출력
void print_list(LINK head)
{
	if (head == NULL)
		printf("NULL");
	else {
		printf("%s --> ", head->d);
		print_list(head->next);
	}
}

////////////////////////////////////////////////////////
//linked list의 인덱스 위치 문자열 반환
char *index_find(LINK head, int index){
    if(!index) return head->d;
    else return index_find(head->next, index-1);
}


////////////////////////////////////////////////////////
//a에 b를 연결
void concatenate(LINK a, LINK b)
{
	assert(a != NULL);
	if (a->next == NULL)
		a->next = b;
	else
		concatenate(a->next, b);
}

///////////////////////////////////////////////////////
//linked list의 index자리 다음에 q 인설트 ( -1 : 맨 앞, -2 : 맨 뒤)  헤드 반환
LINK insert(LINK head, char *q, int index)
{
    if(index == -1){
        LINK p1 = string_to_list(q);
        p1->next = head;
        return p1;
    }

    if(index == -2) index = count(head)-1;
    LINK p1 = head;
    while(index--){
        p1 = p1->next;
    }

    if(p1->next == NULL){
        LINK p2 = string_to_list(q);
        p1->next = p2;
    }
    else{
        LINK p3 = p1->next;
        LINK p2 = string_to_list(q);
        p1->next = p2;
        p2->next = p3;
    }
    return head;
}

///////////////////////////////////////////////////////
//linked list 삭제
void delete(LINK head){
    if(head == NULL) return;
    else{
        LINK next_head = head->next;
        free(head);
        delete(next_head);
    }
}

int main()
{
	LINK h;
	h = string_to_list("ABC");
        h = insert(h,"fds",0);
        h = insert(h,"abc",-1);
        h = insert(h,"fcd",-2);
        print_list(h);
        printf("\n%s\n",index_find(h,1));
        
        delete(h);
	return 0;
}
