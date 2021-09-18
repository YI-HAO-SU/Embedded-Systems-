#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>

typedef struct {
	char suit;
	char num;
}card;

void swap(int* x, int* y) {
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
//rearrange card_list value than point to whr struct "card"
void point_arrange	(card *pc) {
	int k;
	for (int i = 0; i < 4 ; i++)
		{
			for (int j =0; j < 13 ; j++)
			{
				k = i * 13 + j;
				pc[k].suit = i;						
				pc[k].num = j + 1;
			}
		}
}

void main(){
	int card_list[5];
	card pc[52];
	srand(time(NULL));
		
	while (1) {
		for (int i = 0; i < 5; i++)
		{
			card_list[i] = (rand() % 51) + 1;
			/*
			for (int j = 0; j < 4; j++)
			{
				if (card_list[j] == card_list[j + 1]) {
					card_list[i] = (rand() % 51) + 1;
				}
			}
			for (int k = 0; k < 3; k++)
			{
				if (card_list[k] == card_list[k + 2]) {
					card_list[i] = (rand() % 51) + 1;
				}
			}
			for (int l = 0; l < 2; l++)
			{
				if (card_list[l] == card_list[l + 3]) {
					card_list[i] = (rand() % 51) + 1;
				}
			}
			for (int m = 0; m < 1; m++)
			{
				if (card_list[m] == card_list[m + 4]) {
					card_list[i] = (rand() % 51) + 1;
				}
			}
			*/
		}

		while( (card_list[0] == card_list[1]) || (card_list[1] == card_list[2]) || (card_list[2] == card_list[3]) || (card_list[3] == card_list[4])) {
			for (int i = 0; i < 5; i++)
			{
				card_list[i] = (rand() % 51) + 1;
			}
		}

		//順子測試
		//card_list[0] = 0, card_list[1] = 1, card_list[2] = 2, card_list[3] = 3, card_list[4] = 4;
		//葫蘆測試1
		//card_list[0] = 0, card_list[1] = 13, card_list[2] = 26, card_list[3] = 1, card_list[4] = 14;
		//葫蘆測試2
		//card_list[0] = 0, card_list[1] = 13, card_list[2] = 1, card_list[3] = 14, card_list[4] = 27;

		point_arrange(pc);
		
		//抽出之卡片號碼
		//printf("%d " "%d ""%d ""%d ""%d \n", card_list[0], card_list[1], card_list[2], card_list[3], card_list[4]);

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (pc[card_list[j]].num > pc[card_list[j + 1]].num)
				{
					swap(&(card_list[j]), &(card_list[j + 1]));
				}
			}
		}

		//num檢查
		//printf("%d " "%d ""%d ""%d ""%d \n", pc[card_list[0]].num, pc[card_list[1]].num, pc[card_list[2]].num, pc[card_list[3]].num, pc[card_list[4]].num);

		printf("本輪之結果為：\n");

		for (int  i = 0; i < 5; i++)
		{
			printf("花色為 %d " "點數為 %d \n", pc[card_list[i]].suit, pc[card_list[i]].num);
		}

		if ( (pc[card_list[0]].num+1 == pc[card_list[1]].num) && (pc[card_list[1]].num+1 == pc[card_list[2]].num) && (pc[card_list[2]].num+1 == pc[card_list[3]].num)&& (pc[card_list[3]].num+1 == pc[card_list[4]].num) ) {
			printf("\n這是順子 \n");
			break;
		}
	
		if ( ((pc[card_list[0]].num  == pc[card_list[1]].num) && (pc[card_list[1]].num == pc[card_list[2]].num ) && (pc[card_list[3]].num == pc[card_list[4]].num)) || (( (pc[card_list[0]].num == pc[card_list[1]].num ) && ( pc[card_list[2]].num == pc[card_list[3]].num) ) && (pc[card_list[3]].num == pc[card_list[4]].num)) ) {
			printf("\n這是葫蘆 \n");
			break;
		}

		printf("\n");


		Sleep(100);
	}



	
}
