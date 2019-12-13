
typedef char DATA;

struct linked_list {
    DATA d;
    struct linked_list *prev, *next;
};

typedef struct linked_list ELEMENT;
typedef ELEMENT *LINK;



//어떤 함수가 있나요///////////////////////////////////////////////////////////
//
LINK char_to_list(char); // 헤드의 데이터가 char인 헤드 주소 반환
//
unsigned long long count(LINK); // LINK의 길이 반환
//
LINK last_link(LINK); // Linked list의 맨 마지막 주소 반환
//
void print_list(LINK); // Linked list 출력
//
void print_answer(LINK); // Linked list 깔끔하게 출력
//
void zero_erase(LINK);  // 소수점 아래의 쓸모없는 0 제거
//
void concatenate(LINK a, LINK b); // a에 b 붙이기
//
void insert(LINK p1, char x); // p1 뒤에 x 끼워넣기
//
void del_link(LINK p); // p 삭제  *주의 : 헤드 삭제 불가능
//
LINK copy_link(LINK p2); // p2 복사해서 반환
//
char compare(LINK, LINK); // 두 수 비교,  1:a가 더 큼  2:b가 더 큼  3:같음
//
LINK Upzero_fill(LINK, LINK); // 작은 수의 앞자리에 0 채워서 큰 수와 자릿수 맞추기
//
void Downzero_fill(LINK, LINK); // 소수점 자리 0 채워서 맞춰주기
//
void free_all(LINK h); // Linked list 데이터 전부 free
//
///////////////////////////////////////////////////////////////////////////////





LINK char_to_list(char s){
    LINK head;
    head = malloc(sizeof(ELEMENT));
    head->d = s;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

unsigned long long count(LINK head){
    unsigned long long cnt = 0;
    for( ; head != NULL; head = head->next) cnt++;
    return cnt;
}

LINK last_link(LINK head){
    for( ; head->next != NULL; head = head->next);
    return head;
}

void print_list(LINK head){
    if(head == NULL);
    else {printf("%c", head->d); print_list(head->next);}
}

void zero_erase(LINK head){
    head = last_link(head);
    while(head->d!='.' && head->d=='0'){
        LINK store = head->prev;
        del_link(head);
        head = store;
    }
}

void print_answer(LINK head){
    for(; head!=NULL; head = head->next){
        if(head->d == '+') continue;
        if(head->d == '.' && head->next == NULL) break;
        printf("%c",head->d);
    }
}

void concatenate(LINK a, LINK b){
    if(a->next == NULL){
        a->next = b;
        b->prev = a;
    }
    else{
        concatenate(a->next,b);
    }
}

void insert(LINK p1, char x){
    LINK q = char_to_list(x);
    if(p1->next == NULL){
        p1->next = q;
        q->prev = p1;
    }
    else{
        q->next = p1->next;
        p1->next->prev = q;
        p1->next = q;
        q->prev = p1;
    }
}

void del_link(LINK p){
    if(p->next == NULL){
        p->prev->next = NULL;
        free(p);
    }
    else{
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
    }
}

LINK copy_link(LINK p2){
    LINK p1 = char_to_list(p2->d);
    LINK p = p1;
    p2 = p2->next;
    for(; p2!=NULL; p2=p2->next){
        insert(p,p2->d);
        p = p->next;
    }
    return p1;
}

char compare(LINK x, LINK y){
    LINK a = x->next;
    LINK b = y->next;
    while((a!=NULL && b!=NULL) && (a->d!='.' || b->d!='.')){
        if(a->d == '.') return 2;
        if(b->d == '.') return 1;
        a = a->next;
        b = b->next;
    }

    a = x->next;
    b = y->next;
    while(a!=NULL && b!=NULL){
        if(a==NULL) return 2;
        if(b==NULL) return 1;
        if(a->d > b->d) return 1;
        if(a->d < b->d) return 2;
        a = a->next;
        b = b->next;
    }
    return 3;
}

LINK Upzero_fill(LINK x, LINK y){
    LINK a = x;
    LINK b = y;

    unsigned long long alen, blen; alen=blen=0;
    for(; a->d != '.'; a=a->next) alen++;
    for(; b->d != '.'; b=b->next) blen++;

    if(alen == blen) return y;
    
    unsigned long long len = alen - blen;
    LINK zero = char_to_list('0');
    while(len-->0){
        insert(zero,'0');
    }
    concatenate(zero,y);
    return zero;
}

void Downzero_fill(LINK x, LINK y){
    LINK a = last_link(x);
    LINK b = last_link(y);
    for(; a->d != '.'; a=a->prev);
    for(; b->d != '.'; b=b->prev);
    while(a!=NULL || b!=NULL){
        if(a->next != NULL && b->next == NULL) insert(b,'0');
        if(a->next == NULL && b->next != NULL) insert(a,'0');
        a=a->next; b=b->next;
    }
}


void free_all(LINK h){
    if(h == NULL) return;
    free_all(h->next);
    free(h);
}
