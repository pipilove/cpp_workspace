/********************************************************************************/
/*	���֮��0.0 - дһ����������������������Ԫ�ر���һ��Ԫ�س��Ľ�� ƤƤ 2014-6-30	*/
/********************************************************************************/
#include <stdio.h>
using namespace std;

void divide(int *array , int size){
	if(array[0] == 0){
		printf("error : devided by zero\n");
		return;
	}
	for(int i = size - 1 ; i >= 0; i--)	//����д����ֹarray[0]һ��ʼ����Ϊ1
		array[i]  /= array[0];
}

int main(){
	int a[10] = {2,13,5,6,4,9,0,98};
	for(int i = 0; i < 10; i++)
		printf("%d ",a[i]);
	divide(a,10);
	for(int i = 0; i < 10; i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
