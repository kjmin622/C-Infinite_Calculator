#include<stdio.h>
#include<stdlib.h>
#include "inter_link.h"

LINK division(LINK, LINK);
int division_compare(LINK, LINK);


int division_compare(LINK a, LINK b){  // 둘 다 양수이고 소수부가 없을 때를 가정  a>=b: 1  /  a<b : 2
    int alen = count(a);
    int blen = count(b);
    if(alen>blen) return 1;
    if(blen>alen) return 2;
    ////////////////////////////길이가 같을 때

    for(; a != NULL; a = a->next){
        if(a->d > b->d) return 1;
        if(b->d > a->d) return 2;
        b= b->next;
    }
    return 1;
}

LINK division(LINK a, LINK b){  // a/b
    //선언부/////////////////////////////////////////////////////////////
    int buho=0;  // 1->'+' , 2->'-'
    int alen = 0;
    int blen = 0;
    LINK num_copy;
    LINK num1;
    LINK num2;
    LINK where1;
    LINK where2;
    LINK mod;

    //부호 계산//////////////////////////////////////////////////////////
    if(a->d == b->d) buho=1;
    /////////////////////////////////////////////////////////////////////
    

    //부호 없애기////////////////////////////////////////////////////////
    num_copy = a;
    a = a->next;
    a->prev = NULL;
    free(num_copy);

    num_copy = b;
    b = b->next;
    b->prev = NULL;
    free(num_copy);
    ////////////////////////////////////////////////////////////////////
    //print_list(a);
    //print_list(b);
   
    //소수점 없애고 소수 아래 자리 세기//////// /////////////////////////
    num_copy = a;
    for(; num_copy->d != '.'; num_copy = num_copy->next);
    num1 = num_copy;
    del_link(num_copy);
    
    num_copy = b;
    for(; num_copy->d != '.'; num_copy = num_copy->next);
    num2 = num_copy;
    del_link(num_copy);
    ////////////////////////////////////////////////////////////////////
    //print_list(a);
    //print_list(b);

    //소수 아래 자리 맞추기///////////////////////////////////////////
    while(num1->next!=NULL || num2->next!=NULL){        
        if(num1->next == NULL) insert(num1,'0');
        if(num2->next == NULL) insert(num2,'0');

        num1 = num1->next;
        num2 = num2->next;
    }
    ///////////////////////////////////////////////////////////////////
    //print_list(a);
    //print_list(b);
    
    //나눠봅시다///////////////////////////////////////////////////////
    // num1 / num2
    num1 = char_to_list(a->d);
    where1 = num1;
    where2 = a->next;
    num2 = copy_link(b);
    num_copy = num2;
    
    if(division_compare(a,b)==1){   //a가 b보다 클 때
        for(; num_copy->next!=NULL; num_copy=num_copy->next){
            insert(where1,where2->d);
            where1 = where1->next;
            where2 = where2->next;
        }
        if(division_compare(num1,num2)==2){
            insert(where1,where2->d);
            where1 = where1->next;
            where2 = where2->next;
        }
    }
    else{  //b가 a보다 클 때
        free_all(a); free_all(b); free_all(num1); free_all(num2);
        num1 = char_to_list('+');
        insert(num1, '.');
        insert(num1, '0');
        return num1;
    }
        
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

