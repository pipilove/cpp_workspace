/*	函数参数为指针	
#include "stdio.h"
#include "stdlib.h"

void allocateInt(int** i){	//void allocateInt(int* i){
	*i=(int*)malloc(sizeof(int));	//i=(int*)malloc(sizeof(int));
	**i=3;	//*i=3;
}

void main(){
	int* i;
	allocateInt(&i);	//allocateInt(i);改3个地方则程序崩溃
	printf("i=%d",*i);
}
*/