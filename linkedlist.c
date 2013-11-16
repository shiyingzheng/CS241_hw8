/*
 * A doubly linked list
 */
#include "linkedlist.h"
node* node_init(int datasize, void* data){
	node* n=malloc(sizeof(node));
	if(!n) fprintf(stderr,"not enough memory");
	n->data=malloc(datasize);
	if(!n->data) fprintf(stderr, "not enough memory");
	if(data) memcpy(n->data, data, datasize);
	n->datasize=datasize;
	return n;
}
void node_free(node* n){
	free(n->data);
	free(n);
}
linkedlist* linkedlist_init(int datasize){
	linkedlist* list=malloc(sizeof(linkedlist));
	if(!list) fprintf(stderr, "not enough memory");
	list->size=0;
	list->datasize=datasize;
	list->head=node_init(datasize,NULL);
	list->tail=node_init(datasize,NULL);
	list->head->prev=NULL;
	list->head->next=list->tail;
	list->tail->prev=list->head;
	list->tail->next=NULL;
	return list;
}
void linkedlist_addfront(linkedlist* list, void* data){
	if(!data) fprintf(stderr,"Nullpointer; trying to add NULL data");
	node* newnode=node_init(list->datasize,data);
	node* tmp=list->head->next;
	list->head->next=newnode;
	newnode->prev=list->head;
	newnode->next=tmp;
	tmp->prev=newnode;
	list->size++;
}
void linkedlist_addend(linkedlist* list, void* data){
	if(!data) fprintf(stderr,"Nullpointer; trying to add NULL data");
        node* newnode=node_init(list->datasize,data);
        node* tmp=list->tail->prev;
        list->tail->prev=newnode;
        newnode->next=list->tail;
        newnode->prev=tmp;
        tmp->next=newnode;
	list->size++;
}
void* linkedlist_getfront(linkedlist* list){
	if(!list->size){ 
		fprintf(stderr,"Cannot get from an empty list");
		return NULL;	
	}
	void* data=list->head->next->data;
	return data;
}
void* linkedlist_getend(linkedlist* list){
	if(!list->size){ 
		fprintf(stderr,"Cannot get from an empty list");
		return NULL;	
	}
	void* data=list->tail->prev->data;
	return data;
}
void* linkedlist_rmfront(linkedlist* list){
	if(!list->size){
		fprintf(stderr,"can't remove from a list of size 0");
		return NULL;
	}
	node* removethis=list->head->next;
	void* value=malloc(list->datasize);
	if(!value) fprintf(stderr,"ran out of memory");
	memcpy(value,removethis->data,list->datasize);
	list->head->next=removethis->next;
	removethis->next->prev=list->head;
	node_free(removethis);
	list->size--;
	return value;
}
void* linkedlist_rmend(linkedlist* list){
	if(!list->size){
		fprintf(stderr,"can't remove from a list of size 0");
		return NULL;
	}
	node* removethis=list->tail->prev;
	void* value=malloc(list->datasize);
	if(!value) fprintf(stderr,"ran out of memory");
	memcpy(value,removethis->data,list->datasize);
	list->tail->prev=removethis->prev;
	removethis->prev->next=list->tail;
	node_free(removethis);
	list->size--;
	return value;
}
int linkedlist_size(linkedlist* list){
	return list->size;
}
iterator* linkedlist_iterator(linkedlist* list){
	iterator* iter=malloc(sizeof(iterator));
	iter->list=list;
	iter->position=0;
	iter->current=list->head;
	return iter;
}
iterator* linkedlist_iteratorend(linkedlist* list){
	iterator* iter=malloc(sizeof(iterator));
	iter->list=list;
	iter->position=list->size-1;
	iter->current=list->tail->prev;
	return iter;
}
int linkedlist_iteratorhasnext(iterator* iter){
	return (iter->position<iter->list->size);
}
int linkedlist_iteratorhasprev(iterator* iter){
	return (iter->position>0);
}
void* linkedlist_iteratornext(iterator* iter){
	void* value=iter->current->next->data;
	if(!value) fprintf(stderr,"I don't have a next");
	iter->current=iter->current->next;
	iter->position++;	
	return value;
}
void* linkedlist_iteratorprev(iterator* iter){
	void* value=iter->current->data;
	if(!value) fprintf(stderr,"I don't have a prev");
	else iter->current=iter->current->prev;	
	iter->position--;	
	return value;
}
void linkedlist_iteratoradd(iterator* iter){
	//not implemented yet
}
void* linkedlist_iteratorrm(iterator* iter){
	//not implemented yet
	void* a;
	return a;
}
void linkedlist_free(linkedlist* list){
	node* freethis=list->head;
	node* tmp;
	while(freethis!=list->tail){
		tmp=freethis->next;
		node_free(freethis);
		freethis=tmp;
	}
	node_free(list->tail);
	free(list);
}	
void linkedlist_freeiter(iterator* iter){
	free(iter);
}
