#include <stdio.h>
#pragma warning(disable:4996)

int main(int argc,char** argv) {
	FILE* afile , * bfile;
	char c, buf[100];
	int n;
	fopen_s(&afile ,argv[1], "rb");
	fopen_s(&bfile , argv[2], "wb");
	n = fread(buf, sizeof(char), 100, afile);
	while ( n == 100) {
		fwrite(buf, sizeof(char), 100, bfile);
		n = fread(buf, sizeof(char), 100, afile);
	}
	fwrite(buf, sizeof(char), 100, bfile);
	fclose(afile);
	fclose(bfile);
}