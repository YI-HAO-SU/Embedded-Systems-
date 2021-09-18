#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

char* get_buf(void);
char append_char_to_string(char* s, char c);
void print_string(char* buft);
int delete_char_string(s);

int delete_char_string(s) {
	int i = 0;
	char* buf, * t;												//指向
	buf = s;														//buf 值為 變數s
	while (buf[i]) {											//buf 之值不為界符
		i++;															
		if (i == 100) {
			buf = *((char**)&buf[i]);					//Type * , **指向&取值
			i = 0;													//Initialize
		}
	}
	if (i == 0) {													//while loop over i==0 go in this part
		t = buf;														//set t to save buf value
		buf = *((char**)&buf[100 + 4]);			//Type * , **指向&取值 +4 : A char
		if (buf == NULL) {									//When last one already NULL can not delete any more
			buf = t;													//already the first one
			i = 0;													//set i to 0
			return 0;												//return s to 0
		}
		else {
			free(t);													//release t cause useless 清空ptr不然會一直占用新的空間
			i = 99;													//set i to 99
			*((char**)&buf[100]) = NULL;			//將整段空間設為空
		}
	}
	else {
		i--;															// i != 0 direct i--
	}
	buf[i] = 0x00;												//set buf[i] as 字串界符
	return 1;
}

char* get_buf(void) {
	char* s;
	s = (char*)malloc(100 * sizeof(char) + sizeof(char*) + sizeof(char*));		//建立起第一組空間  Cast 為*指向 空間排列
	if (s != NULL) {	
		s[0] = 0x00;
		*((char**)&(s[100])) = NULL;																//type * , **指向&取值
		*((char**)&(s[100 + sizeof(char*)])) = NULL;										//Same↑
	}
	return s;
}

char append_char_to_string(char* s, char c) {
	char* buf, * t;
	int i = 0;
	buf = s;
	while (buf[i]) {													//buf 之值不為界符
		i++;
		if (i == 100) {
			buf = *((char**)&buf[i]);							//buf load buf[100]  //Type * , **指向&取值
			if (buf == NULL) {										//if the value = NULL
				buf = *((char**)&buf[i]) = get_buf();	//buf value = { get_buf() } return  s  //重新抓取
				i = 0;														//Initialize
				break;														//out of the loop
			}
			i = 0;															//i return to 0
		}
	}
	buf[i++] = c;														//buf 之末值設定為 c 變數 //main func Case 0x0D 設定為0x0A換行 // default 為直接鍵入
	if (i == 100) {
		t = buf;																//讓temp保留原本buf資料
		buf = *((char**)&buf[i]) = get_buf();			//buf value = { get_buf() } return  s  //重新抓取
		*((char**)&buf[i + sizeof(char)]) = t;			//還原原本temp儲存的前一組的位址資料
		i = 0;																//Initialize
	}
	buf[i] = 0x00;														//set buf[i] as 字串界符
	return c;
}

void print_string(char* buft) {
	int i = 0;
	while (buft[i])														//buf 之值不為界符執行
	{
		putchar(buft[i++]);											//持續輸出值到
		if (i == 100)														//當I為100
		{
			buft = *((char**)&buft[i]);							//type * , **指向&取值  //重新抓取
			i = 0;															//Initialize
		}
	}
}

int main(void){
	char* s , c;
	s = get_buf();

	while ((c = _getch()) != 0x1B) {							//0X1B = ESC
		switch (c) {
			case 0x08:													//Backspace
				{
					putchar(c);											//Backspace
					putchar(' ');											//print ' ' cover the last text
					putchar(c);											//Backspace
					int flag = delete_char_string(s);			//
					if (flag == 0)										//
						putchar(0x07);									//BEBE       //BUG : only the first row will success , if enter to next row happen nothing 
					break;													//out of the loop
				}
			case 0x0D:													//Enter
				{	
					putchar(c);											//enter 
					putchar(0x0A);									//換行
					append_char_to_string(s, 0x0A);		//消除最後一個字符
					break;
				}
			default:														//others 鍵入
				{
					putchar(c);
					append_char_to_string(s, c);				//直接鍵入
				}
		}
	}

	putchar(0x0A);
	print_string(s);														//將儲存之字串輸出

	return 1;

}