/*	最小堆排序(降序)	2013.10.18	
#define arrayLength(A)(sizeof(A)/sizeof(A[0]))
#define swap(a,b)(a^=b,b^=a,a^=b)
#define parent(i)((i-1)/2)
#define left(i)(2*i+1)
#define right(i)(2*i+2)

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
const int LEN=100000;	//定义要排序的数组的大小
const int LOWER=800000;	//定义要排序的数组的最小值
const int UPPER=1000000;	//定义要排序的数组的最大值

int random(int low,int high){
	return rand()%(high-low+1)+low;
}

void minHeapify(int* A,int i,int heapsize){
	int small=i;
	int l=left(i);
	int r=right(i);

	if(l<=heapsize-1&&A[l]<A[small])
		small=l;
	if(r<=heapsize-1&&A[r]<A[small])
		small=r;
	if(small!=i){
		swap(A[i],A[small]);
		minHeapify(A,small,heapsize);
	}
}

void buildMinHeap(int* A,int heaplength){
	for(int i=parent(heaplength);i>=0;i--)
		minHeapify(A,i,heaplength);
}

void minHeapSort(int* A,int heaplength){
	buildMinHeap(A,heaplength);
	for(;heaplength>=2;){
		heaplength--;
		swap(A[0],A[heaplength]);
		minHeapify(A,0,heaplength);
	}
}

void main(){
	int A[LEN];
	srand((unsigned)time(0));
	for(int k=0;k<LEN;k++){
		A[k]=random(LOWER,UPPER);
		//printf("%d   ",A[k]);
	}printf("\n");

	int heaplength=arrayLength(A);
	int startTime=clock();
	minHeapSort(A,heaplength);
	int endTime=clock();

	for(int i=0;i<LEN;i++)
		printf("%d   ",A[i]);
	printf("\nthe running time is: %d\n",endTime-startTime);	//94

	system("pause");
}
*/