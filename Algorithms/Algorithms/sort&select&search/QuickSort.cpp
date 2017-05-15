/*	����(����)	2013.10.23	*/
#include "partition.h"

//һ���������
void quickSort(int* A,int low,int high){
	if(low<high){
		int p=partition(A,low,high);
		quickSort(A,low,p-1);
		quickSort(A,p+1,high);
	}
}

//�����������
void randomizedQuickSort(int* A,int p,int r){
	if(p<r){
		int q=randomizedPartition(A,p,r);
		randomizedQuickSort(A,p,q-1);
		randomizedQuickSort(A,q+1,r);
	}
}

//�����λ����������
void midRandomizedQuickSort(int* A,int p,int r){
	if(p<r){
		int q=midRandomPartition(A,p,r);
		midRandomizedQuickSort(A,p,q-1);
		midRandomizedQuickSort(A,q+1,r);
	}
}

//����Ŀ���hoare
void hoareQuickSort(int* A,int p,int r){
	if(p<r){
		int q=hoarePartition(A,p,r);
		hoareQuickSort(A,p,q);	//!!!���ص�qֻ�ܱ�֤>j��������<=j�Ĵ󣬲��ܱ�֤j��<j�Ĵ�
		hoareQuickSort(A,q+1,r);
	}
}


#include <stdio.h>
int __35168351main( ){
	int a[ ] = {4,7,2,5,3,0,9,4,8};
	int a_len = sizeof(a) / sizeof(a[0]);
	quickSort(a, 0, a_len - 1);
	for(int i = 0; i < a_len; i++)
	    printf("%d  ", a[i]);
	return 0;
}
