#include <stdio.h>
#include<stdlib.h>
typedef struct {
	int buf[10];
	int sp;
}Stack;

Stack* initial_stack(void) {
	Stack* p;
	p = (Stack*)malloc(1 * sizeof(Stack));
	p->sp = 10;
	for (int i = 0; i < 10; i++)
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

void print_stack(Stack** st) {
	int i, j;
	for ( i = 0; i < 3; i++)
	{
		printf(" st[%d] => ",i);
		if(i >= 1)printf(" ");

		for (j = 0; j < 10; j++) {
			printf("%d", (st[i]->buf)[j]);
		}
	}
}

void Tmove(int n, int s, int d, Stack** st);


int main(void)
{
	int n, i;
	Stack* st[3];
	st[0] = initial_stack();
	st[1] = initial_stack();
	st[2] = initial_stack();
	printf("Enter number 1 ~ 10 :\n");
	scanf_s("%d", &n);
	for (i = 0; i < n; i++) {
		push(st[0], n - i);
	}

	printf("First state\n");
	print_stack(st);
	//Tmove(n-1 ,0 ,1,st);
	//Tmove(1 ,0 ,2,st);
	//Tmove(n-1 ,1 ,2,st);
	Tmove(n, 0, 2, st);
	printf("\nFinal state\n");
	print_stack(st);
}

void Tmove(int n, int s, int d, Stack** st)
{
	int temp, n_temp;
	if (n == 1) {
		n_temp = pop(st[s]);
		push(st[d], n_temp);
	}
	else {
		temp = 3 - (s + d);
		Tmove(n - 1, s, temp, st);
		Tmove(1, s, d, st);
		Tmove(n - 1, temp, d, st);
	}
}






