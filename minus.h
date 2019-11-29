
int compare(LINK, LINK); // 두 수 비교,  1:a가 더 큼  2:b가 더 큼  3:같음
LINK Upzero_fill(LINK, LINK); // 작은 수의 앞자리에 큰 수와 자릿수 맞추기 0채워서
void Downzero_fill(LINK, LINK); // 소수점 자리 맞춰주기


LINK minus(LINK a, LINK b){
    
    /////////////////////////////////////////////////////////////
    //선언부
    LINK ans;
    LINK num_copy;
    LINK num1;
    LINK num2;
    int buho;
    int big_num;
    int point_count = 0;
    int now = 0;
    int down = 0;

    /////////////////////////////////////////////////////////////
    //절대값이 큰 수가 a로 가도록 및 혹시 답이 0이니?
    big_num = compare(a,b);

    if(big_num == 3){ // 둘의 절대값이 같을 때
        ans = char_to_list('+');
        insert(ans,'.');
        insert(ans,'0');
        free_all(a); free_all(b);
        return ans;
    }
    
    if(big_num == 2){ // b가 더 크면 b가 a로 이동
        num_copy = a;
        a = b;
        b = num_copy;
    }
    /////////////////////////////////////////////////////////////
    //부호는 a의 부호를 따라가도록
    buho = a->d == '+' ? 1 : 0;  // +면 1, -면 0

    /////////////////////////////////////////////////////////////
    //숫자 부호 없애고 절대값으로
    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b);
    
    /////////////////////////////////////////////////////////////
    //소수점 위 맞추기
    num2 = Upzero_fill(num1,num2);

    ////////////////////////////////////////////////////////////
    //소수점 아래 맞추기
    Downzero_fill(num1,num2);

    ////////////////////////////////////////////////////////////
    //소수점 자릿수 세기 및 제거
    a = last_link(num1);
    b = num2;
    for(; a->d != '.'; a=a->prev) point_count++; del_link(a);
    for(; b->d != '.'; b=b->next); del_link(b);

    ///////////////////////////////////////////////////////////
    //계산
    a = last_link(num1);
    b = last_link(num2);

    while(a!=NULL){
        int number1 = a->d-'0';
        int number2 = b->d-'0';
        int check = 0;
        if(number2-down > number1) {number1 += 10; check = 1;};
        now = number1 - number2 + down;
        down = check ? -1 : 0;
        a->d = now + '0';
        a = a->prev;
        b = b->prev;
    }
    
    ans = copy_link(num1);
    free_all(num1); free_all(num2);
    ////////////////////////////////////////////////////////////
    //점 붙이기
    a = last_link(ans);
    while(point_count--) a = a->prev;
    insert(a,'.');
    
    ////////////////////////////////////////////////////////////
    //뒤 0 없애기
    a = last_link(ans);
    while(a->d != '.' && a->d == '0'){
        LINK tmp = a->prev;
        del_link(a);
        a=tmp;
    }
    
    ///////////////////////////////////////////////////////////
    //부호 붙이기
    a = ans;
    ans = char_to_list(buho ? '+' : '-');
    concatenate(ans,a);

    ///////////////////////////////////////////////////////////
    //앞 0 없애기
    a = ans->next;
    for(; a->next->d != '.' && a->d == '0'; a=a->next) del_link(ans->next);


    return ans;
}

int compare(LINK x, LINK y){
    LINK a = x->next;
    LINK b = y->next;
    while(a->d!='.' || b->d!='.'){
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

    int alen, blen; alen=blen=0;
    for(; a->d != '.'; a=a->next) alen++;
    for(; b->d != '.'; b=b->next) blen++;

    if(alen == blen) return y;
    
    int len = alen - blen;
    LINK zero = char_to_list('0');
    for(int i=1; i<len; i++){
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


/*
//test
int main(){
    LINK a1, a2;
    char input;

    while(1){

    scanf(" %c",&input);
    a1 = char_to_list(input);
    LINK a_input = a1;
    while(scanf("%c",&input)){
        if(input == '\n') break;
        insert(a_input,input);
        a_input = a_input->next;
    }

    scanf(" %c",&input);
    a2 = char_to_list(input);
    a_input = a2;
    while(scanf("%c",&input)){
        if(input == '\n') break;
        insert(a_input,input);
        a_input = a_input->next;
    }
    
    LINK a3 =minus(a1,a2);
    print_list(a3); printf("\n");
    }
}
*/
