#include "mySortDefine.h"

//*	������Ԫ�ؽ����Ļ��ֺ���(����)	*/
int partition(int* A, int low, int high){
	int pivot = A[low];
	while(low < high){
		while(low < high && A[high] >= pivot)
		    high--;
		//if(low < high){
		    A[low] = A[high];
		    //low++;
		//}
		while(low < high && A[low] <= pivot)
		    low++;
		//if(low < high){
		    A[high] = A[low];
		    //high--;
		//}
	}
	A[low] = pivot;
	return low;
}

//һ�㻮�ֺ���(�㷨����)
int partition222222222(int* A,int p,int r){		//����p,r
	if(p == r) return p;
	int pivot = A[r];
	int low = p-1;
	for(int high = p;high<=r-1;high++){
		if(A[high]<pivot){				//<=��Ϊ< swap()������������ͬһ����
			printf("%d - %d ---> ", A[low],A[high]);
			low++;
			if(low != high)
			swap(A[high],A[low]);
			printf("%d - %d\n", A[low],A[high]);
		}
	}
	A[r] = A[low + 1];
	A[low + 1] = pivot;					//	printf("partition returns low+1 = %d\n",low);
	return low + 1;
}

//ͬʱ�����ͬԪ�������һ�㻮�ֺ���
int partition11111111111111111111(int* A,int p,int r){
	int pivot=A[r];

	int i=p-1,mid=(p+r)/2;
	int j,temp;
	for(j=p;j<=mid-1;j++){
		if(A[j]<=pivot){
			temp=A[++i];
			A[i]=A[j];
			A[j]=temp;
		}
	}
	for(j=mid;j<=r-1;j++){
		if(A[j]<pivot){
			temp=A[++i];
			A[i]=A[j];
			A[j]=temp;
		}
	}
	A[r]=A[i+1];
	A[i+1]=pivot;
	//printf("partition returns i+1 = %d\n",i+1);
	return i+1;	
}

//������ֺ���
int randomizedPartition(int* A,int p,int r){		//A[]<=>* A
	int pivot_i=random(p,r);
	int temp=A[r];
	A[r]=A[pivot_i];
	A[pivot_i]=temp;
	return partition(A,p,r);	
}

//����汾hoare-partition
int hoarePartition(int* A,int p,int r){
	int pivot=A[p];
	int low=p-1;
	int high=r+1;
	while(1){
		while(A[--high]>pivot);
		while(A[++low]<pivot);
		//	<=> do{--high;}while(A[high]>pivot);	do{++low;}while(A[low]<pivot);
		//	<=> while(--high && A[high] > pivot); while(++low&& A[low] < pivot);
		if(low<high)
			swap(A[low],A[high]);
		else {//printf("return high= %d\n",high);	//���Խ����ͬ���ݷ����м��±�
			return high;
		}
	}
}

//�����λ�����ֺ���
int midRandomPartition(int* A,int p,int r){		//A[]<=>* A
	//int pivot_i=randomizedSelect(A,p,r,(p+r)/2);	//����A��λ���±�
	int pivot_i[3];
	pivot_i[0]=random(p,r);
	pivot_i[1]=random(p,r);
	pivot_i[2]=random(p,r);
	if(A[pivot_i[1]]>A[pivot_i[0]])
		pivot_i[0]=pivot_i[1];
	if(A[pivot_i[2]]>A[pivot_i[0]])
		pivot_i[0]=pivot_i[2];
	int temp=A[r];
	A[r]=A[pivot_i[0]];
	A[pivot_i[0]]=temp;
	return partition(A,p,r);	
}
