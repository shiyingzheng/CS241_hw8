/*
 * A doubly linked list
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct node {
	void* data;
	unsigned int datasize;
	struct node *next, *prev;
} node;
typedef struct linkedlist{
	unsigned int datasize;
	unsigned int size;
	struct node *head, *tail;
} linkedlist;
typedef struct iterator{
	linkedlist* list;
	int position;
	node* current;
} iterator;
extern linkedlist* linkedlist_init(int datasize);
extern void linkedlist_addfront(linkedlist* list, void* data);
extern void linkedlist_addend(linkedlist* list, void* data);
extern void* linkedlist_rmfront(linkedlist* list);
extern void* linkedlist_rmend(linkedlist* list);
extern int linkedlist_size(linkedlist* list);
extern iterator* linkedlist_iterator(linkedlist* list);
extern int linkedlist_iteratorhasnext(iterator* iter);
extern int linkedlist_iteratorhasprev(iterator* iter);
extern void* linkedlist_iteratornext(iterator* iter);
extern void* linkedlist_iteratorprev(iterator* iter);
extern void linkedlist_iteratoradd(iterator* iter);
extern void* linkedlist_iteratorrm(iterator* iter);
extern void linkedlist_free(linkedlist* list);
extern void linkedlist_freeiter(iterator* iter);
