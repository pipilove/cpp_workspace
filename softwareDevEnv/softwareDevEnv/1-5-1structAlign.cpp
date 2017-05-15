/*	对齐	
#include "stdio.h"

struct person{
	char c;
	short s;
	char c2;
	int i;
	//double d;
};

void main(){
	person p;
	p.c=1;	//压栈对齐时先考虑c,+1填充
	p.s=2;
	p.c2=3;	//+4填充
	p.i=4;	//不填充
	//p.d=5;
	printf("%d",sizeof(p));	//12;加double d 则为24
}
*/