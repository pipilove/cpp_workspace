/*//快速排序的栈深度-尾递归
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <process.h>
const int LEN=10;

//一般划分函数
int partition(int* A,int p,int r){
	int pivot=A[r];

	int i=p-1;
	int j,temp;
	for(j=p;j<r;j++){
		if(A[j]<=pivot){
			temp=A[++i];
			A[i]=A[j];
			A[j]=temp;
		}
	}
	A[r]=A[i+1];
	A[i+1]=pivot;//	printf("partition returns i+1 = %d\n",i+1);
	return i+1;	
}

void tailRecursiveQuicksort(int* A,int p,int r){
	int q;
	while(p<r){
		q=partition(A,p,r);
		tailRecursiveQuicksort(A,p,q-1);
		p=q+1;
	}
}


void main(){
	int A[LEN];
	srand(_getpid());
	for(int k=0;k<LEN;k++){
		A[k]=rand()%200;
		printf("%d   ",A[k]);
	}printf("\n");
	int len=sizeof(A)/sizeof(A[0]);
	tailRecursiveQuicksort(A,0,len-1);

	for(int i=0;i<len;i++)
		printf("%d,",A[i]);

	system("pause");
}
*/