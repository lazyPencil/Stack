#include "stack_linked.h"

head* createhead(void){
	head* ptr = (head*)malloc(sizeof(head));
	if (ptr == NULL) {
		return NULL;
	}
	ptr->cnt = 0;
	ptr->top = NULL;
	return ptr;
}
void push(head* pstack, int item) {
	stacknode* ptr = (stacknode*)malloc(sizeof(stacknode));
	if (ptr == NULL) { // isfullstack
		printf("new node memory allocation failure\n");
		return;
	}
	ptr->link = pstack->top;
	ptr->data = item;
	pstack->top = ptr;
	(pstack->cnt)++;
}
int pop(head* pstack) {
	int x;
	stacknode* temp = NULL;
	if (pstack->top == NULL) { // isemptystack
		printf("stack is empty...\n");
		return 0;
	}
	x = (pstack->top)->data;
	temp = pstack->top; 
	pstack->top = (pstack->top)->link;
	free(temp);
	(pstack->cnt)--;
	return x;
}
int topcheck(head* pstack) {
	if (pstack->top == NULL) return 0;

	return (pstack->top)->data;
}
void destroystack(head* pstack) {
	clearstack(pstack);
	free(pstack);
}
bool isfullstack(head* pstack) {
	stacknode* ptr = (stacknode*)malloc(sizeof(stacknode));
	if (ptr == NULL) // isfullstack
		return true;
	else {
		free(ptr);
		return false;
	}
}
bool isemptystack(head* pstack) {
	if (pstack->top == NULL)
		return true;
	else
		return false;
}
int countstackitem(head* pstack) {
	return pstack->cnt;
}
void clearstack(head* pstack) {
	stacknode* temp = NULL;
	while (pstack->top != NULL) {
		temp = pstack->top;
		pstack->top = (pstack->top)->link;
		free(temp);
		(pstack->cnt)--;
	}
}