#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"

#ifndef _Stack
#define _Stack
Stack* initial_stack(void) {
	Stack* p;
	p = (Stack*)malloc(1 * sizeof(Stack));
	p->sp = 16;
	int i;
	for (i = 0; i < 16; i++)
	{
		(p->buf)[i] = 0;
	}
	return p;
}
int isFulled(Stack* st) {
	if (st->sp == 0) return 1;
	return 0;
}

int isEmpty(Stack* st) {
	if (st->sp == 100) return 1;
	return 0;
}

void push(Stack* st, int n) {
	if (!isFulled(st)) {
		st->buf[--(st->sp)] = n;
	}
}

int pop(Stack* st) {
	int c;
	if (!isEmpty(st)) {
		c = st->buf[(st->sp)];
		(st->buf)[(st->sp)++] = 0;
	}
	else
	{
		c = 0;
	}
	return c;
}

#endif
