#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "inter_link.h"
#include "stack.h"
#include "multiple.h"
#include "minus.h"
#include "plus.h"
#include "division.h"

LINK calculator(LINK,LINK,char);
void print_help();


int main(void){
    printf("\n______________________________________\n\n물어볼 게 있으시면 w를 입력해주세요!\n");
    printf("계산기를 종료하고 싶으시면 q를 입력해주세요!\n");
    while(1){


        ////////////////////////////////////////////////
        //선언부

        // 앞으로 에러를 체크해 줄 겸, 귀여운 텍스트를 만들어 줄 변수
        char errorcheck=-31; // 0: +  1: -  2: *  3: /  5: ()  / -31: 연산자 없음 /  -1: error

        // 숫자 스택, 연산자 스택
        Stack num_stack, oper_stack;
        InitStack(&num_stack);
        InitStack(&oper_stack);

        ///////////////////////////////////////////////
        //입력부

        printf("______________________________________\n식을 입력해주세요!!\n ->  ");
    
        //input에 입력을 받고 리스트에 넣는다.
        char input; scanf(" %c",&input);
        if(input == 'w') {print_help(); continue;}  // w를 받으면 도움말 함수 호출
        if(input == 'q') break; // q를 받으면 코드 종료
        
        //식 링크드리스트 생성
        LINK exp_head = char_to_list(input);
        LINK exp = exp_head;
        LINK exp_x;
        
        //두번째 글자부터 입력 및 링크드리스트 넣기
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
        //식의 앞에 있는 공백 제거
        exp = exp_head;
        while(exp->next != NULL){
            if(exp->d != ' ' && exp->d != '\n') break;
            exp_x = exp->next;
            exp->next->prev = NULL;
            free(exp);
            exp = exp_x;
        }
        exp_head = exp;
        

        //식 중간중간에 있는 공백 제거
        exp = exp_head->next;
        while(exp!=NULL){
            if(exp->d == ' ' || exp->d == '\n'){
                exp_x = exp->prev;
                del_link(exp);
                exp = exp_x;
            }
            exp = exp->next;
        }

        
        exp = exp_head;

        //중간부분 체크에 쓰일 변수 선언
        int number = 1; // 숫자가 있으면 0
        int spot = 0;
        int left_bracket = 0; // 왼괄호
        int right_bracket = 0; // 우괄호

        // 맨 앞에 나오면 안되는 게 있으면 에러 체크
        if(!(exp->d == '(' || exp->d == '-' || (exp->d >= '0' && exp->d <= '9'))) errorcheck = -1;

        //맨 앞이 숫자이면 숫자 나왔다고 알려주기
        if(exp->d>='0' && exp->d <='9') number = 0;


        //중간부분
        exp = exp_head;
        while(exp->next != NULL){

            //에러가 체크되어 있으면 break
            if(errorcheck == -1) break;
            
            //숫자 하나에 .이 2개이면 에러 체크, 숫자 나왔는지 확인
            if((exp->d >= '0' && exp->d <= '9') || exp->d == '.'){
                number = 0;
                if(!spot && exp->d == '.') spot = 1;
                else if(spot && exp->d == '.') {errorcheck = -1; break;}
            }
            else spot = 0;
            
            //괄호 개수 세기
            if(exp->d == '(') left_bracket ++;
            if(exp->d == ')') right_bracket ++;

            //우괄호가 더 많으면 에러체크
            if(left_bracket < right_bracket) {errorcheck = -1; break;}
            
        

            //나오면 안되는 문자
            if(!(exp->d == '+' || exp->d == '-' || exp->d == '/' || exp->d == '*' || 
                        exp->d == '(' || exp->d == ')' || exp->d == '.' ||  (exp->d>='0'&&exp->d<='9'))){errorcheck = -1; break;}
            
            //연산자 다음에 나오면 안되는 문자
            if(exp->d == '+' || exp->d == '/' || exp->d == '*' || exp->d == '-'){
                if(!(exp->next->d == '(' || (exp->next->d>='0' && exp->next->d<='9'))) {errorcheck = -1; break;}
            }

            if(exp->d == '('){
                if(!(exp->next->d == '(' || exp->next->d == ')' || exp->next->d == '-' || 
                            (exp->next->d>='0' && exp->next->d<='9'))) {errorcheck = -1; break;}
            }
            if(exp->d == ')'){
                if(exp->next->d >= '0' && exp->next->d <='9') {errorcheck = -1; break;}
            }
            exp = exp->next;
            

            // 귀여운 텍스트를 위한 단계
            if(errorcheck != -1){
                if(errorcheck < 0 && exp->d == '+') errorcheck = 0;
                if(errorcheck < 1 && exp->d == '-') errorcheck = 1;
                if(errorcheck < 2 && exp->d == '*') errorcheck = 2;
                if(errorcheck < 3 && exp->d == '/') errorcheck = 3;
                if(errorcheck < 4 && exp->d == ')') errorcheck = 4;
            }
        }

        // 마지막 글자로 나오면 안되는게 나오면 에러체크 및 괄호 세기 및 숫자 체크
        if(exp->prev != NULL){
            if(!(exp->d == '+' || exp->d == '-' || exp->d == '/' || exp->d == '*' || 
                        exp->d == '(' || exp->d == ')' || (exp->d>='0'&&exp->d<='9'))) errorcheck = -1;

            if(!(exp->d == ')' || (exp->d >= '0' && exp->d <= '9'))) errorcheck = -1;
            if(exp->d == ')') right_bracket++;
            if(exp->d >= '0' && exp->d<='9') number = 0;
        }

        //숫자가 없으면 에러 체크
        if(number) errorcheck = -1;

        //괄호 개수가 같지 않으면 에러 체크
        if(left_bracket != right_bracket) errorcheck = -1;

        //에러가 체크되어 있으면 오류문구 출력 후 처음으로
        if(errorcheck == -1) {printf("어라.. 식이 이상한 거 같은데요?\n\n"); free_all(exp_head); continue;}

        
        //귀여운 텍스트 출력
        if(errorcheck == -31) printf("음.. 연산자가 없는거 같기도 하고..");
        if(errorcheck == 0) printf("일단 저걸 더해야 하고..");
        if(errorcheck ==1) printf("저것들은 빼야 할 거 같고..");
        if(errorcheck ==2) printf("얘네는 이렇게 이렇게 곱하고 더해서..");
        if(errorcheck ==3) printf("저걸 저걸로 잘 나눠주면...");
        if(errorcheck ==4) printf("저건 묶어서 생각하고...");


        ////////////////////////////////////////////////
        //수정부
        //

        // 맨 앞에 -가 나오는 경우, 맨 앞에 0 붙여주기   ( -   >   0- )
        if(exp_head->next != NULL && exp_head->d == '-'){
            LINK minus = char_to_list('0');
            concatenate(minus, exp_head);
            exp_head = minus;
        }


        // 중간 수정 파트 //
        exp = exp_head;
        int situration = 0;
        for(; exp!=NULL; exp=exp->next){

            //피연산자를 만났을 때
            if((exp->d >='0' && exp->d <='9') || exp->d == '.'){

                // 다음 링크의 글자가 '(' 일 때 * 추가   ex) 2(3-2)  ->  2*(3-2)
                if(exp->next != NULL && exp->next->d == '('){
                    insert(exp,'*'); 
                }

                // .을 만나면 만났다고 체크
                if(exp->d == '.'){
                    situration = 1;
                }

                //다음 링크의 글자가 피연산자가 아닐 때
                if(exp->next != NULL && (exp->next->d <'0' || exp->next->d >'9') && exp->next->d != '.'){

                    // 소수점이 없었다면 소수점하고 소수점 체크 변수 0으로 초기화
                    if(situration == 0){
                        insert(exp,'.');
                        exp=exp->next;
                    }
                    // 소수점이 있었다면 0으로 초기화
                    else situration = 0;
                }
            }

            // 우괄호를 만나고, 바로 다음이 좌괄호이면 * 추가
            if(exp->next != NULL && exp->d == ')' && exp->next->d == '(') insert(exp,'*');

            // 좌괄호이고, 다음 문자가 '-' 이면 0 추가
            else if(exp->d == '('){
                if(exp->next!=NULL && exp->next->d == '-'){
                    insert(exp,'0');
                }
            }
        }


        // 마지막 피연산자에 .이 없었다면 . 추가
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

        // 피연산자를 받아오기 위한 링크드리스트들
        LINK rational;
        LINK input_link;

        //피연산자 추가중이면 1, 아니면 0
        situration = 0;
     
        for(; exp != NULL; exp = exp->next){
            //피연산자 추가
            if((exp->d == '.') || (exp->d >= '0' && exp->d <= '9')){

                //피연산자의 맨 처음 문자를 만났을 때
                //식에서 만난 피연산자는 무조건 양수이므로 + 부호 추가
                //피연산자 추가중이라고 체크
                if(situration == 0){
                    rational = char_to_list('+');
                    insert(rational, exp->d);
                    input_link = rational->next;
                    situration = 1;
                }

                //피연산자 링크드리스트에 문자 추가
                else{
                    insert(input_link,exp->d);
                    input_link = input_link->next;
                }

                //식의 다음 문자가 피연산자가 아니라면 숫자 스택에 푸쉬하고 피연산자 추가중 체크 해제
                if(exp->next == NULL || (exp->next->d < '0' || exp->next->d > '9') && (exp->next->d != '.')){
                    Push(&num_stack,rational);
                    situration = 0;
                }
            }
            
            // 현재 식의 문자가 ) 일 때의 연산
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

            // 현재 식의 문자가 ( 일 때 연산자 스택에 푸쉬
            else if(exp->d == '(') Push(&oper_stack,char_to_list('('));

            // 현재 식의 문자가 + 또는 - 일 때 연산하고 연산자스택에 푸쉬
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

            // 현재 식의 문자가 * 또는 / 일 때 연산하고 연산자 스택에 푸쉬
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
        
        // 연산자 스택이 비어있지 않을 때 연산
        while(!IsEmpty(&oper_stack)){
            LINK oper = Pop(&oper_stack);
            if(oper->d == '(') {free(oper); continue;}
            LINK p2 = Pop(&num_stack);
            LINK p1 = Pop(&num_stack);
            Push(&num_stack,calculator(p1,p2,oper->d));
            free_all(oper);
        }
        

        printf("아 끝났다! 답이에요!\n ->  ");

        //답 출력
        LINK answer = Pop(&num_stack);
        print_answer(answer);
        ////////////////////////////////////////////////
        //메모리를 아끼자
        
        //답, 식 메모리 해제
        free_all(answer);
        free_all(exp_head);
    }

    printf("이용해주셔서 감사합니다!\n");
}

LINK calculator(LINK p1, LINK p2, char oper){
    LINK p3;

    //연산자가 + 또는 - 일 때
    if(oper == '+' || oper=='-'){

        //연산자가 - 일 때, 뒷 피연산자의 부호 바꾸기
        if(oper == '-'){
            p2->d = (p2->d == '-' ? '+' : '-');
        }

        // 두 피연산자의 부호가 같으면 더하기, 다르면 빼기
        if(p1->d + p2->d == '+'+'+' || p1->d + p2->d == '-'+'-'){p3 = plus(p1,p2);}   //부호가 같을 시 플러스
        else {p3 = minus(p1,p2);}   // 부호가 다를 시 마이너스
    }

    if(oper == '*') {p3 = multiple(p1,p2);}
    if(oper == '/') {p3 = division(p1,p2);}
    
    return p3;
}

void print_help(){
    printf("\n\n\
--------------------------------------\n\
안녕하세요 저는 계산기에요!\n\
어떤 것을 여쭤보고 싶으신가요?\n\
--------------------------------------\n\
지원하는 연산자     | a\n\
식 쓰는 방법        | b\n\
물어볼 거 없어요    | c\n\
--------------------------------------\n\
-> ");

    char input; scanf(" %c",&input);
    if(input == 'a'){
        printf("\
--------------------------------------\n\
+ : 더하기\n\
- : 빼기\n\
* : 곱하기\n\
/ : 몫(0으로 나눌 시, 0을 반환합니다)\n\
( : 좌괄호\n\
) : 우괄호\n\
및 소수점을 포함한 숫자\n\
--------------------------------------\n");
    }
    else if(input == 'b'){
        printf("\
--------------------------------------\n\
1. 일반적인 수학책에 나오는 모든 사칙 연산 가능합니다\n\
    -> 음수로 시작 가능  ex) -321  -(32)\n\
    -> 괄호 끼리 붙이기 가능  ex) (423)(32)\n\
    -> 사이 공백 가능 등등..\n\n\
2. 일반적이지 않은 부호로 시작하지 못합니다\n\
    ex) +312\n\n\
3. 모든 문법 오류는 계산이 불가능합니다.\n\
    ex) (32(\n\
        x+y\n\
        (432)423\n\
--------------------------------------\n");
    }
    else{
        printf("\
--------------------------------------\n\
    즐거운 계산 되세요!\n\
--------------------------------------\n");
    }
}


