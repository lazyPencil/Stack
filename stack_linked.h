#pragma once
#include <stdio.h>
#include <stdbool.h> // bool,
#include <stdlib.h> // free, malloc,

typedef struct node {
	int data;
	struct node* link;
} stacknode;

typedef struct head { // head doesn't have any data
	int cnt;
	stacknode* top;
} head;

head* createhead(void);
void push(head* pstack, int item);
int pop(head* pstack);
int topcheck(head* pstack);
void destroystack(head* pstack);
bool isfullstack(head* pstack);
bool isemptystack(head* pstack);
int countstackitem(head* pstack);
void clearstack(head* pstack);
