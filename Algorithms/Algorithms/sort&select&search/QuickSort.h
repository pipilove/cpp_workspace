/*	快排	2013.10.23	*/
//一般划分函数
int partition(int* A,int p,int r);
//同时解决相同元素排序的一般划分函数
//int partition(int* A,int p,int r);
//随机划分函数
int randomizedPartition(int* A,int p,int r);
//最初版本hoare-partition
void hoarePartition(int* A,int p,int r);

//选择第i小的元素
int select(int *a,int p,int r,int i);
//随机选择第i小的元素???（改为了返回下标）
int randomizedSelect(int *a,int p,int r,int i);
//随机中位数划分函数
int midRandomPartition(int* A,int p,int r);

//一般快速排序
void quickSort(int* A,int p,int r);
//随机快速排序
void randomizedQuickSort(int* A,int p,int r);
//随机中位数快速排序
void midRandomizedQuickSort(int* A,int p,int r);
//最初的快排hoare
void hoareQuickSort(int* A,int p,int r);
