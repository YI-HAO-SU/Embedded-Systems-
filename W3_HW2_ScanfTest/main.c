#include<stdio.h>
#include<conio.h>

int main(void) {
	char buf[100], c = 0;
	//scanf_s("%s", buf, 100);
	
	//scanf_s test
	int i;
		
	for (i = 0; i < 99; i++) {
		buf[i] = _getch();
		putchar(buf[i]);

		if (buf[i] == 0x0D) {				//Enter
			putchar(0x0A);					//Change to next line 
			buf[i] = 0x00;						//¦r²ÅÃä¬É
			break;
		}
	}
	/*
	int i = 0;
	do {
		c = _getch();
		buf[i] = c;
		i++;
		putchar(c);
	} while (c != 0x0D);
	
	buf[i] = 0x00;
	*/
	
	printf("%s \n",buf);
	return 1;
}