#include "bigint.h"
#include <ctype.h>
#define LINE_MAX 1024
int eof=0;
bigint* getbigint(){
	bigint* newint;
	int c;
	if((c=getchar())==EOF||c=='\n') newint=bigint_init(1);
	while(c!='\n'&&c!=EOF){
		while(isspace(c)){
			c=getchar();
		}
		if(c=='-'){
			newint=bigint_init(-1);
			c=getchar();
		}
		else newint=bigint_init(1);
		while(c=='0'){
			c=getchar();
		}
		while(isdigit(c)){
			bigint_add_digit(newint,c-'0');
			c=getchar();
		}
		while(c!='\n'&&c!=EOF){
			c=getchar();
		}
	}
	if(c==EOF) eof=1;
	if(!linkedlist_size(newint->digit_list)) bigint_add_digit(newint,0);
	return newint;		
}
int main(){
	bigint* sum=bigint_init(1);
	bigint_add_digit(sum,0);
	bigint* newsum;
	bigint* newint;
	while(!eof){
		newint=getbigint();
		if(!bigint_iszero(newint)||!eof){
			newsum=add(sum,newint);
			free_bigint(sum);
			free_bigint(newint);
			sum=newsum;
			printf("Total: ");
			print_bigint(sum);
			printf("\n");
		}
		else free_bigint(newint);
	}
	free_bigint(sum);
}		