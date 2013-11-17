#include "linkedlist.h"
/*
 * The struct bigint
 */
typedef struct bigint {
	linkedlist* digit_list; //a list of digits
	char sign; //sign can only be 1 or -1, and we are using char because it saves space
} bigint;
extern bigint* bigint_init (char num_sign);
extern void bigint_add_digit(bigint* num, int digit);
extern int bigint_abscmp (bigint * num1, bigint* num2);
extern int bigint_iszero(bigint* num);
extern bigint* add (bigint* num1, bigint* num2);
extern void print_bigint(bigint* num);
extern void free_bigint(bigint* num);