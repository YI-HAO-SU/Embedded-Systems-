#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include "LinkList.h"

struct BufNode* getnode(void) {
	struct BufNode* ptr;
	ptr = (struct BufNode*)malloc(1 * sizeof(struct BufNode));
	ptr->fptr = ptr->nptr = NULL;						//Initialize
	(ptr->buf)[0] = 0x00;
	return ptr;
}

char delete_char_string(struct BufNode* s) {
	int i = 0;
	struct BufNode* t = s;
	while ((s->buf)[i]) {
		i++;
		if (i == 30) {
			s = s->nptr;
			i = 0;
		}
	}
	if (i == 0) {
		struct BufNode* t = s;
		s = s->fptr;
		if (s == NULL) {											//When last one already NULL can not delete any more
			s = t;														//already the first one
			i = 0;														//set i to 0
			return 0;													//return s to 0
		}
		else {
			free(t);														//release t cause useless 清空ptr不然會一直占用新的空間
			i = 29;														//set i to 99
			s->nptr = NULL;									//????????????????
		}
	}
	else {
		i--;																// i != 0 direct i--
	}
	(s->buf)[i] = 0x00;										//set buf[i] as 0
	return 1;
}

/*char* get_buf(void) {
	char* s;
	s = (char*)malloc(100 * sizeof(char) + sizeof(char*) + sizeof(char*));		//建立起第一組空間
	if (s != NULL) {
		s[0] = 0x00;
		*((char**)&(s[100])) = NULL;
		*((char**)&(s[100 + sizeof(char*)])) = NULL;
	}
	return s;
}*/

char append_char_to_string(struct BufNode* s, char c) {
	int i = 0;
	struct BufNode* t = s;

	while ((s->buf)[i]) {
		i++;
		if (i == 30) {
			s = s->nptr;													//buf load buf[100]  
			i = 0;															//i return to 0
		}
	}
	(s->buf)[i++] = c;												//buf[i++] = c
	if (i == 30) {
		struct BufNode* t = s;										//t load buf
		s = s->nptr = getnode();									//buf value = { get_buf() } return  s
		s->fptr = t;														//讓temp保留原本ptr儲存的前一組的位址資料
		i = 0;
	}
	(s->buf)[i] = 0x00;												//set buf[i] as 0
	return c;
}

void print_string(struct BufNode* buft) {
	int i = 0;
	while ((buft->buf)[i])
	{
		putchar((buft->buf)[i++]);
		if (i == 30)
		{
			buft = buft->nptr;
			i = 0;
		}
	}
}
