/*	��������Ϊָ��	
#include "stdio.h"
#include "stdlib.h"

void allocateInt(int** i){	//void allocateInt(int* i){
	*i=(int*)malloc(sizeof(int));	//i=(int*)malloc(sizeof(int));
	**i=3;	//*i=3;
}

void main(){
	int* i;
	allocateInt(&i);	//allocateInt(i);��3���ط���������
	printf("i=%d",*i);
}
*/