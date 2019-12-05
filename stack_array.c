#include "stack_array.h"

stack* createstack(int size) {
	stack* pstack = (stack*)malloc(sizeof(stack)); // ptr alloc
	if (pstack == NULL) {
		return NULL;
	}
	pstack->stack = (int*)malloc(sizeof(int) * size); // array alloc
	if (pstack->stack == NULL) {
		free(pstack);
		return NULL;
	}
	pstack->max = size;
	pstack->top = -1;

	return pstack;
}
void push(stack* pstack, int item) {
	if (isfullstack(pstack)) {
		printf("stack is full...\n");
		return;
	}
	pstack->stack[++(pstack->top)] = item; // First time, top = -1
}
int pop(stack* pstack) {
	if (isemptystack(pstack)) {
		printf("stack is empty...\n");
		return -1111;
	}
	return pstack->stack[(pstack->top)--];
}
int topcheck(stack* pstack) {
	if (isemptystack(pstack))
		return -1111;
	return pstack->stack[pstack->top];
}
void destroystack(stack* pstack) {
	free(pstack->stack);
	free(pstack);
	pstack = NULL;
	//printf("pstack->stack addr = %p\n", pstack->stack);
}
bool isfullstack(stack* pstack) {
	if (pstack->top == pstack->max - 1)
		return true;
	else
		return false;
}
bool isemptystack(stack* pstack) {
	if (pstack->top == -1)
		return true;
	else
		return false;
}
int countstackitem(stack* pstack) {
	int count = 0;
	int idx = pstack->top;
	while (idx != -1) {
		idx--;
		count++;
	}
	return count;
}
void clearstack(stack* pstack) {
	pstack->top = -1;
}