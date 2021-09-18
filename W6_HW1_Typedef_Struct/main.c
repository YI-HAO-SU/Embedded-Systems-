#include<stdio.h>
#include <malloc.h>

typedef struct {
	char buf[100];
	int sp;
}Stack;

Stack* initial_stack();
int isfull(Stack* st);
int isempty(Stack* st);
char push(Stack* st, char c);
char pop(Stack* st);
void puting(char* s);

Stack* initial_stack(void) {
	Stack* p;
	p = (Stack*)malloc(1 * sizeof(Stack));
	p->sp = 100;		//buf + sp					
	return p;
}

int isfull(Stack* st) {
	if (st->sp == 0) return 1;
	return 0;
}

int isempty(Stack* st) {
	if (st->sp == 100) return 1;
	return 0;
}

char push(Stack* st, char c) {
	if (!isfull(st)) {
		(st->buf)[--(st->sp)] = c;
	}
	else {
		c = 0x00;
	}
	return c;
}

char pop(Stack* st) {
	char c;
	if (!isempty(st)) {
		c = (st->buf)[(st->sp)++];
	}
	else {
		c = 0x00;
	}
	return c;
}

void puting(char* s){
	for (int i = 0; s[i]; i++)
		putchar(s[i]);

	putchar(0x0A);
}

int main(void) {
	Stack* st;
	st = initial_stack();
	char* s = "Hello!";
	puting(s);
	putchar(0x0A);

	int i = 0;
	while (s[i]) {
		push(st, s[i]);						//call by value to change call by reference
		i++;
	}
	while (!isempty(st)) {
		putchar(pop(st));
	}

	return 0;
}

