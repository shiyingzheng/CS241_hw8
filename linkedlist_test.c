/*
 * test linkedlist
 */
#include "linkedlist.h"
int main(){
	int n=50;
	linkedlist* list=linkedlist_init(sizeof(int));
	for(int i=0;i<n;i++){
		linkedlist_addend(list,&i);
	}
	linkedlist_free(list);
}
