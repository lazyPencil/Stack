#include <stdio.h>
#include "stack_array.h"
#define SIZE 4

int main(void) {
	stack* var = NULL;
	int i;

	var = createstack(SIZE);
	if (var == NULL) {
		printf("createstack failure\n");
	}

	for (i = 0; i < SIZE; i++) {
		push(var,i*5);
		printf("push %d!\n", i * 5);
	}
	push(var, 500);

	for (i = 0; i < SIZE; i++) {
		printf("pop %d!\n", pop(var));
	}
	i = pop(var);
	printf("pop(ptr) = i = %d\n", i);

	for (i = 0; i < SIZE-1; i++) {
		push(var, i * 18);
		printf("push %d!\n", i * 18);
	}
	printf("var->top=%d\n", var->top);
	i = countstackitem(var);
	printf("countstackitem(arr) = i = %d\n", i);
	for (i = 0; i < SIZE; i++) {
		printf("pop %d!\n", pop(var));
	}
	i = topcheck(var);
	printf("topcheck(ptr) = i = %d\n", i);
	i = countstackitem(var);
	printf("countstackitem(arr) = i = %d\n", i);
	clearstack(var);
	i = topcheck(var);
	printf("after clearstack, topcheck(ptr) = i = %d\n", i);
	push(var, 3500);
	i = topcheck(var);
	printf("after push( , 3500), topcheck(ptr) = i = %d\n", i);
	i = countstackitem(var);
	printf("countstackitem(arr) = i = %d\n", i);
	destroystack(var);
	return 0;
}