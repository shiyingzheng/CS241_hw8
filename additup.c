#include "bigint.h"
#include <ctype.h>
#define LINE_MAX 1024
int eof=0;
/*
 * Getting the first digits from a line until the first non digit, and turn them into a bigint, ignoring empty lines
 * Returns a pointer to a bigint
 */
bigint* getbigint(){
	bigint* newint;
	int c;
	if((c=getchar())==EOF) newint=bigint_init(1);
	while(c=='\n'){
		c=getchar();
	}
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
/*
 * The main method of the program
 */
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