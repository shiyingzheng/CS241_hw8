all: linkedlist_test bigint

linkedlist: linkedlist.c
	clang -g -c linkedlist.c

linkedlist_test: linkedlist.o linkedlist_test.c
	clang -std=c99 -g -o linkedlist_test linkedlist_test.c linkedlist.o

bigint: bigint.c linkedlist.o
	clang -std=c99 -g -o additup bigint.c linkedlist.o

clean: 
	rm -f linkedlist_test linkedlist.o bigint *~
