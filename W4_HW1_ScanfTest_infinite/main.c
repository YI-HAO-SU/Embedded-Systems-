#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

int main(void) {

	char * buf, * buft, c = 0;
	int i = 0;
	buft = buf = (char*)malloc(100 * sizeof(char) + 1 * sizeof(char*));				//Cast ���V �ʺA�Ŷ� �]�w�ؤo�j�p
	//�D��JEnter
	while (c != 0x0D)					//Enter
	{
		c = _getch();			
		putchar(c);
		buf[i++] = c;						//buf[0]?

		if (c == 0x0D)
		{
			putchar(0x0A);				//����
			//i = i - 1;
		}
		
		if (i == 100)							//Full
		{
			buf = *((char**)&(buf[i])) = (char*)malloc(100 * sizeof(char) + sizeof(char*));				//�]buf�� * ���V�G (*)  ( (char**) ���V &(buf[i]) ����)
			i = 0;								//Initialize
		}
	}
	//��JEnter
	buf[i] = 0x00;							//�r��ɲ�--------------�A�N�̫�@��]�w���r��ɲ�
	putchar(0x0A);						//����							|
													//									|
	i = 0;										//Initialize					|
	while (buft[i])							//��!=0�hTrue�A���������
	{
		putchar(buft[i++]);				//�N�s����buft������X
		if (i==100)							//�P�W�q�ۦP��W�L100�ɡA�N�Ŷ����s���V�ƦC
		{
			buft = *((char**)&buft[i]);
			i = 0;
		}
	}

	return 1;
}