#include <stdio.h>
#include<stdlib.h>


void AMUL(int* A, int* B, int* C, int n) {
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			*(C + i * n + j) = 0;
			for (k = 0; k < n; k++) {
				*(C + i * n + j) += (*(A + i * n + k)) * (*(B + k * n + j));
			}
		}
	}
}

void print_string(int* C, int n) {
	int a = 0;
	for (int i = 0; i < n; i++) {

		if (i > 0)	printf("\n");

		for (int j = 0; j < n; j++) {
			a = *(C + i * n + j) ;
			printf("%2d  ", a);
		}
	}
	
}

int main(void) {
	int A[5][5] = { {1,1,1,1,1},{2,2,2,2,2},{3,3,3,3,3},{4,4,4,4,4},{5,5,5,5,5} };
	int B[5][5] = { {1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1} };
	int C[5][5];
	
	AMUL(A, B, C, 5);
	print_string(C, 5);

	return 0;
}





