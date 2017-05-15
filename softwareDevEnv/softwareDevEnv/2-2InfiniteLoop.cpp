/*	测试死循环	
#include "stdio.h"
#include "stdlib.h"

int main(){
	int i;	//比a先压栈
	int a[10];	//a[0]最后压栈
	int c=12;	//15;
	for(i=0;i<=c;i++){	//release版本i直接存在寄存器中，不会越界
		a[i]=0;	//i;则不会死循环
		printf("%d\n",i);
	}
	system("pause");
	return 0;
}
*/