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
    LINK exp_head = del_space(exp_head);

    //에러가 체크되어 있으면 오류문구 출력 후 종료
    char errorcheck = exp_error(exp_head);    
    if(errorcheck){
        printf("Problem on Input\n"); 
        free_all(exp_head);
        printf("Elapsed Time: %lld\n",getElapsedTime(1));
        exit(1);
    }

    ////////////////////////////////////////////////
    //수정부
    LINK exp_head = exp_change(exp_head);
    
    ////////////////////////////////////////////////

    ////////////////////////////////////////////////
    //계산부
    LINK answer = exp_answer(exp_head);

    if(p3->d == 'e'){
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
