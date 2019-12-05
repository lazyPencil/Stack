#include <stdio.h>
#include <stdlib.h> // atoi
#include "stack_array.c"
#define LEN 10
int main(void) {
	stack* pstack = NULL;
	int item,i,error,temp;

	pstack = createstack(LEN);

	printf("input an number. ( %d times )\n", LEN);
	for (i = 0; i < LEN; i++) {
		error = scanf("%d", &item);
		if (error != 1) {
			printf("you didn't enter a number\n");
			i--;
			while (1) {
				if (getchar() == '\n') break;
			}
		} else {
			if ((item >= 0 && item < 10) != 1){
				printf("you have to enter one letter number. input again\n");
				i--;
			} else {
				push(pstack, item);
			}
		}
	}
	while (topcheck(pstack) != -1111) { // Reversing Process // -1111 : error return value
		printf("%d", pop(pstack));
	}
	puts("");
	
	return 0;
}