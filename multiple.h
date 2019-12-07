/*
#include <stdio.h>
#include <stdlib.h>
#include "inter_link.h"
#include "stack.h"
*/

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
    LINK zero_link;
    LINK save;
    int buho = 0;   // 0 -> '-'  1-> '+'

    // 계산 값 부호 결정 
    //
    if(num1->d == num2->d) buho = 1;
 
    // 소수점 계산 
    //
    int point = 0;
    num_copy = num1_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3 
    num_copy = num2_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3+4=7
    //printf("%d",point);

    // 점 빼기
    num_copy = num1_int;
    for( ; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);
    num_copy = num2_int;
    for( ; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);

    // 계산/////////////////////////////////////////////////////////////////////
    // num2->d* num1->d .. 해서 계산 후 9보다 크면 다음칸에 올림
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
        num_copy = last_link(input);
        for( ; num_copy->prev != NULL; num_copy = num_copy->prev){
            if(num_copy->d != '0') break;
        }
        //자릿수 추가//////////////////////////////////////////////
        if(zero>0){
            zero_link = char_to_list('0');
            for(int i=1; i<zero; i++){
                insert(zero_link,'0');
            }
            concatenate(zero_link,input);
            input = zero_link;
        } 
        //쓸모없는 0 지우기////////////////////////////////////////
        num_copy = last_link(input);
        while(1){
            if(num_copy->prev == NULL || num_copy->d != '0') break;
            LINK save = num_copy->prev;
            del_link(num_copy);
            num_copy = save;
        }

        ///////////////////////////////////////////////////////////
        //덧셈
        //수는 리버스 되어있음
        //1321 + 432 = 5641
        if(!zero) ans = copy_link(input);
        
        else{
            int alen = count(ans);
            int blen = count(input);
            if(blen>alen){
                num_copy = ans;
                ans = input;
                input = num_copy;
            }
            save = ans;
            num_copy = input;
            now = 0;
            up = 0;
            for(; num_copy != NULL; num_copy = num_copy->next){
                now = num_copy->d-'0' + save->d-'0' +up;
                up = now/10;
                now = now%10;
                save->d = now+'0';
                save = save->next;
            }
            for(; up && save != NULL; save = save->next){
                now = save->d-'0' + up;
                up = now/10;
                now = now%10;
                save->d = now+'0';
            }
            if(up){
                save = last_link(ans);
                insert(save,'1');
            }
        }
        free_all(input);
        zero++; 
    }
    
    // 부호 추가하고 뒤집고 소수점 계산 한 값만큼 소수점 뒤에서부터 카운트
    //
    int anslen = count(ans);
    if(anslen > point){
        num_copy = ans;
        save = ans;
        if(buho) ans = char_to_list('+');
        else ans = char_to_list('-');

        for(; num_copy!=NULL; num_copy = num_copy->next){
            insert(ans,num_copy->d);
        }
        free_all(save);

        num_copy = last_link(ans);
        while(point--) num_copy = num_copy->prev;
        insert(num_copy, '.');
    }
    else{
        num_copy = ans;
        if(buho) ans = char_to_list('+');
        else ans = char_to_list('-');
        save = ans;        
        insert(save,'0'); save = save->next; insert(save,'.'); save = save->next;
        point-=anslen;
        while(point--){
            insert(save,'0');
            save = save->next;
        }
        for(; num_copy!=NULL; num_copy = num_copy->next){
            insert(save,num_copy->d);
        }
    }
    zero_erase(ans);
    free_all(num1);
    free_all(num2);
    free_all(num1_int);
    free_all(num2_int);
    return ans;
}

/*

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
    
    LINK a3 = multiple(a1,a2);
    print_list(a3);
    }
}
*/
