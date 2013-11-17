all: linkedlist_test bigint additup

linkedlist: linkedlist.c
	clang -g -c linkedlist.c

linkedlist_test: linkedlist.o linkedlist_test.c
	clang -std=c99 -g -o linkedlist_test linkedlist_test.c linkedlist.o

bigint: bigint.c linkedlist.o
	clang -g -c bigint.c

additup: bigint.o linkedlist.o additup.c
	clang -std=c99 -g -o additup additup.c linkedlist.o bigint.o

clean: 
	rm -f linkedlist_test additup bigint.o linkedlist.o *~
