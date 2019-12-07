
LINK division_minus(LINK, LINK);
int division_compare(LINK, LINK);

LINK division(LINK a, LINK b){  // a//b
    //선언부////////////////////////////////////////////////////
    int comp;
    int buho; // +이면 1, -이면 0:

    LINK num1;
    LINK num2;
    LINK num3;
    LINK num0;
    LINK answer;
    
    
    //b가 0인지 확인////////////////////////////////////////////
    if(b->next->d=='0' && b->next->next->d=='.') {
        LINK ans = char_to_list('+'); insert(ans,'.'); insert(ans,'0');
        free_all(a); free_all(b);
        return ans;  //b가 0이면 0 반환
    }

    //a보다 b가 더 큰지 확인////////////////////////////////////
    comp = compare(a,b);
    if(comp == 2){
        LINK ans = char_to_list('+'); insert(ans,'.'); insert(ans,'0');
        free_all(a); free_all(b);
        return ans;   //b가 더 크면 0 반환
    }

    //부호 연산 및 부호 제거////////////////////////////////////
    buho = a->d == b->d ? 1 : 0;

    if(comp == 3){
        LINK ans = char_to_list(buho?'+':'-'); insert(ans,'.'); insert(ans,'1');
        free_all(a); free_all(b);
        return ans;  //a와 b가 같으면 부호에 따른 1 반환
    }
    
    num1 = a->next; num2 = b->next;
    free(a); free(b);

    //소수점 제거///////////////////////////////////////////////
    Downzero_fill(num1,num2);
    a=num1; for(; a->d != '.'; a=a->next); del_link(a);
    a=num2; for(; a->d != '.'; a=a->next); del_link(a);


    //num0 생성////////////////////////////////////////////////
    //
    
    num0 = char_to_list(num1->d);
    a = num2->next;
    b = num0;
    num3 = num1->next;
    for(; a!=NULL; a=a->next){
        insert(b,num3->d);
        b = b->next;             // num0의 현재 읽기 위치
        num3 = num3->next;       // num1의 불러오기 위치
    }

    //계산//////////////////////////////////////////////////////
    // num0 / num2
    // num1의 아직 적용안된 맨 처음 위치는 num3
    
    answer = char_to_list(buho ? '+' : '-');
    b = answer;

    while(1){
        int input = 0;
        while(division_compare(num0,num2) != 2){ 
            input ++;
            num0 = division_minus(num0,num2);
        }

        insert(b,input+'0');
        b=b->next;
        if(num3 != NULL){
            concatenate(num0,char_to_list(num3->d));
            num3 = num3->next;
        }
        else{
            break;
        }
    }
    
    //메모리 해제/////////////////////////////////////////////// 
    free_all(num0);
    free_all(num1);
    free_all(num2);

    //다듬기////////////////////////////////////////////////////
    a = answer->next;
    while(a->next != NULL && a->d == '0'){
        b = a->next;
        del_link(a);
        a = b;
    }
    for(;a->next!=NULL;a=a->next);
    insert(a,'.');

    return answer;
}

LINK division_minus(LINK a, LINK b){
    int alen = count(a);
    int blen = count(b);
    int len = alen-blen;

    if(len != 0){
        LINK zero = char_to_list('0');
        len --;
        for(int i=0; i<len; i++){
            insert(zero,'0');
        }
        concatenate(zero,b);
        b = zero;
    }
    LINK x = last_link(a);
    LINK y = last_link(b);
    
    int now; int down = 0;
    
    while(x!=NULL){
        int num1 = x->d -'0';
        int num2 = y->d -'0';
        now = num1 - num2 - down;
        down = 0;
        if(now < 0) {now += 10; down = 1;}
        
        x->d = now+'0';
        x = x->prev;
        y = y->prev;
    }

    for(; a->next != NULL && a->d == '0'; ){
        x = a->next;
        a->next->prev = NULL;
        free(a);
        a = x;
    }
    return a;
}

int division_compare(LINK a, LINK b){
    
    int alen = count(a);
    int blen = count(b);
    if(alen > blen) return 1;
    if(alen < blen) return 2;

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


/*
//테스트
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
    print_list(division(a1,a2));
    }
}
*/
