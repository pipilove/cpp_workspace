//*	随机选择第pos大的数		2013.11.20	*/
#include "Partition.h"

//p、r为要在数组A中选择第pos大的数的选择区域
int randomizedSelect(int* A,int p,int r,int pos){
	if(p == r) return A[p];
	int posFind = randomizedPartition(A,p,r);
	if(pos == posFind+1)
		return A[posFind];
	else if(pos < posFind+1)
		return randomizedSelect(A,p,posFind-1,pos);
	else// if(pos > posFind+1)
		return randomizedSelect(A,posFind+1,r,pos);
}

//选择第(i >= 1)大的数
int select(int *A, int k, int low, int high){
	if(low == high)
		return A[low];
	int p = partition(A, low, high);
	int j = p - low + 1;
	if(k == j)
		return A[p];
	if(k < j)
		return select(A, k, low, p - 1);
	return select(A, k - j, p + 1, high);
}

int randomizedSelectFrom0(int* A,int p,int r,int pos){	//p pos都从0开始
	if(p == r) return A[p];
	int posFind = partition(A,p,r);
	if(pos == posFind)
		return A[posFind];
	else if(pos < posFind)
		return randomizedSelect(A,p,posFind - 1,pos);
	else
		return randomizedSelect(A,posFind + 1,r,pos);
}

#include <stdio.h>
int __164651main( ){
	while(1){
		int A[ ] = {6,8,3,5,2,0,8,1};
		int a_len = sizeof(A) / sizeof(A[0]);
		int k;
		scanf("%d", &k);
		printf("%d\n", select(A, k, 0, a_len-1) );
	}
	return 0;
}
