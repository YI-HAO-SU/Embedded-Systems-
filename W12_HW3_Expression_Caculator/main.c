#include <stdio.h>
#include <conio.h>
#include "Stack.h"
int CalExpression(char* exp);
int getValue(char* exp, int* i);
int priority(char op);
int caculate(char op, int opnd1, int opnd2);

int i = 0;

void main(void) {
	int v;
	char exp[100];

	while (1) {
		printf("Input Expression: ");
		gets_s(exp,100);
		if (exp[0] == 0x00) {
			break;
		}
		i = 0;
		v = CalExpression(exp);
		printf("[%s]=[%d]\n", exp, v);

	}
	getchar();
}

int CalExpression(char *exp) {
	int v, opnd1, opnd2, op, opFlag = 0;
	Stack s[2];  //s[0]:Operand s[1]:Operator

	initial_stack( & (s[0]) );
	initial_stack( & (s[1]) );
	while (exp[i]) {
		if (!opFlag) {
			v = getValue(exp, &i);
			push(&(s[0]), v);
			opFlag = 1;
		}
		else {
			if (isempty(&(s[1]))) {
				push(&(s[1]), exp[i]);	//(int)exp[i]
			}
			else {
				do {
					op = pop(&(s[1]));
					if (priority(exp[i]) > priority((char)op)) {
						push(&(s[1]), op);
						break;
					}
					else {
						opnd2 = pop(&(s[0]));
						opnd1 = pop(&(s[0]));
						v = caculate(op, opnd1, opnd2);
						push(&s[0], v);
					}
				} while (!isempty(&(s[1])));
				push(&s[1], exp[i]);		//(int)exp[i]
			}
			i++;
			opFlag = 0;
		}
	}
	while (!isempty(&(s[1]))) {
		op = pop(&(s[1]));
		opnd2 = pop(&(s[0]));
		opnd1 = pop(&(s[0]));
		v = caculate((char)op, opnd1, opnd2);
		push(&s[0], v);
	}
	v= pop(&(s[0]));
	return v;
}

int getValue(char* exp, int* i) {
	int k, j = 0;
	int v = 0;

	for (k = *i; exp[k] != 0x00 && (exp[k] >= '0' && exp[k] <= '9'); k++)
	{
		v = v * 10 + (exp[k] - '0');
	}
		*i = k;
		return v;
	
}

int priority(char op) {
	int i = 0, v;
	char* ops = (char*)"+-*/";
	int pv[] = { 1,1,2,2,-1 };
	v = -1;
	for ( i = 0; ops[i] &&ops[i]!=op; i++)
	{
		v = pv[i];
	}
	return v;
}

int caculate(char op, int opnd1, int opnd2) {
	int v = 0;

	switch (op){
	case '+': {
		v = opnd1 + opnd2;
		break;
	}
	case '-': {
		v = opnd1 - opnd2;
		break;
	}
	case '*': {
		v = opnd1 * opnd2;
		break;
	}
	case '/': {
		v = opnd1 / opnd2;
		break;
	}
	}
	return v;
}