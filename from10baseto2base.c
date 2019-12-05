#include <stdio.h>
#include "stack_linked.c"

int main(void) {
	int dec, error, temp;
	head* var = createhead();
	printf("Input a decimal number you want to convert into binary number...\n");
	error = scanf("%d", &dec);
	if (error != 1) return 1;
	temp = dec;
	while (dec) {
		//printf("dec=%d dec%%2=%d\n", dec, dec % 2);
		push(var, dec % 2);
		dec /= 2;
	}
	printf("%d(10) converts into ", temp);
	while (1) {
		if (topcheck(var) == -1111) break;
		printf("%d", pop(var));
	}
	puts("(2)");
	return 0;
}