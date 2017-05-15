/*	插入排序(升序)	2013.10.23	*/
void insertionSort(int* A,int A_length){
	int j,current_key;
	for(int i=1;i<=A_length-1;i++){
		j=i-1;current_key=A[i];
		while(j>=0&&A[j]>current_key)
			A[j+1]=A[j--];	//只移动不交换
		A[j+1]=current_key;
	}
}
