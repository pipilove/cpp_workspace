/*	������������	2013.10.18	*/
#define parent(i)((i-1)>>1)//((i-1)/2)	//�ֱ𷵻ظ���㡢������ҽ���±�,A���±�0��ʼ
#define left(i)((i<<1)+1)//(2*i+1)�ǲ��Ǹ��죿����
#define right(i)((i+1)<<1)//(2*i+2)

#include "mySortDefine.h"

//ά�����ѵ�����O(lgn)
void maxHeapify000000000000000000000000(int* A,int i,int heapsize){	//iΪ���������
	int large=i;
	int l=left(i);
	int r=right(i);
	if(l<=heapsize-1&&A[i]<A[l])	//<��Ϊ>������С�ѣ�����
		large=l;
	if(r<=heapsize-1&&A[large]<A[r])	//<��Ϊ>������С�ѣ�����
		large=r;

	if(large!=i){
		swap(A[i],A[large]);
		maxHeapify000000000000000000000000(A,large,heapsize);
	}
}
//ά�����ѵ����ʷǵݹ�ʵ��
void maxHeapify(int* A,int i,int heapsize){
	int large;
	while(i<=(heapsize-1)/2){	// /2���Ч��
		large=i;
		int l=left(i);
		int r=right(i);
		if(l<=heapsize-1&&A[i]<A[l])	//˳���ܷ��ˣ������ȡλ��...ʱ�������ʳ�ͻ;<��Ϊ>������С�ѣ�����
			large=l;
		if(r<=heapsize-1&&A[large]<A[r])	//<��Ϊ>������С�ѣ�����
			large=r;

		if(large!=i){
			swap(A[i],A[large]);
			i=large;
		}
		else break;
	}
}

//��������0(n)
void buildMaxHeap(int* A,int heaplength){	//�����ѵĹ�����maxHeapify�е�heapsize=heaplength����
	for(int i=parent(heaplength);i>=0;i--)
		maxHeapify(A,i,heaplength);
}

//������O(nlgn)
void heapSort(int* A,int heaplength){
	buildMaxHeap(A,heaplength);
	int heapsize=heaplength;	//ֻΪ�˸������
	for(;heapsize>=2;){	
		--heapsize;
		swap(A[0],A[heapsize]);//--heapsize]);�򽻻�ʱ����3�Σ�heapsize��10��Ϊ7
		maxHeapify(A,0,heapsize);	
	}
}
