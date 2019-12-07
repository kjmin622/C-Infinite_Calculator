
LINK plus(LINK a, LINK b){
    
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
    int up = 0;

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
    //올림 대비 0 한개씩 더 추가
    a = num1; num1 = char_to_list('0'); concatenate(num1, a);
    a = num2; num2 = char_to_list('0'); concatenate(num2, a);

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

        now = number1 + number2 + up;
        
        up = now/10;
        a->d = now%10 + '0';
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
    zero_erase(ans);
    
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

