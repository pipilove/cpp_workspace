#include <stdio.h>

//* 二分递归算法(序号从0开始) */
int binarySearch(int a[ ], int x, int low, int high){
	if(low > high)
	    return -1;
	int middle = (low + high)/2;
	if(x == a[middle])
	    return middle;
	 if(x > a[middle])
	     return binarySearch(a, x, middle + 1, high);
	  return binarySearch(a, x , low, middle - 1);
}

int __35616165main(){
	int a[6] = {1,3,4,6,7,9}; //已排序
	printf("%d\n", binarySearch(a, 9, 0, 5) );
	return 0;
}
