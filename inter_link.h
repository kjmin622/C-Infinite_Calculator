
typedef char DATA;

struct linked_list {
    DATA d;
    struct linked_list *prev, *next;
};

typedef struct linked_list ELEMENT;
typedef ELEMENT *LINK;


LINK char_to_list(char s){
    LINK head;
    head = malloc(sizeof(ELEMENT));
    head->d = s;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

int count(LINK head){
    int cnt = 0;
    for( ; head != NULL; head = head->next) cnt++;
    return cnt;
}

LINK last_link(LINK head){
    for( ; head->next != NULL; head = head->next);
    return head;
}

void print_list(LINK head){
    if(head == NULL) printf(" NULL\n");
    else {printf("%c", head->d); print_list(head->next);}
}

void zero_erase(LINK head){
    head = last_link(head);
    for(; head->d!='.';){
        if(head->d != '0') break;
        
        head->prev->next = NULL;
        LINK store = head->prev;
        free(head);
        head = store;
    }
}

void print_answer(LINK head){
    for(; head!=NULL; head = head->next){
        if(head->d == '+') continue;
        if(head->d == '.' && head->next == NULL) break;
        printf("%c",head->d);
    }
    printf("\n\n");
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

void free_all(LINK h){
    if(h == NULL) return;
    free_all(h->next);
    free(h);
}
