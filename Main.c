#include <stdio.h>
#include <stdlib.h>
#include "inter_link.h"
#include "stack.h"
int main(void){
    char done = 1;
    while(done){


        ////////////////////////////////////////////////
        //선언부
        Stack num_stack, oper_stack;
        InitStack(&num_stack);
        InitStack(&oper_stack);
        
        char input; scanf("%c",&input);

        LINK exp_head = char_to_list(input);
        LINK exp = exp_head;


        ////////////////////////////////////////////////
        //입력부
        while(scanf("%c",&input)){
            if(input == '\n') break;
            LINK p = char_to_list(input);
            exp->next = p;
            p->prev = exp;
            exp = p;
        }
        
        ////////////////////////////////////////////////
        //수정부
        if(exp_head->next != NULL && exp_head->d == '-'){ //맨 앞 - 나오는 경우
            LINK minus = char_to_list('0');
            concatenate(minus, exp_head);
            exp_head = minus;
        }

        exp = exp_head;
        int situration = 0; // 0 -> 소수점 안만남  1-> 소수점 만남
        for(; exp!=NULL; exp=exp->next){
            if((exp->d >='0' && exp->d <='9') || exp->d == '.'){ //피연산자일때
                if(exp->next != NULL && exp->next->d == '('){ // 13(1+2)  ->  13*(1+2)
                    insert(exp,'*'); 
                }
                if(exp->d == '.'){
                    situration = 1;
                }
                if(exp->next != NULL && (exp->next->d <'0' || exp->next->d >'9') && exp->next->d != '.'){
                    if(situration == 0){
                        insert(exp,'.');
                        exp=exp->next;
                    }
                    else situration = 0;
                }
            }
            else if(exp->d == '('){
                if(exp->next->d == '-'){ // -(1+2)  ->  0-(1+2)
                    insert(exp,'0');
                }
            }
        }
        LINK exp_last = last_link(exp_head);
        exp = exp_last;
        if(situration == 0 && exp->d>='0' && exp->d<='9'){
            insert(exp,'.');
        }


        ////////////////////////////////////////////////
        // 중간 테스트
        Push(&num_stack,exp_head);
        print_list(Pop(&num_stack));

        ////////////////////////////////////////////////
        //계산부
        exp = exp_head;
        LINK rational;
        situration = 0; // 0:연산자 입력 받는중   1: 피연산자 입력 받는중

        for(; exp != NULL; exp = exp->next){
            if(exp->d >= '0' && exp->d <= '9'){
                
            }
            else{
                printf("#");
            }
        }
        printf("\n");

        ////////////////////////////////////////////////
        //메모리를 아끼자
        free_all(exp_head);
    }
}
