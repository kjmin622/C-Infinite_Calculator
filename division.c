#include<stdio.h>
#include<stdlib.h>
#include "inter_link.h"

LINK division(LINK a, LINK b){  // a//b
    //선언부////////////////////////////////////////////////////
    int comp;
    int buho; // +이면 1, -이면 0:

    LINK num1;
    LINK num2;
    LINK num3;
    LINK num0;


    //b가 0인지 확인////////////////////////////////////////////
    if(b->next->d=='0' && b->next->next->d=='.') {
        free_all(a); free_all(b);
        return char_to_list('e');   //에러 반환
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
    num0 = char_to_list(num1->d);
    a = num2->next;
    b = num0;
    num3 = num1->next;
    for(; a!=NULL; a=a->next){
        insert(b,num3->d);
        b = b->next;             // num0의 현재 읽기 위치
        num3 = num3->next;       // num1의 불러오기 위치
    }
    
    if(num0->d < num2->d || compare(num0, num2)==2){
        insert(b,num3->d);
        b = b->next;
        num3 = num3->next;
    }

    //계산//////////////////////////////////////////////////////


    //다듬기////////////////////////////////////////////////////


    return num1;
}



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

