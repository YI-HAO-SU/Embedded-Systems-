#pragma once
typedef struct {
	int data[16];
	int sp;
}Stack;

void initial_stack(Stack* s);
int isempty(Stack* s);
void push(Stack* s, int c);
int pop(Stack* s);
void print_Stacks(Stack* s);

