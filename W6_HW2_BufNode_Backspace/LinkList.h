#pragma once
struct BufNode {
	char buf[30];
	struct BufNode* nptr, * fptr;
};



struct BufNode* getnode(void);
/*char* get_buf(void);*/
char append_char_to_string(struct BufNode* s, char c);
void print_string(char* buft);
char delete_char_string(struct BufNode* s);
