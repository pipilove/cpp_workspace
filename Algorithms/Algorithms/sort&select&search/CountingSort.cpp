/*	��������	rang=O(LEN)ʱʹ��	2013.10.19	*/
#include <stdio.h>
#include <stdlib.h>

void countingSort(int* A,int* B,int lower,int upper,int A_length){
	//k���������е�LEN��ΪA���ֵ��A�����ֵ̫��malloc��4*k�����ֽڻᵼ��ջ���
	if (lower > upper) {printf ("The lower must be smaller than the upper\n");exit (1);}
	int i,range=upper-lower+1;
	int* C=(int*)malloc(sizeof(A[0])*range);
	if(C==NULL){
		printf("malloc fail ......");
		exit(0);}
	for(i=0;i<=range-1;i++)	C[i]=0;
	for(i=0;i<=A_length-1;i++)
		++C[A[i]-lower];
	for(i=1;i<=range-1;i++)
		C[i]+=C[i-1];
	for(i=A_length-1;i>=0;i--){
		B[C[A[i]-lower]-1]=A[i];	//B���±�0��ʼ
		--C[A[i]-lower];
	}
	free(C);
}
