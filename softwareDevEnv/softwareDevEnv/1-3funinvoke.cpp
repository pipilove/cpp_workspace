/*	�������ú;ֲ�����-�Ӻ�������С�ֽ�����	
#include "stdio.h"
#include "stdlib.h"

 int _stdcall Add(int x,int y){	//��ջ��СΪ2^16=64KB
	int sum;
	sum=x+y;
	return sum;
}

void main(){
	int z;
	goto label1;	//goto�е�jmpΪһ���ֽ���ת�ռ�
	z=Add(1,2);	//call�е�jmpΪ�����ֽڵ���ת
label1:
	z=Add(1,23);
	printf("z=%d\n",z);
	system("pause");
}
*/