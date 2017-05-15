/********************************************************************************/
/*	编程之美0.0 - 写一个函数，返回数组中所有元素被第一个元素除的结果 皮皮 2014-6-30	*/
/********************************************************************************/
#include <stdio.h>
using namespace std;

void divide(int *array , int size){
	if(array[0] == 0){
		printf("error : devided by zero\n");
		return;
	}
	for(int i = size - 1 ; i >= 0; i--)	//倒着写，防止array[0]一开始被除为1
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
