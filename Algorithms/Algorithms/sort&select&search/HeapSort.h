/*	最大堆排序（升序）	2013.10.18	*/
//维护最大堆的性质O(lgn)
//void maxHeapify(int* A,int i,int heapsize);

//维护最大堆的性质非递归实现
void maxHeapify(int* A,int i,int heapsize);

//建立最大堆0(n)
void buildMaxHeap(int* A,int heaplength);

//堆排序O(nlgn)
void heapSort(int* A,int heaplength);
