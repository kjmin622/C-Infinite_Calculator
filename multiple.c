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
    if(num1->d == num2->d ){
        ans->d = '+';}
    else{
        ans->d = '-';}

    // 반대로 뒤집기 
    // 123.531+
    // 9712.5-

    LINK num1_copy = last_link(num1);
    LINK num2_copy = last_link(num2);

    // 소수점 계산 
    //
    int point = 0;
    for( ; num1_copy->d != '.' ; num1_copy = num1_copy->prev){point++};//3
    for( ; num2_copy->d != '.' ; num2_copy = num2_copy->prev){point++};//3+4=7




    for( ; num2_copy->d != NULL ; num2_copy = num2_copy->next);
        for( ; num2_copy->d != '+' || num2_copy != '-' ; num2_copy = num2_copy->prev){
            num2_reverse = num2_copy;}



    // 소수점 계산 
    int point1 =0, point2 =0;

     for( ; num1_copy->d != NULL ; num1_copy = num1_copy->next);
     for( ; num1_copy->d != '.' ; num1_copy = num1_copy->prev) point++;


    // 소수점 위치 계산 
    //
    LINK num1_point = num1;
    LINK num2_point = num2;

    
    for( ; num1_point->d != '.' ; num1_point=num1_point->next); //3
    for( ; num2_point->d != '.' ; num2_point=num2_point->next); //2
    
    // 점 빼기
    //

    // 계산
    // num2->d* num1->d .. 해서 계산 후 9보다 크거나 같으면 다음칸에 올림
    // num2->next->d* num1-> .. ...위에 계산 한 칸에 +
    // 

    // 다하면 반대로 뒤집기
    //

    // 소수점 계산 한 값만큼 소수점 뒤에서부터 카운트
    //


       

