#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "inter_link.h"
#include "stack.h"
#include "multiple.h"
#include "minus.h"
#include "plus.h"
#include "division.h"

LINK calculator(LINK,LINK,char);
long long getElapsedTime(unsigned int);

int main(void){
    
    ////////////////////////////////////////////////
    //시간 재기 시작
    getElapsedTime(0);

    ////////////////////////////////////////////////
    //선언부

    // 앞으로 에러를 체크해 줄
    char errorcheck=0;  // -1: error

    // 숫자 스택, 연산자 스택
    Stack num_stack, oper_stack;
    InitStack(&num_stack);
    InitStack(&oper_stack);

    ///////////////////////////////////////////////
    //입력부
    FILE *fq = fopen("input","r"); 
    printf("Input : ");
    //input에 입력을 받고 리스트에 넣는다.
    char input = getc(fq);
    printf("%c",input);

    //식 링크드리스트 생성
    LINK exp_head = char_to_list(input);
    LINK exp = exp_head;
    LINK exp_x;
    
    //두번째 글자부터 입력 및 링크드리스트 넣기
    while(input = getc(fq)){
        if(input == '\n') break;
        printf("%c",input);
        LINK p = char_to_list(input);
        exp->next = p;
        p->prev = exp;
        exp = p;
    }
    printf("\n");
    
    ////////////////////////////////////////////////
   
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
    char number = 1; // 숫자가 있으면 0
    char spot = 0;
    unsigned long long left_bracket = 0; // 왼괄호
    unsigned long long right_bracket = 0; // 우괄

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

    //에러가 체크되어 있으면 오류문구 출력 후 종료
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(errorcheck){
        printf("Problem on Input\n"); 
        free_all(exp_head);
        printf("Elapsed Time: %lld\n",getElapsedTime(1));
        exit(1);
    }


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
    char situration = 0;
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
                LINK p3 = calculator(p1,p2,oper->d);
                if(p3->d == 'e'){
                    printf("0으로 나눌 수는 없습니다.\n");
                    free_all(exp_head);
                    printf("Elapsed Time: %lld\n",getElapsedTime(1));
                    exit(2);
                }
                Push(&num_stack,p3);
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
                LINK p3 = calculator(p1,p2,oper->d);
                if(p3->d == 'e'){
                    printf("0으로 나눌 수는 없습니다.\n");
                    free_all(exp_head);
                    printf("Elapsed Time: %lld\n",getElapsedTime(1));
                    exit(2);
                }
                Push(&num_stack,p3);

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
                LINK p3 = calculator(p1,p2,oper->d);
                if(p3->d == 'e'){
                    printf("0으로 나눌 수는 없습니다.\n");
                    free_all(exp_head);
                    printf("Elapsed Time: %lld\n",getElapsedTime(1));
                    exit(2);
                }
                Push(&num_stack,p3);
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
        LINK p3 = calculator(p1,p2,oper->d);
        if(p3->d == 'e'){
            printf("0으로 나눌 수는 없습니다.\n");
            free_all(exp_head);
            printf("Elapsed Time: %lld\n",getElapsedTime(1));
            exit(2);
        }
        Push(&num_stack,p3);
        free_all(oper);
    }
    
    //답 출력
    printf("Result : ");
    LINK answer = Pop(&num_stack);
    print_answer(answer);
    printf("\n");
    ////////////////////////////////////////////////
    //메모리 해제
    
    //답, 식 메모리 해제
    free_all(answer);
    free_all(exp_head);

    printf("Elapsed Time: %lld\n",getElapsedTime(1));
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

long long getElapsedTime(unsigned int nFlag)
{
	const long long NANOS = 1000000000LL;
	static struct timespec startTS, endTS;
	static long long retDiff = 0;

	if (nFlag == 0) {
		retDiff = 0;
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
	}
	else {
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
		retDiff = NANOS * (endTS.tv_sec - startTS.tv_sec) + (endTS.tv_nsec - startTS.tv_nsec);
 	}

	return retDiff;
}
