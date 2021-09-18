#include<stdio.h>
#include <malloc.h>

typedef union {
	float v;
	unsigned char p[4];
	struct {
		unsigned F : 23;
		unsigned E : 8;
		unsigned S : 1;
	};
}Float;


int main(void) {
	
	Float x;
	printf(">>");
	scanf_s("%f", &(x.v));
	printf("[%f]: ", x.v);
	for (int i = 3; i >= 0 ; i--)
	{
		printf(" %2x", x.p[i]);
	}
	printf("\n");
	printf("[S=%x][E=%02x][F=%06x]\n", x.S, x.E, x.F);

	return 0;
}

