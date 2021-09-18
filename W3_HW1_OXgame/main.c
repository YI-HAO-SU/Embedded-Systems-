#include <stdio.h>

void putsb(char* s, char sbb[]) {
	int i, j = 0;
	for (i = 0; s[i]; i++)
	{
		if ( (s[i] >= '0') && (s[i] <= '9') ) {
			if (sbb[j] == ' ') {
				putchar(s[i]);
			}
			else {
				putchar(sbb[j]);
			}
			j++;
		}
		else {
			putchar(s[i]);
		}
	}
	putchar(0x0A);
}

void display_form(char* pf[], char sb[3][3]) {
	int i, j = 0;
	for ( i = 0; i < 5; i++)
	{
		if (i % 2) {
			printf("%s \n", pf[i]);
		}
		else {
			putsb(pf[i], sb[j++]);
		}
	}
}

int sb_check(char sb[3][3]) {
	int i, j;
	//ROW
	for ( i = 0; i < 3; i++)
	{
		if ((sb[i][0] == sb[i][1]) && (sb[i][1] == sb[i][2]) && (sb[i][0] != ' ')) {
			return 1;
		}
	}
	//COLUMN
	for (j = 0; j < 3; j++)
	{
		if ((sb[0][j] == sb[1][j]) && (sb[1][j] == sb[2][j]) && (sb[0][j] != ' ')) {
			return 1;
		}
	}
	//1 5 9
	if ((sb[0][0] == sb[1][1]) && (sb[1][1] == sb[2][2]) && (sb[0][0] != ' ')) {
		return 1;
	}
	//3 5 7
	if ((sb[0][2] == sb[1][1]) && (sb[1][1] == sb[2][0]) && (sb[0][2] != ' ')) {
		return 1;
	}
	return 0;
}

int main(void) {

	char* playform[] = { "1|2|3",
						"-+-+-",
						"4|5|6",
						"-+-+-",
						"7|8|9", };
	char sb[3][3];
	char turn = 'O';
	int i, j,pos;
	for ( i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++) {
			sb[i][j] = ' ';
		}
	}
	
	for ( i = 0; i < 9; i++)
	{
		display_form(playform, sb);
		printf("\n");
		printf("round %d \n", i+1);
		printf("[%c]>>", turn);
		scanf_s("%d", &pos);

		//note p.3
		//sb[i][j]  i and j def by ¡õ
		//*( (char*)sb + i*column_num + j)
		*((char*)sb + (pos - 1)) = turn;

		if (sb_check(sb))
		{
			display_form(playform, sb);
			printf("[%c] is the winner", turn);
			break;
		}
		turn = (turn == 'O') ? 'X' : 'O';
		
		printf("\n");
	}

	if (i == 9) {
		printf("Draw!!\n");
	}

	getchar( );
}

