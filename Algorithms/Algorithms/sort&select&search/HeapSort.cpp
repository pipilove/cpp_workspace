/*	最大堆排序（升序）	2013.10.18	*/
#define parent(i)((i-1)>>1)//((i-1)/2)	//分别返回父结点、左结点和右结点下标,A从下标0开始
#define left(i)((i<<1)+1)//(2*i+1)是不是更快？？？
#define right(i)((i+1)<<1)//(2*i+2)

#include "mySortDefine.h"

//维护最大堆的性质O(lgn)
void maxHeapify000000000000000000000000(int* A,int i,int heapsize){	//i为子树根结点
	int large=i;
	int l=left(i);
	int r=right(i);
	if(l<=heapsize-1&&A[i]<A[l])	//<改为>则是最小堆，降序
		large=l;
	if(r<=heapsize-1&&A[large]<A[r])	//<改为>则是最小堆，降序
		large=r;

	if(large!=i){
		swap(A[i],A[large]);
		maxHeapify000000000000000000000000(A,large,heapsize);
	}
}
//维护最大堆的性质非递归实现
void maxHeapify(int* A,int i,int heapsize){
	int large;
	while(i<=(heapsize-1)/2){	// /2提高效率
		large=i;
		int l=left(i);
		int r=right(i);
		if(l<=heapsize-1&&A[i]<A[l])	//顺序不能反了，否则读取位置...时发生访问冲突;<改为>则是最小堆，降序
			large=l;
		if(r<=heapsize-1&&A[large]<A[r])	//<改为>则是最小堆，降序
			large=r;

		if(large!=i){
			swap(A[i],A[large]);
			i=large;
		}
		else break;
	}
}

//建立最大堆0(n)
void buildMaxHeap(int* A,int heaplength){	//建立堆的过程中maxHeapify中的heapsize=heaplength不变
	for(int i=parent(heaplength);i>=0;i--)
		maxHeapify(A,i,heaplength);
}

//堆排序O(nlgn)
void heapSort(int* A,int heaplength){
	buildMaxHeap(A,heaplength);
	int heapsize=heaplength;	//只为了更好理解
	for(;heapsize>=2;){	
		--heapsize;
		swap(A[0],A[heapsize]);//--heapsize]);则交换时调用3次，heapsize由10变为7
		maxHeapify(A,0,heapsize);	
	}
}
