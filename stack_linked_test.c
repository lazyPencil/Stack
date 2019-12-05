#include <stdio.h>
#include "stack_linked.h"

int main(void) {
	head* var = NULL;
	int i,j;
	var = createhead();
	if (var == NULL) {
		printf("main) createhead failure\n");
		return 1;
	}
	for (i = 0; i < 3; i++) {
		push(var, i * 10);
		printf("push %2d\n",i*10);
	}
	i = topcheck(var);
	printf("topcheck()=%d\n", i);
	i = countstackitem(var);
	printf("countstackitem()=%d\n", i);
	for (j = 0; j < 3; j++) {
		i = pop(var);
		printf("pop()=%d\n", i);
	}
	printf("result of fourth pop()?\n");
	i = pop(var);
	printf("pop()=%d\n", i);
	push(var, 4140);
	push(var, 5000);
	printf("before clearstack, var->top addr = %p \t var->cnt = %d\n", var->top, var->cnt);
	clearstack(var);
	printf("after clearstack, var->top addr = %p \t var->cnt = %d\n", var->top, var->cnt);
	printf("before destroystack, var addr = %p\n", var);
	destroystack(var);
	var = NULL;
	return 0;
}