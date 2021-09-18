#include <stdio.h>

void _puts(char* S)
{
	int i;
	for (i = 0; S[i]; i++)
	{
		putchar(S[i]);
	}
}

int main(void) {

	char* S0[15]={
		"    **   **    \n",
		"***************\n", 
		"    **   **    \n",
		"  **       *** \n",
		"  ****  ****   \n",
		" **  *    **   \n",
		"**  *     **   \n",
		" ****** ****** \n",
		" ** * *   **   \n",
		" ******  ****  \n",
		" ** * *  ***** \n",
		" ****** **** **\n",
		"        * **  *\n",
		" * * * *  **   \n",
		"*  * * *  **   \n",
	};
	char* S1[15] = {
		"     **       \n",
		"      **      \n",
		"**************\n",
		"**************\n",
		"    **  **    \n",
		"    **  **    \n",
		"  * **  ** *  \n",
		"  * **  ** *  \n",
		" ** **  ** ** \n",
		"**  **  **  **\n",
		"**  **  **  **\n",
		"   **   **    \n",
		"  **    **    \n",
		"***   ****    \n",
		" *     **     \n",
	};
	char* S2[15] = {
		"      **     \n",
		"**************\n",
		"**************\n",
		"             \n",
		"  **********\n",
		"  **      **  \n",
		"**************\n",
		"**          **\n",
		"  **********  \n",
		"    ***   **  \n",
		" *** *** **    \n",
		"    ** ***    \n",
		" ***  *****   \n",
		"   *** ** *** \n",
		" ***  **   ** \n",
	};
		
	for (int i = 0; i < 15; i++)
	{
		_puts(S0[i]);
	};
	for (int i = 0; i < 15; i++)
	{
		_puts(S1[i]);
	};
	for (int i = 0; i < 15; i++)
	{
		_puts(S2[i]);
	};

	return 0;
}