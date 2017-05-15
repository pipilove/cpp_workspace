/****************************************************************************/
/*			编程之美1.8 - 小飞的电梯调度算法		皮皮 2014-7-2				*/
/****************************************************************************/
#include <stdio.h>
#include <malloc.h>

int partition(int* A,int p,int r){		//包含p,r
	if(p == r) return p;
	int pivot = A[r];
	int low = p-1;
	int tmp;
	for(int high = p;high<=r-1;high++){
		if(A[high]<pivot){
			low++;
			if(low != high){
			tmp = A[low];
			A[low] = A[high];
			A[high] = tmp;
			}
		}
	}
	A[r] = A[low + 1];
	A[low + 1] = pivot;
	return low + 1;
}

int randomizedSelect(int* A,int p,int r,int pos){	//p pos都从0开始
	if(p == r) return A[p];
	int posFind = partition(A,p,r);
	if(pos == posFind)
		return A[posFind];
	else if(pos < posFind)
		return randomizedSelect(A,p,posFind - 1,pos);
	else
		return randomizedSelect(A,posFind + 1,r,pos);
}

void elevator(){
	int n, i, medium;
	int *a;
	scanf("%d",&n);
	a = (int*)malloc(n * sizeof(int));
	for(i = 0; i < n; i++)
		scanf("%d",&a[i]);	

	medium = randomizedSelect(a,0, n - 1, n / 2);
	printf("%d", medium);
}

int __548415main(){
	elevator();
	return 0;
}