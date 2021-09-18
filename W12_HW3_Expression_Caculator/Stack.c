#include<stdio.h>
#include <conio.h>
#include"Stack.h"


void initial_stack(Stack* s) {
	s->sp = 16;																//將sp設成最後				
}

int isempty(Stack* s) {
	if (s->sp == 16) return 1;
	return 0;
}

void push(Stack* s, int c) {
	if (s->sp == 0) {
		return;
	}
	--s->sp;
	(s->data)[(s->sp)] = c;

}

int pop(Stack* s) {
	if (s->sp == 16) {
		return -1;
	}
	else {
		return s->data[s->sp++];
	}
}
void print_Stacks(Stack* s) {
	int i;

	printf("[s0]=[");

	for (i = 15; i >= s[0].sp; i--) {
		printf("%d, ", s[0].data[i]);
	}

	printf("]\t");
	printf("[s1]=[");

	for (i = 15; i >= s[1].sp; i--) {
		printf("%d, ", s[1].data[i]);
	}

	printf("]\n");

	getchar();
}