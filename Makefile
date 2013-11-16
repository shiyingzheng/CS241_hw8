all: linkedlist_test

linkedlist:
	clang -c linkedlist.c

linkedlist_test: linkedlist.o linkedlist_test.c
	clang -std=c99 -o linkedlist_test linkedlist_test.c linkedlist.o

clean: 
	rm -f linkedlist_test linkedlist.o *~
