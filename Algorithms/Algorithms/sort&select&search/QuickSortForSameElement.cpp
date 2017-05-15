/*//针对相同元素的快速排序
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <process.h>
const int LEN=10;


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

/*
void main(){
	int A[LEN];
	srand(getpid());	//取得目前进程的进程识别码，不同数组的排序
	for(int k=0;k<LEN;k++){
		//srand(getpid());//相同数组的排序
		A[k]=rand()%200;
		printf("%d   ",A[k]);
	}printf("\n");
	int len=sizeof(A)/sizeof(A[0]);
	//quickSort(A,0,len-1);
	randomizedQuickSort(A,0,len-1);
	//midRandomizedQuickSort(A,0,len-1);？？？

	for(int i=0;i<len;i++)
		printf("%d,",A[i]);

	system("pause");
}
*/