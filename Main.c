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
#include "base.h"

long long getElapsedTime(unsigned int);

int main(void){
    
    ////////////////////////////////////////////////
    //시간 재기 시작
    getElapsedTime(0);

    //입력부
    LINK exp_head = input_exp();
    
    ////////////////////////////////////////////////
   
    ////////////////////////////////////////////////
    //오류 제거
    //
    //식의 앞에 있는 공백 제거
    exp_head = del_space(exp_head);

    //에러가 체크되어 있으면 오류문구 출력 후 종료
    char errorcheck = exp_error(exp_head);    
    if(errorcheck){
        printf("입력에 오류가 있습니다. 아래를 확인해주세요.\n");
        printf("\t1. 맨 앞 또는 ( 뒤에는 숫자, -, ( 만 올 수 있습니다.\n");
        printf("\t2. 숫자가 존재해야 합니다.\n");
        printf("\t3. 제대로 된 정수 또는 실수를 입력해야 합니다.\n");
        printf("\t4. 좌 우 각각의 괄호 개수가 같아야 합니다.\n");
        printf("\t5. 이상한 문자를 입력하면 안됩니다.\n");
        printf("\t6. 괄호 안이 비어있으면 안됩니다.\n");
        printf("\t7. 우괄호는 함께 쓰이는 좌괄호가 있어야 나올 수 있습니다.\n");
        printf("\t8. 마지막 글자에는 숫자, ) 만 올 수 있습니다. 등등..\n\n");
         
        free_all(exp_head);
        printf("Elapsed Time: %lld\n",getElapsedTime(1));
        exit(1);
    }

    ////////////////////////////////////////////////
    //수정부
    exp_head = exp_change(exp_head);
    
    ////////////////////////////////////////////////

    ////////////////////////////////////////////////
    //계산부
    LINK answer = exp_answer(exp_head);

    if(answer->d == 'e'){
        printf("0으로 나눌 수는 없습니다.\n");
        free_all(exp_head);
        printf("Elapsed Time: %lld\n",getElapsedTime(1));
        exit(2);
    }
   
    //답 출력
    printf("Result : ");
    print_answer(answer);
    printf("\n");

    ////////////////////////////////////////////////
    //답, 식 메모리 해제
    free_all(answer);
    free_all(exp_head);

    printf("Elapsed Time: %lld\n",getElapsedTime(1));
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
