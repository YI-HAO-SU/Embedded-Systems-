#include<stdio.h>
#include <malloc.h>


struct Stack;
struct Stack* initial_stack(void);
int isfull(struct Stack* st);
int isempty(struct Stack* st);
char push(struct Stack* st, char c);
char pop(struct Stack* st);
void puting(char* s);

struct Stack {
	char buf[100];
	int sp;
};

struct Stack* initial_stack(void) {
	struct Stack* p;
	p = (struct Stack*)malloc(1 * sizeof(struct Stack));	//�]�w�ʺA�Ŷ��s��
	p->sp = 100;																//buf + sp					
	return p;
}

int isfull(struct Stack* st) {
	if (st->sp == 0) return 1;
	return 0;
}

int isempty(struct Stack* st) {
	if (st->sp == 100) return 1;
	return 0;
}

char push(struct Stack* st, char c) {
	if (!isfull(st)) {
		(st->buf)[--(st->sp)] = c;
	}
	else {
		c = 0x00;
	}
	return c;
}

char pop(struct Stack* st) {
	char c;
	if (!isempty(st)) {
		c = (st->buf)[(st->sp)++];
	}
	else {
		c = 0x00;
	}
	return c;
}

void puting(char* s){														//��X�x�s�r��
	for (int i = 0; s[i]; i++)
		putchar(s[i]);

	putchar(0x0A);
}

int main(void) {
	struct Stack* st;
	st = initial_stack();
	char* s = "Hello!";
	puting(s);									//��X�x�s�r��
	putchar(0x0A);

	int i = 0;
	while (s[i]) {							//�����ɲŮɦ���
		push(st, s[i]);						//call by value to change call by reference
		i++;
	}
	while (!isempty(st)) {
		putchar(pop(st));
	}


	return 0;
}

