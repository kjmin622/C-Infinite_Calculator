#include <stdio.h>
#include <stdlib.h>
#include "inter_link.h"
#include "stack.h"

// 0 1 2 3 4 5 6 7 8
// + 1 3 5 . 3 2 1
// - 5 . 2 1 7 9

LINK multiple(LINK num1, LINK num2){
    // 계산 값 
    // 선언부
    LINK ans; 
    LINK num_copy;
    LINK num1_last = last_link(num1); // num1_last : num1의 마지막   //   num2_last : num2의 마지막 
    LINK num2_last = last_link(num2);
    LINK num1_int = copy_link(num1->next);
    LINK num2_int = copy_link(num2->next);
    LINK mul1;
    LINK mul2;
    LINK input;
    LINK num_copy_copy;
    Stack stack;

    // 계산 값 부호 결정 
    //
    if(num1->d == num2->d) ans->d = '+';
    else                   ans->d = '-';
 
    // 소수점 계산 
    //
    int point = 0;
    num_copy = num1_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3 
    num_copy = num2_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3+4=7
    //printf("%d",point);

    // 점 빼기
    // 0 1 2 3 4 5 6 7 8
    // + 1 3 5 . 3 2 1
    // - 5 . 2 1 7 9
    
    num_copy = num1_int;
    for( ; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);
    num_copy = num2_int;
    for( ; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);

    // 계산
    // num2->d* num1->d .. 해서 계산 후 9보다 크거나 같으면 다음칸에 올림
    // num2->next->d* num1-> .. ...위에 계산 한 칸에 +
    // 
    mul1 = last_link(num1_int);
    int zero = 0;
    for(; mul1 != NULL; mul1 = mul1->prev){
        mul2 = last_link(num2_int);
        int now = (mul1->d-'0') * (mul2->d-'0'); 
        int up = now/10;
        now %=10;
        input = char_to_list(now + '0');
        num_copy = input;
        mul2 = mul2->prev;
        for(; mul2 != NULL; mul2 = mul2->prev){
            now = (mul1->d-'0') * (mul2->d-'0') + up;
            up = now/10;
            now %= 10;
            insert(num_copy, now + '0');
            num_copy = num_copy->next;
        }
        if(up != 0) insert(num_copy, up+'0');
        
        num_copy = char_to_list('+');
        num_copy_copy = num_copy;
        mul2 = last_link(input);
        int check = 1; 
        for( ; mul2!=NULL; mul2 = mul2->prev){
            if(mul2->prev == NULL) check = 0;
            if(check){
                if(mul2->d == '0') continue;
                else check = 0;
            }
            insert(num_copy_copy, mul2->d);
            num_copy_copy = num_copy_copy->next;
        }
        for(int i=0; i<zero; i++){
            insert(num_copy_copy, '0');
            num_copy_copy = num_copy_copy -> next;
        }
        insert(num_copy_copy, '.');
        free(input);

        //Push(&stack, num_copy); 스택에 넣어야 함
        zero ++;
    }
    
    // 소수점 계산 한 값만큼 소수점 뒤에서부터 카운트
    //
    
    free_all(num1_int);
    free_all(num2_int);
    return ans;
}

int main(){
    LINK a1, a2;
    char input;

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
    
    LINK a3 = multiple(a1,a2);
}

