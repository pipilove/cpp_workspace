/*	函数调用和局部变量-子函数返回小字节数据	
#include "stdio.h"
#include "stdlib.h"

 int _stdcall Add(int x,int y){	//清栈大小为2^16=64KB
	int sum;
	sum=x+y;
	return sum;
}

void main(){
	int z;
	goto label1;	//goto中的jmp为一个字节跳转空间
	z=Add(1,2);	//call中的jmp为两个字节的跳转
label1:
	z=Add(1,23);
	printf("z=%d\n",z);
	system("pause");
}
*/