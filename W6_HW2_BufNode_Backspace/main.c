#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include "LinkList.h"

int main(void) {
	char c;
	struct BufNode* tbuf, * ubuf;
	tbuf = ubuf = getnode();

	while ((c = _getch()) != 0x1B) {							//0X1B = ESC
		switch (c) {
		case 0x08:														//Backspace
		{
			putchar(c);													//Backspace
			putchar(' ');													//print ' ' cover the last text
			putchar(c);													//Backspace
			int flag = delete_char_string(ubuf);			//
			if (flag == 0)												//
				putchar(0x07);											//BEBE       //BUG : only the first row will success , if enter to next row happen nothing 
			break;															//out of the loop
		}
		case 0x0D:														//Enter
		{
			putchar(c);													//enter 
			putchar(0x0A);											//´«¦æ
			append_char_to_string(ubuf, 0x0A);
			break;
		}
		default:
		{
			putchar(c);
			append_char_to_string(ubuf, c);
		}
		}
	}

	putchar(0x0A);
	printf("==============================================================");
	putchar(0x0A);

	print_string(tbuf);

	return 1;

}