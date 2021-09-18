#include<stdio.h>

int GCD(int a, int b) {
	if (b == 0)
	{
		return a;
	}
	else
	{
		return GCD(b, a % b);
	}
}

int main(void) {
	int a = 201, b = 48;
	printf("%d", GCD(a, b));

	return 1;
}