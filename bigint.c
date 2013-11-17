/* bigint struct takes care of both positive and negative numbers! */
#include "bigint.h"
/*
 * Initializes a bigint
 * Takes in 1 when the number is positive, and -1 when the number is negative.
 * Returns a pointer to a bigint with only a sign and nothing as its digits.
 */
bigint* bigint_init (char num_sign) {
	bigint* myint = malloc(sizeof(bigint));
	if (!myint) exit(EXIT_FAILURE);
	myint->digit_list = linkedlist_init(sizeof(char)); //we are using sizeof(char) here because we want to save space, as each digit is only from 0 to 9
	myint->sign = num_sign;
	return myint;
}
/*
 * Adds digits to the bigint.
 * Takes in a pointer to the bigint and an integer which is the digit being added to the bigint
 */
void bigint_add_digit(bigint* num, int digit) {
	linkedlist_addend(num->digit_list, &digit); //add to the end of digit_list in num
}
/*
 * Compares the absolute values of two bigints.
 * Takes in two pointers to the two bigints.
 * Returns a positive integer if the first bigint has a bigger absolute value than the second one,
 * a negative integer if it is smaller, and 0 if they are the same.
 */
int bigint_abscmp (bigint * num1, bigint* num2) {
	int a;
	if ((a=(num1->digit_list->size - num2->digit_list->size))) //if the number of digits in one number is larger than the other, simply return the difference of the lengths
		return a;
	iterator* iter1 = linkedlist_iterator(num1->digit_list);
	iterator* iter2 = linkedlist_iterator(num2->digit_list);
	while(linkedlist_iteratorhasnext(iter1)){ //iterate through the numbers and return the difference of the first different digits
		if ((a=(*(char*)linkedlist_iteratornext(iter1) - *(char*)linkedlist_iteratornext(iter2)))) {
			linkedlist_freeiter(iter1);
			linkedlist_freeiter(iter2);
			return a;
		}
	}
	linkedlist_freeiter(iter1);
	linkedlist_freeiter(iter2);

	return a;
}
/*
 * Checks if the first digit is zero.
 * Takes in a pointer to a bigint.
 * Returns non-zero value if true, and zero if false.
 */
int bigint_iszero(bigint* num){
	return 0==*(char*)linkedlist_getfront(num->digit_list);
}
/*
 * Adds the absolute values of two bigints of the same sign.
 * Takes in two pointers to two bigints.
 * Returns a pointer to the bigint which is the sum.
 */
bigint* addabs (bigint* num1, bigint* num2){
	bigint* sum = bigint_init(1);
	int carry=0;
	int cur_digit;
	iterator* iter1 = linkedlist_iteratorend(num1->digit_list);
	iterator* iter2 = linkedlist_iteratorend(num2->digit_list);
	while (linkedlist_iteratorhasprev(iter1) && linkedlist_iteratorhasprev(iter2)){//adds the ending digits together until maybe there are digits left in one but not in the other
		cur_digit=*(char*)linkedlist_iteratorprev(iter1)+*(char*)linkedlist_iteratorprev(iter2)+carry;
		if (cur_digit>9){
			carry=1;
			cur_digit=cur_digit-10;
		}
		else{
			carry=0;
		}
		linkedlist_addfront(sum->digit_list, &cur_digit);
	}
	while (linkedlist_iteratorhasprev(iter1)){//adds the digits left in num1 to the sum, if there are any
		cur_digit=*(char*)linkedlist_iteratorprev(iter1)+carry;
		if (cur_digit>9){
			carry=1;
			cur_digit=cur_digit-10;
		}
		else{
			carry=0;
		}
		linkedlist_addfront(sum->digit_list, &cur_digit);
	}
	while (linkedlist_iteratorhasprev(iter2)){//adds the digits left in num2 to the sum, if there are any
		cur_digit=*(char*)linkedlist_iteratorprev(iter2)+carry;
		if (cur_digit>9){
			carry=1;
			cur_digit=cur_digit-10;
		}
		else{
			carry=0;
		}
		linkedlist_addfront(sum->digit_list, &cur_digit);
	}
	if (carry){//there might be an extra 1, e.g. the 1 in 100 from 36+64
		cur_digit=1;
		linkedlist_addfront(sum->digit_list, &cur_digit);
	}
	linkedlist_freeiter(iter1);
	linkedlist_freeiter(iter2);
	return sum;
}
/*
 * Assuming num1's absolute value is bigger than num2's, does subtraction on the absolute values of two bigints
 * Takes in two pointers to two bigints
 * Returns a pointer to a bigint which is the difference
 */
bigint* minus (bigint* num1, bigint* num2) { //so that we can take care of the case when one of the two numbers is negative
	bigint* dif = bigint_init(1);
	int carry=0;
	int cur_digit;
	char a;
	char* b;
	iterator* iter1 = linkedlist_iteratorend(num1->digit_list);
	iterator* iter2 = linkedlist_iteratorend(num2->digit_list);
	iterator* difiter;
	while (linkedlist_iteratorhasprev(iter1) && linkedlist_iteratorhasprev(iter2)){//subtracts the ending digits of num2 from num1 until maybe there are digits left in num1
		cur_digit=*(char*)linkedlist_iteratorprev(iter1)+carry-*(char*)linkedlist_iteratorprev(iter2);
		if (cur_digit<0){
			cur_digit=cur_digit+10;
			carry=-1;
		}
		else{
			carry=0;
		}
		linkedlist_addfront(dif->digit_list, &cur_digit);
	}
	while (linkedlist_iteratorhasprev(iter1)){//adds the remaining digits from num1 to sum
		cur_digit=*(char*)linkedlist_iteratorprev(iter1)+carry;
		if (cur_digit<0){
			carry=-1;
			cur_digit=cur_digit+10;
		}
		else{
			carry=0;
		}
		linkedlist_addfront(dif->digit_list, &cur_digit);
	}

	//maybe there are leading 0's in the sum right now, so we need to remove them
	difiter=linkedlist_iterator(dif->digit_list); 
	while (linkedlist_iteratorhasnext(difiter) && bigint_iszero(dif)) {
		b=linkedlist_rmfront(dif->digit_list);
		free(b);
	}
	//if the sum is 0, we just removed all 0's and nothing is in sum! so we need to add a 0 back
	if (!linkedlist_size(dif->digit_list)) bigint_add_digit(dif, 0);
	linkedlist_freeiter(iter1);
	linkedlist_freeiter(iter2);
	linkedlist_freeiter(difiter);
	return dif;
}
/*
 * Adds two bigints
 * Takes in two pointers to two bigints to sum up
 * Returns a pointer to a big int which is the sum
 */
bigint* add (bigint* num1, bigint* num2){
	bigint* sum;
	int a;
	if (1==num1->sign && 1==num2->sign){//Adding two positive numbers is just adding them.
		sum=addabs(num1, num2);
	}
	else if (-1==num1->sign && -1==num2->sign){ //When two numbers are both negative, the result is negative. Add the two absolute value together and set the sum negative
		sum=addabs(num1, num2);
		sum->sign=-1;
	}
	else{//When one number is positive and one is negative, we need to use the minus function. Use subtract the smaller absolute value from the bigger one, and decide
		 //the sign later.
		a = bigint_abscmp(num1, num2);
		if (a>0){
			if (1==num1->sign){//e.g. 100 and -40
				sum=minus(num1, num2);
			}
			else{//e.g. -100 and 40
				sum=minus(num1, num2);
				sum->sign=-1;
			}
		}
		else{
			if (1==num1->sign){//e.g. 40 and -100
				sum=minus(num2, num1);
				sum->sign=-1;
			}
			else{//e.g. -40 and 100
				sum=minus(num2, num1);
			}
		}
	}

	return sum;
}
/*
 * Prints a bigint
 * Takes in a pointer to the bigint to be printed
 */
void print_bigint(bigint* num) {
	iterator* iter = linkedlist_iterator(num->digit_list);
	if (-1==num->sign && bigint_iszero(num)){
		printf("%d", 0);
	}
	else {
		if (-1==num->sign) printf("-");
		while (linkedlist_iteratorhasnext(iter)){
			printf("%d", *(char*)linkedlist_iteratornext(iter));
		}
	}
	linkedlist_freeiter(iter);
}
/*
 * Frees a memory allocated to a bigint
 * Takes in a pointer to a bigint
 */
void free_bigint(bigint* num){
	linkedlist_free(num->digit_list);
	free(num);
}