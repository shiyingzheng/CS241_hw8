/*
 * test linkedlist
 */
#include "linkedlist.h"
int main(){
	int n=50;
	int q;

	//test addend and removeend
	linkedlist* list=linkedlist_init(sizeof(int));
	for(int i=0;i<n;i++){
		q=i+n;
		linkedlist_addend(list,&q);
	}
	for(int i=0;i<n;i++){
		int* ptr=linkedlist_rmend(list);
		printf("%d ",*ptr);
		free(ptr);
	}
	printf("\n");
	linkedlist_free(list);


	//test the iterator
	list=linkedlist_init(sizeof(int));
	for(int i=0;i<n;i++){
		q=i+n;
		linkedlist_addend(list,&q);
	}
	iterator* iter=linkedlist_iterator(list);
	while(linkedlist_iteratorhasnext(iter)){
		printf("%d ",*(int*)linkedlist_iteratornext(iter));
	}
	printf("\n");
	linkedlist_free(list);
	linkedlist_freeiter(iter);


	//test the getfront and getend
	list=linkedlist_init(sizeof(char*));
	char* string="This is a string";
	char* string2="meow";
	linkedlist_addend(list,&string);
	linkedlist_addend(list,&string2);
	printf("%s %s\n",*(char**)linkedlist_getfront(list),*(char**)linkedlist_getend(list));
	linkedlist_free(list);
}
