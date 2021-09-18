#include "Stack.h"

void print_stack(Stack** st) {
	int i, j;
	for (i = 0; i < 3; i++)
	{
		printf(" st[%d] => ", i);
		if (i >= 1)printf(" ");

		for (j = 0; j < 16; j++) {
			printf("%d", (st[i]->buf)[j]);
		}
		printf("\n");
	}
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

int main(void)
{
	int n, i;
	Stack* st[3];
	st[0] = initial_stack();
	st[1] = initial_stack();
	st[2] = initial_stack();
	printf("Enter number 1 ~ 16 :\n");
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








