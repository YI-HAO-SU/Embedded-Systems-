#include<stdio.h>

void printA(int A[], int n)
{
	int i;
	putchar('\n');
	for (i = 0; i < n; i++)
	{
		printf("%d    ", A[i]);
	}
	putchar('\n');
}

void swap(int* x, int* y) {
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int main(int argc, char* argv[])
{
	int A[10] = { 10,50,66,33,44,88,22,55,49,85 };
	printA(A,10);
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (A[j] < A[j + 1])
			{
				swap(&(A[j]), &(A[j + 1]));
			}
		}
	}
	printA(A, 10);

	return 0;
}
