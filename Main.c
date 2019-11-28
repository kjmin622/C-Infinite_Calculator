#include <stdio.h>
#include <stdlib.h>
#include "inter_link.h"
#include "stack.h"
#include "multiple.h"
LINK calculator(LINK,LINK,char);



int main(void){
    char done = 1;
    while(done){


        ////////////////////////////////////////////////
        //선언부
        int errorcheck=-301; // 0: +  1: -  2: *  3: /  5: ()  / -301: 연산자 없음 /  -1: error
        Stack num_stack, oper_stack;
        InitStack(&num_stack);
        InitStack(&oper_stack);
        printf("______________________________________\n식을 입력해주세요!!\n ->  ");
        char input; scanf(" %c",&input);

        
        LINK exp_head = char_to_list(input);
        LINK exp = exp_head;
        LINK exp_x;
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
        printf("\n어디보자... ");
        ////////////////////////////////////////////////
        //오류 제거
        //
        //앞 공백 제거
        exp = exp_head;
        while(exp->next != NULL){
            if(exp->d != ' ' && exp->d != '\n') break;
            exp_x = exp->next;
            exp->next->prev = NULL;
            free(exp);
            exp = exp_x;
        }
        exp_head = exp;
        
        //공백 제거
        exp = exp_head->next;
        while(exp!=NULL){
            if(exp->d == ' ' || exp->d == '\n'){
                exp_x = exp->prev;
                del_link(exp);
                exp = exp_x;
            }
            exp = exp->next;
        }
        //맨 앞 글자
        exp = exp_head;

        int number = 1; // 숫자가 있으면 0
        int left_bracket = 0; // 왼괄호
        int right_bracket = 0; // 우괄호
        if(!(exp->d == '(' || exp->d == '-' || (exp->d >= '0' && exp->d <= '9'))) errorcheck = -1;
        if(exp->d>='0' && exp->d <='9') number = 0;


        //중간부분
        exp = exp_head;
        while(exp->next != NULL){
            if(errorcheck == -1) break;
            
            if(number && exp->d >= '0' && exp->d <= '9') number = 0;
            if(exp->d == '(') left_bracket ++;
            if(exp->d == ')') right_bracket ++;
            if(left_bracket < right_bracket) {errorcheck = -1; break;}

            //나오면 안되는 문자
            if(!(exp->d == '+' || exp->d == '-' || exp->d == '/' || exp->d == '*' || 
                        exp->d == '(' || exp->d == ')' || exp->d == '.' ||  (exp->d>='0'&&exp->d<='9'))) {errorcheck = -1; break;}
            
            //연산자 다음에 나오면 안되는 문자
            if(exp->d == '+' || exp->d == '/' || exp->d == '*' || exp->d == '-'){
                if(!(exp->next->d == '(' || (exp->next->d>='0' && exp->next->d<='9'))) {errorcheck = -1; break;}
            }
            if(exp->d == '('){
                if(!(exp->next->d == '-' || (exp->next->d>='0' && exp->next->d<='9'))) {errorcheck = -1; break;}
            }
            if(exp->d == ')'){
                if(exp->next->d >= '0' && exp->next->d <='9') {errorcheck = -1; break;}
            }
        
            exp = exp->next;
        }

        if(exp->prev != NULL){
            if(!(exp->d == '+' || exp->d == '-' || exp->d == '/' || exp->d == '*' || 
                        exp->d == '(' || exp->d == ')' || (exp->d>='0'&&exp->d<='9'))) errorcheck = -1;

            if(!(exp->d == ')' || (exp->d >= '0' && exp->d <= '9'))) errorcheck = -1;
            if(exp->d == ')') right_bracket++;
            if(exp->d >= '0' && exp->d<='9') number = 0;
        }

        if(number) errorcheck = -1;
        if(left_bracket != right_bracket) errorcheck = -1;


        if(errorcheck == -1) {printf("어라.. 식이 이상한 거 같은데요?\n\n"); free_all(exp_head); continue;}
        if(errorcheck == -301) printf("음.. 연산자가 없는거 같기도 하고..");
        if(errorcheck == 0) printf("일단 저걸 더해야 하고..");
        if(errorcheck ==1) printf("저것들은 빼야 할 거 같고..");
        if(errorcheck ==2) printf("얘네는 이렇게 이렇게 곱하고 더해서..");
        if(errorcheck ==3) printf("저걸 저걸로 잘 나눠주면...");
        if(errorcheck ==4) printf("저건 묶어서 생각하고...");
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
            if(exp->prev != NULL && exp->d == ' '){
                LINK prev_link = exp->prev;
                del_link(exp);
                exp = prev_link;
            }

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
            if(exp->next != NULL && exp->d == ')' && exp->next->d == '(') insert(exp,'*');
            else if(exp->d == '('){
                if(exp->next!=NULL && exp->next->d == '-'){ // -(1+2)  ->  0-(1+2)
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

        printf(" 계산하면... ");
        ////////////////////////////////////////////////
        //계산부
        exp = exp_head;
        LINK rational;
        LINK input_link;
        situration = 0;
     
        for(; exp != NULL; exp = exp->next){
            if((exp->d == '.') || (exp->d >= '0' && exp->d <= '9')){ //피연산자 스택 넣기
                if(situration == 0){
                    rational = char_to_list('+');
                    insert(rational, exp->d);
                    input_link = rational->next;
                    situration = 1;
                }
                else{
                    insert(input_link,exp->d);
                    input_link = input_link->next;
                }
                if(exp->next == NULL || (exp->next->d < '0' || exp->next->d > '9') && (exp->next->d != '.')){
                    Push(&num_stack,rational);
                    situration = 0;
                }
            }
            
            if(exp->d == ')'){
                while(Top(&oper_stack)->d != '('){
                    LINK oper = Pop(&oper_stack);
                    LINK p2 = Pop(&num_stack);
                    LINK p1 = Pop(&num_stack);
                    Push(&num_stack,calculator(p1,p2,oper->d));
                    free_all(oper);
                }
                free(Pop(&oper_stack));
            }
            else if(exp->d == '(') Push(&oper_stack,char_to_list('('));

            else if(exp->d == '+' || exp->d == '-'){
                while(!IsEmpty(&oper_stack) && Top(&oper_stack)->d != '('){
                    LINK oper = Pop(&oper_stack);
                    LINK p2 = Pop(&num_stack);
                    LINK p1 = Pop(&num_stack);
                    Push(&num_stack,calculator(p1,p2,oper->d));
                    free_all(oper);
                }
                Push(&oper_stack,char_to_list(exp->d));
            }
            else if(exp->d == '*' || exp->d == '/'){
                while(!IsEmpty(&oper_stack) && Top(&oper_stack)->d != '('
                        && Top(&oper_stack)->d != '+' && Top(&oper_stack)->d != '-'){
                    LINK oper = Pop(&oper_stack);
                    LINK p2 = Pop(&num_stack);
                    LINK p1 = Pop(&num_stack);
                    Push(&num_stack,calculator(p1,p2,oper->d));
                    free_all(oper);
                }
                Push(&oper_stack,char_to_list(exp->d));
            }
                    
        }
        
        while(!IsEmpty(&oper_stack)){
            LINK oper = Pop(&oper_stack);
            if(oper->d == '(') {free(oper); continue;}
            LINK p2 = Pop(&num_stack);
            LINK p1 = Pop(&num_stack);
            Push(&num_stack,calculator(p1,p2,oper->d));
            free_all(oper);
        }
        
        printf("아 끝났다! 답이에요!\n ->  ");
        LINK answer = Pop(&num_stack);
        print_answer(answer);
        ////////////////////////////////////////////////
        //메모리를 아끼자
        free_all(answer);
        free_all(exp_head);
    }
}

LINK calculator(LINK p1, LINK p2, char oper){
    LINK p3;
    if(oper == '+' || oper=='-'){
        if(p1->d + p2->d == '+'+'+' || p1->d + p2->d == '-'+'-'){p3 = copy_link(p1);}// plus(p1,p2);   //부호가 같을 시 플러스
        else {p3 = copy_link(p1);}// minus(p1,p2); // 부호가 다를 시 마이너스
    }

    if(oper == '*') {p3 = multiple(p1,p2);}// multiple(p1,p2); //곱하기 만들어야 함
    if(oper == '/') {p3 = copy_link(p1);}// division(p1,p2); //나누기 만들어야 함
    
    return p3;
}
