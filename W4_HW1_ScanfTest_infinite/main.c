#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

int main(void) {

	char * buf, * buft, c = 0;
	int i = 0;
	buft = buf = (char*)malloc(100 * sizeof(char) + 1 * sizeof(char*));				//Cast 指向 動態空間 設定尺寸大小
	//非鍵入Enter
	while (c != 0x0D)					//Enter
	{
		c = _getch();			
		putchar(c);
		buf[i++] = c;						//buf[0]?

		if (c == 0x0D)
		{
			putchar(0x0A);				//換行
			//i = i - 1;
		}
		
		if (i == 100)							//Full
		{
			buf = *((char**)&(buf[i])) = (char*)malloc(100 * sizeof(char) + sizeof(char*));				//因buf為 * 指向故 (*)  ( (char**) 指向 &(buf[i]) 取值)
			i = 0;								//Initialize
		}
	}
	//鍵入Enter
	buf[i] = 0x00;							//字串界符--------------，將最後一位設定為字串界符
	putchar(0x0A);						//換行							|
													//									|
	i = 0;										//Initialize					|
	while (buft[i])							//值!=0則True，直到↑成立
	{
		putchar(buft[i++]);				//將存取之buft全部輸出
		if (i==100)							//與上段相同當超過100時，將空間重新指向排列
		{
			buft = *((char**)&buft[i]);
			i = 0;
		}
	}

	return 1;
}