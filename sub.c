#include <stdio.h>
#include "inter_link.h"
#include <stdbool.h>
	
bool sub(LINK a, LINK b, bool is_it_first){//subtract eachnumber in same digit 

    int a_tmp, b_tmp;
    if(a->d == '.') sub(a->prev, b->prev, is_it_first);
    else if((a->prev != NULL) && (a->d != '.')){
        int a_tmp = a->d - '0';
        int b_tmp = b->d - '0';

        a_tmp = a_tmp - b_tmp;

        if(a_tmp <= 0){
            a_tmp += desending(is_it_first);
            is_it_first = false;

        }else if(a_tmp > 0 && is_it_first == false){
            a_tmp--;
            is_it_first = true;
        }

        a->d = a_tmp + '0';
        b->d = b_tmp + '0';
        sub(a->prev, b->prev, is_it_first);
    }else return is_it_first;

LINK sep(LINK head){					//seperate interger, point and decimel. also return decimals. 
	LINK new;
    for( ; head != NULL; head = head->next){
		if(head->d == '.'){
            new = head->next;
			head->next = NULL;
            break;
        }
    }
    return new;    
}

int fill_zero(LINK a, LINK b){          //fix digit, delete point, return location of point.
    LINK a_deci = sep(a);
    LINK b_deci = sep(b);

    int a_deci_cnt = count(a_deci);
    int b_deci_cnt = count(b_deci);

    int max, min;
    if(a_deci_cnt < b_deci_cnt){
        max = b_deci_cnt;
        min = a_deci_cnt;
        for( ; min < max; min++){
            LINK tmp = char_to_list('0');
            concatenate(a_deci, tmp);
        }
    }else if(a_deci_cnt > b_deci_cnt){
        max = a_deci_cnt;
        min = b_deci_cnt;
        for( ; min < max; min++){
            LINK tmp = char_to_list('0');
            concatenate(b_deci, tmp);
        }
    }

    int a_int_cnt = count(a);
    int b_int_cnt = count(b);

    if(a_int_cnt < b_int_cnt){
        max = b_int_cnt;
        min = a_int_cnt;
        for( ; min < max; min++){
            insert(a, '0');
        }
    }else if(a_int_cnt > b_int_cnt){
        max = a_int_cnt; 

        min = b_int_cnt;
        for( ; min < max; min++){
            insert(b, '0');
        }
    }
    concatenate(a, a_deci);
    concatenate(b, b_deci);

    return max;     //longer integer part.

LINK roll_back(LINK head){	//move pointer to first link. 
    if(head->prev == NULL) return head;
    else roll_back(head->prev);
}


int desending(bool hm){		//when a < b in single node, use this for desending number.
    if(hm == true) return 10;
    else return 9;
}

LINK subtract(LINK a, LINK b){      // IF YOU WANNA SUBTRACT B FROM A, USE THIS FUNCTION. 
    bool mark;						// record + or -
    if(a->d == '+' && b->d == '+') mark = true; 
    else if(a->d == '-' && b->d == '-') mark = false;

    int cnt_point = fill_zero(a, b);//make same digit with zero.

    for( ; a->next != NULL; a = a->next);	//move pointer to last link.
    for( ; b->next != NULL; b = b->next);

    bool is_it_first = sub(a, b, true);		//'is it first' is use for make + or -

    a = roll_back(a);printf("\n"); 			//move pointer to first link
    b = roll_back(b);printf("\n"); 
											//determinasion '+' or '-'
    if((mark == true && is_it_first == true)||(mark == false && is_it_first == false)) a->d = '+';	
    else{
        a->d = '-';							//when a < b, complement calculation 
        if(is_it_first == false){
            int cnt = count(a);             //length of number, use this for make complement calculation.


            LINK cmp = char_to_list('-');	
            for(int i= 0; i < cnt; i++){
                LINK tmp;
                if(i == 0) tmp = char_to_list('1');
				else if(i == cnt_point - 1) tmp = char_to_list('.');

                else tmp = char_to_list('0');
                concatenate(cmp, tmp);
            }

            insert(a, '0');
			for( ; a->next != NULL; a = a->next);	//move pointer to last link.
            for( ; cmp->next != NULL; cmp = cmp->next);

            sub(cmp, a, true);

            a = roll_back(cmp);printf("\n"); //move pointer to first link

            a->d = '-';						//delete zero.
            a->next = a->next->next;
            a->next->prev = a;

        }
    }

    for( ; a->d == '-' || a->d == '+';){	//delete zero in front
        if(a->next->d == '0'){
            a->next = a->next->next;
            a->next->prev = a;
        }else break;
    }

    for( ; a->next != NULL; a = a->next);	//delete zero in back
    for( ; a->d =='0'; a = a->prev){
            a->prev->next = NULL;
    }
	a = roll_back(a);
	return a;
}
