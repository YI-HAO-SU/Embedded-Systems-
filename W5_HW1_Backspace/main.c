#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

char* get_buf(void);
char append_char_to_string(char* s, char c);
void print_string(char* buft);
int delete_char_string(s);

int delete_char_string(s) {
	int i = 0;
	char* buf, * t;												//���V
	buf = s;														//buf �Ȭ� �ܼ�s
	while (buf[i]) {											//buf ���Ȥ����ɲ�
		i++;															
		if (i == 100) {
			buf = *((char**)&buf[i]);					//Type * , **���V&����
			i = 0;													//Initialize
		}
	}
	if (i == 0) {													//while loop over i==0 go in this part
		t = buf;														//set t to save buf value
		buf = *((char**)&buf[100 + 4]);			//Type * , **���V&���� +4 : A char
		if (buf == NULL) {									//When last one already NULL can not delete any more
			buf = t;													//already the first one
			i = 0;													//set i to 0
			return 0;												//return s to 0
		}
		else {
			free(t);													//release t cause useless �M��ptr���M�|�@���e�ηs���Ŷ�
			i = 99;													//set i to 99
			*((char**)&buf[100]) = NULL;			//�N��q�Ŷ��]����
		}
	}
	else {
		i--;															// i != 0 direct i--
	}
	buf[i] = 0x00;												//set buf[i] as �r��ɲ�
	return 1;
}

char* get_buf(void) {
	char* s;
	s = (char*)malloc(100 * sizeof(char) + sizeof(char*) + sizeof(char*));		//�إ߰_�Ĥ@�ժŶ�  Cast ��*���V �Ŷ��ƦC
	if (s != NULL) {	
		s[0] = 0x00;
		*((char**)&(s[100])) = NULL;																//type * , **���V&����
		*((char**)&(s[100 + sizeof(char*)])) = NULL;										//Same��
	}
	return s;
}

char append_char_to_string(char* s, char c) {
	char* buf, * t;
	int i = 0;
	buf = s;
	while (buf[i]) {													//buf ���Ȥ����ɲ�
		i++;
		if (i == 100) {
			buf = *((char**)&buf[i]);							//buf load buf[100]  //Type * , **���V&����
			if (buf == NULL) {										//if the value = NULL
				buf = *((char**)&buf[i]) = get_buf();	//buf value = { get_buf() } return  s  //���s���
				i = 0;														//Initialize
				break;														//out of the loop
			}
			i = 0;															//i return to 0
		}
	}
	buf[i++] = c;														//buf �����ȳ]�w�� c �ܼ� //main func Case 0x0D �]�w��0x0A���� // default ��������J
	if (i == 100) {
		t = buf;																//��temp�O�d�쥻buf���
		buf = *((char**)&buf[i]) = get_buf();			//buf value = { get_buf() } return  s  //���s���
		*((char**)&buf[i + sizeof(char)]) = t;			//�٭�쥻temp�x�s���e�@�ժ���}���
		i = 0;																//Initialize
	}
	buf[i] = 0x00;														//set buf[i] as �r��ɲ�
	return c;
}

void print_string(char* buft) {
	int i = 0;
	while (buft[i])														//buf ���Ȥ����ɲŰ���
	{
		putchar(buft[i++]);											//�����X�Ȩ�
		if (i == 100)														//��I��100
		{
			buft = *((char**)&buft[i]);							//type * , **���V&����  //���s���
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
					putchar(0x0A);									//����
					append_char_to_string(s, 0x0A);		//�����̫�@�Ӧr��
					break;
				}
			default:														//others ��J
				{
					putchar(c);
					append_char_to_string(s, c);				//������J
				}
		}
	}

	putchar(0x0A);
	print_string(s);														//�N�x�s���r���X

	return 1;

}