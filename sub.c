#include <stdio.h>
#include "link.h"
#include "inter_link.h"
	
LINK sub(LINK a, LINK b){// incomplete.
	
	LINK a_deci = sep(a);
	LINK b_deci = sep(b);
	a_cnt = count(a_deci);
	b_cnt = count(b_deci);

	int max, min;
	if(a_cnt < b_cnt){
		max = b_cnt; min = a_cnt;
		for(; min < max;min++){
			LINK tmp = char_to_list('0');
        	concatenate(a_deci, tmp);
    	}

	}else if(a_cnt > b_cnt){
		max = a_cnt; min = b_cnt;
		for(; min < max; min++){
			LIST tmp =  char_to_list('0');
			concatenate(b_sec, tmp)
		}
	}
	
	
	if(a->d == '+' && b->d == '+'){
		
	}else if(a->d == '+' && b->d == '-'){
		b = '+';
		//add(a, b);
	}else if(a->d == '-' && b->d == '+'){
		a = '+';
		//add(a, b); ans[0] = '-';
	}else{
		
	}
	
		
	return ; 
}

LINK subtract(LINK a, LINK b){
	LINK a_re = last_link(a);
	LINK b_re = last_link(b);

	int a_tmp, b_tmp;
	while(a_re != NULL){
		a_tmp = a_re->d - '0';
		b_tmp = b_re->d - '0';
		a_tmp = ((a_tmp - '0') - (b_tmp - '0'));
		if(a_tmp < 0){
			a_re->prev->d = ((a_re->prev->d - '0') -1) + '0';
			a_tmp += 10;
		}
		a_re->d = a_tmp + '0';
		b_re->d = b_tmp + '0';
		a_re = a_re->prev;
		b_re = b_re->prev;
	}
}


/*
  int main(){
 26     LINK a = char_to_list('3');
 27     insert(a, '4');
 28     LINK b = char_to_list('1');
 29     insert(b, '7');
 30 
 31     print_list(a);
 32     printf("\n");
 33     print_list(b);
 34 
 35     subtract(a, b);
 36 
 37     print_list(a);
 38 }
 39 


 3 --> 4 --> NULL

1 --> 7 --> NULL
1 --> 7 --> NULL

 */


int pointCnt(LINK head){
	int cnt = 0;
	for( ; head != NULL; head = head->next ){
		if(head->d == '.')
			return new; break; 
		cnt++;
	}
	return cnt;
}

LINK sep(LINK head){
    LINK new;
    for( ; head != NULL; head = head->next ){
        if(head->d == '.'){
            new = head->next;
            head->next = NULL;
            return new;
            break; 
    	}
	}
}

attach
