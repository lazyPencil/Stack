#pragma once
#include <stdbool.h> // bool,
#include <stdlib.h> // free, malloc,

typedef struct stack {
	int* stack;
	int max;
	int top;
} stack;

stack* createstack(int size);
void push(stack* pstack, int item);
int pop(stack* pstack);
int topcheck(stack* pstack);
void destroystack(stack* pstack);
bool isfullstack(stack* pstack);
bool isemptystack(stack* pstack);
int countstackitem(stack* pstack);
void clearstack(stack* pstack);