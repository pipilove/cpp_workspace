/*
//返回数组A的长度，不安全做法，传入不是指针就会异常，用宏实现（见heapsort）
int length(int* A){
	return sizeof(A)/sizeof(A[0]);
}

//交换两个数的算法（参数为地址）,用宏实现（见heapsort）
void swap(int* a,int* b){
	*a^=*b;
	*b^=*a;
	*a^=*b;
}
*/