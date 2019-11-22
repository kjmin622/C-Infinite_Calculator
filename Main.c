#include <stdio.h>
#include <stdlib.h>
#include "inter_link.h"
#include "stack.h"

LINK calculator(LINK,LINK,char);



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
        print_list(exp_head);
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
        //계산부
        exp = exp_head;
        LINK rational;
        LINK input_link;
        situration = 0;

        for(; exp != NULL; exp = exp->next){
            if(exp->d >= '0' && exp->d <= '9'){ //피연산자 스택 넣기
                if(situration == 0){
                    rational = char_to_list('+');
                    insert(rational, exp->d);
                    input_link = rational;
                    situration = 1;
                }
                else{
                    insert(input_link,exp->d);
                    input_link = input_link->next;
                }
                if(exp->next->d < '0' || exp->next->d > '9'){
                    Push(&num_stack,rational);
                    situration = 0;
                }
            }
            else{
                if(exp->d == ')'){
                    ;
                }
                else if(exp->d == '('){
                    Push(&oper_stack,char_to_list(exp->d));
                }
                else{
                    if(exp->d == '+' || exp->d == '-'){
                        while(!IsEmpty(&oper_stack)){
                            if(Top(&oper_stack)->d == '('){
                                free_all(Pop(&oper_stack));
                                break;
                            }
                            else{
                                LINK p2 = Pop(&num_stack);
                                LINK p1 = Pop(&num_stack);
                                LINK oper = Pop(&oper_stack);
                                LINK p3 = calculator(p1,p2,oper->d);
                                free_all(p2); free_all(p1); free_all(oper);
                                Push(&num_stack,p3);
                            }
                        }
                        Push(&oper_stack,char_to_list(exp->d));
                    }
                    /*
                    else{
                        while(!IsEmpty(&oper_stack) && Top(&oper_stack)->d != '+' && Top(&oper_stack)->d != '-'){
                            if(Top(&oper_stack)->d == '('){
                                free_all(Pop(&oper_stack));
                                break;
                            }
                            else{
                                LINK p2 = Pop(&num_stack);
                                LINK p1 = Pop(&num_stack);
                                LINK oper = Pop(&oper_stack);
                                LINK p3 = calculator(p1,p2,oper->d);
                                free_all(p2); free_all(p1); free_all(oper);
                                Push(&num_stack,p3);
                            }
                        }
                        Push(&oper_stack,char_to_list(exp->d));
                    }
                    */
                }
            }
        }

        while(!IsEmpty(&oper_stack)){
            LINK p2 = Pop(&num_stack);
            LINK p1 = Pop(&num_stack);
            LINK oper = Pop(&oper_stack);
            char operation = oper->d;
            
            Push(&num_stack, calculator(p1,p2,operation));

            free_all(p2); free_all(p1); free_all(oper);
        }

        LINK answer = Pop(&num_stack);
        print_list(answer);
        free(answer);

            
            

        ////////////////////////////////////////////////
        //메모리를 아끼자
        free_all(exp_head);
    }
}

LINK calculator(LINK p1, LINK p2, char oper){
    LINK p3;
    if(oper == '+' || oper=='-'){
        if(p1->d + p2->d == '+'+'+' || p1->d + p2->d == '-'+'-'){p3 = copy_link(p1); printf("+ ");}// plus(p1,p2);   //부호가 같을 시 플러스
        else {p3 = copy_link(p1); printf("- ");}// minus(p1,p2); // 부호가 다를 시 마이너스
    }

    if(oper == '*') {p3 = copy_link(p1); printf("* ");}// multiple(p1,p2); //곱하기 만들어야 함
    if(oper == '/') {p3 = copy_link(p1); printf("/ ");}// division(p1,p2); //나누기 만들어야 함
    
    return p3;
}
