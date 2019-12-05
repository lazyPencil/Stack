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
int myconv(int* arr, int mul10);			// �ǹ̾��� ���� char ���� int ������� conv
int priority(int opcode1, char opcode2);		// ���� ���ÿ� ����ִ� �����ڿ� ���� ������ �ϴ� �����ڸ� ��
int calculate(head* pstack, int opcode);			// opcode�� �ش��ϴ� �����ڷ� pstack���� ������ ����ؼ� ��ȯ
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
		errorchar = fgets(ptr, LEN+1, stdin);		// '\0' ���ڸ�
		if (errorchar == NULL) return -1;
		ptr[strlen(ptr) - 1] = '\0';
		printf("�Է°� : %s\n", input);
		///////////////////////Tokenize(due to space)
		ptr = strtok(input, " ");
		while (ptr != NULL) {
			len = strlen(ptr);
			temp = strcpy(temp, ptr);
			temp += len;
			ptr = strtok(NULL, " ");
		} // eventually, ptr == NULL
		printf("���� ���� �Է°� : %s\n", ptr2);
		////////////////////////Verification
		for (i = 0; ptr2[i]; i++) {
			if (galho < 0) {
				printf("ERROR) ������ȣ���� ������ȣ�� ���� �������ϴ�\n");
				return -1;
			}
			now = check(ptr2[i]);
			if (now == 0) {
				printf("ERROR) ����,������,��ȣ�� ������ ���ڴ� �� �� �����ϴ�\n");
				return -1;
			}
			else if (i == 0) {
				if ((now == 1) || (now == 3)) {
					if (now == 3) galho++;
					prev = now;
				}
				else {
					printf("ERROR) ù��° ���ڴ� ���� �Ǵ� ������ȣ�� �;� �մϴ�\n");
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
						printf("ERROR) ���� ��ȣ �տ� ���ڰ� �� �� �����ϴ�.\n");
						return -1;
					}
				}
				else if ((prev == 2) || (prev == 3)) {
					if ((now == 1) || (now == 3)) {
						if (now == 3) galho++;
						prev = now;
					}
					else {
						printf("ERROR) ������, ���� ��ȣ �տ� ������ �Ǵ� ���� ��ȣ�� �� �� �����ϴ�.\n");
						return -1;
					}
				}
				else {
					if ((now == 2) || (now == 4)) {
						if (now == 4) galho--;
						prev = now;
					}
					else {
						printf("ERROR) ����, ���� ��ȣ �տ� ���� ��ȣ�� �� �� �����ϴ�.\n");
						return -1;
					}
				}
			}
		}
		if (galho != 0) {
			printf("ERROR) ��ȣ�� ������ ���� �ʽ��ϴ�\n");
			return -1;
		}
		len = 0;
		////////////////////////Converting INFIX into POSTFIX  ptr2 > ptr3
		while(*ptr2) {
			if (*ptr2 == '(')
				push(rator, *ptr2);
			else if (*ptr2 == ')') {
				while (topcheck(rator) != '(') { // '(' �� ���� ������
					error = pop(rator);
					if (error == 0) return -1;
					ptr3[idx++] = error;
					ptr3[idx++] = ',';
				}
				pop(rator);						// '(' ���� �����ش�.
			}
			else if (isdigit(*ptr2)) { // ptr2 ���ڸ� ���� ������ �������� ���� �׸�ŭ ptr3�� copy
				while (isdigit(ptr2[len])) {
					len++;
				}
				memcpy(ptr3+idx, ptr2, len);
				idx += len;
				ptr3[idx++] = ',';		// ���ڳ��� �����Ϸ���..
				ptr2 += len - 1;		// ���� �ִ� ptr2++ ����
				len = 0;
			}
			else { // �����ڸ�
				while (priority(topcheck(rator), *ptr2)) { // ���� �̱�� �۵�
					error = pop(rator);
					if (error == 0) return -1;
					ptr3[idx++] = error;
					ptr3[idx++] = ',';
				}
				push(rator, *ptr2);						// �ڰ� �̱�� push
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
						printf("ERROR) ���� �����÷ο�\n");
						return -1;
					}
					push(rand, cnvint);
					idx = 0;
				}
			}
			else if ((ptr3[i]=='+') || (ptr3[i]=='-') || (ptr3[i]=='*') || (ptr3[i]=='/')) {
				error = calculate(rand, ptr3[i]);
				printf("��� ��/// %d\n",topcheck(rand));
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
		getchar();											// scanf ���� ���ۿ� ����� '\n'(10)�� getchar()�� ����
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
	if (opcode1 == 0) { // topcheck�� ��� ���� ��� 1 (��, ���)�� ��ȯ�� �� ����
		//printf("topcheck(rator)�� ��� �����ϴ�\n");
		return 0;
	}
	if (opcode1 == '(') {
		//printf("topcheck(rator)�� '('�� ������ϴ�\n");
		return 0;
	}
	//printf("%c(%d) �� %c(%d)�� �켱���� �񱳸� �մϴ�.\n", opcode1, opcode1, opcode2, opcode2);
	if (opcode1 == MUL || opcode1 == DIV) {
		//printf("%c�� �̱�\n", opcode1);
		return 1;
	}
	else {
		if (opcode2 == PLUS || opcode2 == MINUS) {
			//printf("%c�� �̱�\n", opcode1);
			return 1;
		}
		else {
			//printf("%c�� �̱�\n", opcode2);
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
		printf("%d + %d �� ����մϴ�\n", op2, op1);
		if (overflow(result, op2, op1, PLUS)) {
			printf("��� ���� %d + %d = %d �� �����÷ο� �߻�\n", op2, op1, result);
			return -1;
		}
		push(pstack, result);
		break;
	case MINUS:
		op1 = pop(pstack); op2 = pop(pstack);
		result = op2 - op1;
		printf("%d - %d �� ����մϴ�\n", op2, op1);
		if (overflow(result, op2, op1, MINUS)) {
			printf("��� ���� %d - %d = %d �� �����÷ο� �߻�\n", op2, op1, result);
			return -1;
		}
		push(pstack, result);
		break;
	case MUL:
		op1 = pop(pstack); op2 = pop(pstack);
		result = op2 * op1;
		printf("%d * %d �� ����մϴ�\n", op2, op1);
		if (overflow(result, op2, op1, MUL)) {
			printf("��� ���� %d * %d = %d �� �����÷ο� �߻�\n", op2, op1, result);
			return -1;
		}
		push(pstack, result);
		break;
	case DIV:
		op1 = pop(pstack); op2 = pop(pstack);
		if (op1 == 0) {
			printf("��� ���� %d �� 0���� ������ ������ �ϴ� ���� �߻�\n", op2);
			return -1;
		}
		result = op2 / op1;
		printf("%d / %d �� ����մϴ�\n", op2, op1);
		if (overflow(result, op2, op1, DIV)) {
			printf("��� ���� %d / %d = %d �� �����÷ο� �߻�\n", op2, op1, result);
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
		if ((op1 > 0 && op2 > 0) || (op1 < 0 && op2 < 0)) { // +,+ �Ǵ� -,-
			if (result < 0)	ov = 1;
			else {
				ov = 0;
				small = abs(op1) - abs(op2);		// +,+ �� small>0 �� big=op1 / -,- �� small<0 �� big=op1
				if (small > 0) {
					small = abs(op2);
					big = abs(op1);
				}
				else {
					small = abs(op1);
					big = abs(op2);
				}
				for (i = 1; i <= small; i++) {			// ���ϱ��� �����÷ο�� �ϳ��� ����غ��� �Ѵ�.
					res += big;
					if (res < 0) {
						ov = 1;
						break;
					}
				}
			}
		}
		else {		// +,- �Ǵ� -,+
			if (result > 0) ov = 1;
			else {
				ov = 0;
				small = abs(op1) - abs(op2);		// +,+ �� small>0 �� big=op1 / -,- �� small<0 �� big=op1
				if (small > 0) {
					small = abs(op2);
					big = abs(op1);
				}
				else {
					small = abs(op1);
					big = abs(op2);
				}
				for (i = 1; i <= small; i++) {			// ���ϱ��� �����÷ο�� �ϳ��� ����غ��� �Ѵ�.
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
	if (isdigit(var)) // ����
		x = 1;
	else if ((var == '+') || (var == '-') || (var == '*') || (var == '/')) // ������
		x = 2;
	else if (var == '(') // ���� ��ȣ
		x = 3;
	else if (var == ')') // ���� ��ȣ
		x = 4;
	else
		x = 0;			 // ����
	return x;
}