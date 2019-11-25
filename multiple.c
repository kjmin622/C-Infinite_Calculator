#include <stdio.h>
#include<stdlib.h>
#include "inter_link.h"
// 0 1 2 3 4 5 6 7 8
// + 1 3 5 . 3 2 1
// - 5 . 2 1 7 9

LINK multiple(LINK num1, LINK num2){
    // 계산 값 
    //
    LINK ans; 

    // 계산 값 부호 결정 
    //
    if(num1->d == num2->d) ans->d = '+';
    else                   ans->d = '-';

    // 반대로 뒤집기 
    // 123.531+
    // 9712.5-

    LINK num1_last = last_link(num1);  // num1_last : num1의 마지막   //   num2_last : num2의 마지막 
    LINK num2_last = last_link(num2);

    // 소수점 계산 
    //
    int point = 0;
    LINK num_copy = num1_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3
    
    num_copy = num2_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3+4=7
    
    //printf("%d",point);

    // 점 빼기
    // 0 1 2 3 4 5 6 7 8
    // + 1 3 5 . 3 2 1
    // - 5 . 2 1 7 9


    LINK num1_int = copy_link(num1->next);
    

    //print_list(num1_int);
    //print_list(num2_int);

    

    // 계산
    // num2->d* num1->d .. 해서 계산 후 9보다 크거나 같으면 다음칸에 올림
    // num2->next->d* num1-> .. ...위에 계산 한 칸에 +
    // 

    // 다하면 반대로 뒤집기
    //

    // 소수점 계산 한 값만큼 소수점 뒤에서부터 카운트
    //

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

