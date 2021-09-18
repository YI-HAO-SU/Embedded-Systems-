#include<stdio.h>

int main(void)
{
	float v1, v2, v3;
	unsigned char* buf1;
	unsigned char* buf2;
	unsigned char* buf3;
	v1 = 3.7;
	v2 = 5.3;
	v3 = -4.4;
	buf1 = (unsigned char*)&v1;			//指向v1之位置進行取值 v1為數值非位址故提供位置&
	buf2 = (unsigned char*)&v2;
	buf3 = (unsigned char*)&v3;
	printf("v1 = [%f]\n", v1);				//[%f] float
	printf("%02x %02x %02x %02x\n", buf1[3], buf1[2], buf1[1], buf1[0]);			//IEEE754  
	printf("-----------------------\n");																			// "%02x"  "0 : 缺項補零因不能保證算出來之記憶體位置首部非零" "x : 16bit  2x : 2個16bits"
	printf("v2 = [%f]\n", v2);
	printf("%02x %02x %02x %02x\n", buf2[3], buf2[2], buf2[1], buf2[0]);
	printf("-----------------------\n");
	printf("v3 = [%f]\n", v3);
	printf("%02x %02x %02x %02x\n", buf3[3], buf3[2], buf3[1], buf3[0]);
	return 1;
}