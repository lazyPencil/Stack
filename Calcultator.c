#include <stdio.h>
#include <string.h> // strtok() strcpy() strlen() memcpy()
#include <ctype.h> // isdigit()
#include <math.h> // pow() abs()
#include "stack_linked.c"
#define LEN 100
#define PLUS  43							// ASCII CODE
#define MINUS 45
#define MUL   42
#define DIV   47
int myconv(int* arr, int mul10);			// 의미없는 숫자 char 들을 int 모양으로 conv
int priority(int opcode1, char opcode2);		// 현재 스택에 들어있는 연산자와 이제 들어가려고 하는 연산자를 비교
int calculate(head* pstack, int opcode);			// opcode에 해당하는 연산자로 pstack에서 꺼내서 계산해서 반환
int overflow(int result, int op1, int op2, int operat);
int check(char var);

int main(void) {
	char input[LEN+1] = { 0, };
	char postfix[LEN+1] = { 0, };
	char* reptr = input;
	char* ptr = NULL;
	char* ptr2 = NULL;
	char* ptr3 = NULL;
	char* temp = NULL;
	char* reptr2 = postfix;
	char* errorchar = NULL;
	int loca[10] = { 0, };
	int len, i, cnvint = 0, idx = 0, galho = 0, prev, now, error, on, clear = 1;
	head* rand = NULL;
	head* rator = NULL;

	////////////////////////Create Stack
	rand = createhead();
	rator = createhead();
	////////////////////////Loop
	do {
		input[0] = '\0';
		postfix[0] = '\0';
		ptr = reptr;
		ptr2 = reptr;
		temp = reptr;
		ptr3 = reptr2;
		///////////////////////Input DATA
		printf("Question > ");
		errorchar = fgets(ptr, LEN+1, stdin);		// '\0' 한자리
		if (errorchar == NULL) return -1;
		ptr[strlen(ptr) - 1] = '\0';
		printf("입력값 : %s\n", input);
		///////////////////////Tokenize(due to space)
		ptr = strtok(input, " ");
		while (ptr != NULL) {
			len = strlen(ptr);
			temp = strcpy(temp, ptr);
			temp += len;
			ptr = strtok(NULL, " ");
		} // eventually, ptr == NULL
		printf("공백 없앤 입력값 : %s\n", ptr2);
		////////////////////////Verification
		for (i = 0; ptr2[i]; i++) {
			if (galho < 0) {
				printf("ERROR) 열린괄호보다 닫힌괄호가 먼저 놓였습니다\n");
				return -1;
			}
			now = check(ptr2[i]);
			if (now == 0) {
				printf("ERROR) 숫자,연산자,괄호를 제외한 글자는 올 수 없습니다\n");
				return -1;
			}
			else if (i == 0) {
				if ((now == 1) || (now == 3)) {
					if (now == 3) galho++;
					prev = now;
				}
				else {
					printf("ERROR) 첫번째 글자는 숫자 또는 열린괄호가 와야 합니다\n");
					return -1;
				}
			}
			else {
				if (prev == 1) {
					if (now != 3) {
						if (now == 4) galho--;
						prev = now;
					}
					else {
						printf("ERROR) 열린 괄호 앞에 숫자가 올 수 없습니다.\n");
						return -1;
					}
				}
				else if ((prev == 2) || (prev == 3)) {
					if ((now == 1) || (now == 3)) {
						if (now == 3) galho++;
						prev = now;
					}
					else {
						printf("ERROR) 연산자, 닫힌 괄호 앞에 연산자 또는 열린 괄호가 올 수 없습니다.\n");
						return -1;
					}
				}
				else {
					if ((now == 2) || (now == 4)) {
						if (now == 4) galho--;
						prev = now;
					}
					else {
						printf("ERROR) 숫자, 열린 괄호 앞에 닫힌 괄호가 올 수 없습니다.\n");
						return -1;
					}
				}
			}
		}
		if (galho != 0) {
			printf("ERROR) 괄호의 갯수가 맞지 않습니다\n");
			return -1;
		}
		len = 0;
		////////////////////////Converting INFIX into POSTFIX  ptr2 > ptr3
		while(*ptr2) {
			if (*ptr2 == '(')
				push(rator, *ptr2);
			else if (*ptr2 == ')') {
				while (topcheck(rator) != '(') { // '(' 를 만날 때까지
					error = pop(rator);
					if (error == 0) return -1;
					ptr3[idx++] = error;
					ptr3[idx++] = ',';
				}
				pop(rator);						// '(' 마저 꺼내준다.
			}
			else if (isdigit(*ptr2)) { // ptr2 숫자면 숫자 끝나는 지점까지 세서 그만큼 ptr3에 copy
				while (isdigit(ptr2[len])) {
					len++;
				}
				memcpy(ptr3+idx, ptr2, len);
				idx += len;
				ptr3[idx++] = ',';		// 숫자끼리 구분하려고..
				ptr2 += len - 1;		// 끝에 있는 ptr2++ 때문
				len = 0;
			}
			else { // 연산자면
				while (priority(topcheck(rator), *ptr2)) { // 앞이 이기면 작동
					error = pop(rator);
					if (error == 0) return -1;
					ptr3[idx++] = error;
					ptr3[idx++] = ',';
				}
				push(rator, *ptr2);						// 뒤가 이기면 push
			}
			ptr2++;
		}
		while (isemptystack(rator) != true) {
			error = pop(rator);
			if (error == 0) return -1;
			ptr3[idx++] = error;
			ptr3[idx++] = ',';
		}
		printf("POSTFIX : %s\n", postfix);
		ptr3 = reptr2;
		idx = 0;
		////////////////////////Calculating
		for (i = 0; ptr3[i]; i++) {
			if ((ptr3[i] >= 48) && (ptr3[i] <= 57)) {
				if ((ptr3[i+1] >= 48) && (ptr3[i+1] <= 57))
					loca[idx++] = ptr3[i] - 48;
				else {
					loca[idx] = ptr3[i] - 48;
					cnvint = myconv(loca, idx);
					if (cnvint < 0) {
						printf("ERROR) 정수 오버플로우\n");
						return -1;
					}
					push(rand, cnvint);
					idx = 0;
				}
			}
			else if ((ptr3[i]=='+') || (ptr3[i]=='-') || (ptr3[i]=='*') || (ptr3[i]=='/')) {
				error = calculate(rand, ptr3[i]);
				printf("계산 중/// %d\n",topcheck(rand));
				if (error != 1) return -1;
			}
			else {
			}
		}
		printf("Answer > %d\n", pop(rand));
		clearstack(rand);
		clearstack(rator);
		printf("More calculating ? (Yes=1/No=0)\n");
		error = scanf("%d", &on);
		if (error != 1) return -1;
		getchar();											// scanf 에서 버퍼에 남기는 '\n'(10)를 getchar()로 비우기
	} while (on);
	printf("***************\n");
	printf("* * Bye bye * *\n");
	printf("***************\n");
	destroystack(rand);
	destroystack(rator);
	return 0;
}

int myconv(int* arr, int mul10) {
	int i, x = 0;
	for (i = 0; i <= mul10; i++) {
		//printf("%d*(int)pow(10,%d-%d)=%d\n", arr[i], mul10, i, arr[i] * (int)pow(10, (double)(mul10 - i)));
		x += arr[i] * (int)pow(10, (double)(mul10 - i)); // ex : mul10 = 3, 10^2, 10^1, 10^0
	}
	return x;
}
int priority(int opcode1, char opcode2) {
	if (opcode1 == 0) { // topcheck에 든게 없을 경우 1 (즉, 계산)을 반환할 수 없다
		//printf("topcheck(rator)에 든게 없습니다\n");
		return 0;
	}
	if (opcode1 == '(') {
		//printf("topcheck(rator)에 '('가 들었습니다\n");
		return 0;
	}
	//printf("%c(%d) 와 %c(%d)의 우선순위 비교를 합니다.\n", opcode1, opcode1, opcode2, opcode2);
	if (opcode1 == MUL || opcode1 == DIV) {
		//printf("%c가 이김\n", opcode1);
		return 1;
	}
	else {
		if (opcode2 == PLUS || opcode2 == MINUS) {
			//printf("%c가 이김\n", opcode1);
			return 1;
		}
		else {
			//printf("%c가 이김\n", opcode2);
			return 0;
		}
	}
}
int calculate(head * pstack, int opcode) {
	int op1, op2, result;
	switch (opcode) {
	case PLUS:
		op1 = pop(pstack); op2 = pop(pstack);
		result = op2 + op1;
		printf("%d + %d 을 계산합니다\n", op2, op1);
		if (overflow(result, op2, op1, PLUS)) {
			printf("계산 도중 %d + %d = %d 로 오버플로우 발생\n", op2, op1, result);
			return -1;
		}
		push(pstack, result);
		break;
	case MINUS:
		op1 = pop(pstack); op2 = pop(pstack);
		result = op2 - op1;
		printf("%d - %d 을 계산합니다\n", op2, op1);
		if (overflow(result, op2, op1, MINUS)) {
			printf("계산 도중 %d - %d = %d 로 오버플로우 발생\n", op2, op1, result);
			return -1;
		}
		push(pstack, result);
		break;
	case MUL:
		op1 = pop(pstack); op2 = pop(pstack);
		result = op2 * op1;
		printf("%d * %d 을 계산합니다\n", op2, op1);
		if (overflow(result, op2, op1, MUL)) {
			printf("계산 도중 %d * %d = %d 로 오버플로우 발생\n", op2, op1, result);
			return -1;
		}
		push(pstack, result);
		break;
	case DIV:
		op1 = pop(pstack); op2 = pop(pstack);
		if (op1 == 0) {
			printf("계산 도중 %d 를 0으로 나누기 연산을 하는 문제 발생\n", op2);
			return -1;
		}
		result = op2 / op1;
		printf("%d / %d 을 계산합니다\n", op2, op1);
		if (overflow(result, op2, op1, DIV)) {
			printf("계산 도중 %d / %d = %d 로 오버플로우 발생\n", op2, op1, result);
			return -1;
		}
		push(pstack, result);
		break;
	default: return -1;
	}
	return 1;
}
int overflow(int result, int op1, int op2, int operat) {
	int ov, small, big, res = 0, i;

	switch (operat) {
	case PLUS: // + + - , - - +
		if (op1 > 0 && op2 > 0 && result < 0) ov = 1;
		else ov = 0;
		break;
	case MINUS: //
		ov = 0;
		break;
	case MUL: //
		if ((op1 > 0 && op2 > 0) || (op1 < 0 && op2 < 0)) { // +,+ 또는 -,-
			if (result < 0)	ov = 1;
			else {
				ov = 0;
				small = abs(op1) - abs(op2);		// +,+ 면 small>0 때 big=op1 / -,- 면 small<0 때 big=op1
				if (small > 0) {
					small = abs(op2);
					big = abs(op1);
				}
				else {
					small = abs(op1);
					big = abs(op2);
				}
				for (i = 1; i <= small; i++) {			// 곱하기의 오버플로우는 하나씩 계산해봐야 한다.
					res += big;
					if (res < 0) {
						ov = 1;
						break;
					}
				}
			}
		}
		else {		// +,- 또는 -,+
			if (result > 0) ov = 1;
			else {
				ov = 0;
				small = abs(op1) - abs(op2);		// +,+ 면 small>0 때 big=op1 / -,- 면 small<0 때 big=op1
				if (small > 0) {
					small = abs(op2);
					big = abs(op1);
				}
				else {
					small = abs(op1);
					big = abs(op2);
				}
				for (i = 1; i <= small; i++) {			// 곱하기의 오버플로우는 하나씩 계산해봐야 한다.
					res += big;
					if (res < 0) {
						ov = 1;
						break;
					}
				}
			}
		}
		break;
	case DIV: // 
		ov = 0;
		break;
	}
	return ov;
}
int check(char var) {
	int x;
	if (isdigit(var)) // 숫자
		x = 1;
	else if ((var == '+') || (var == '-') || (var == '*') || (var == '/')) // 연산자
		x = 2;
	else if (var == '(') // 열린 괄호
		x = 3;
	else if (var == ')') // 닫힌 괄호
		x = 4;
	else
		x = 0;			 // 에러
	return x;
}