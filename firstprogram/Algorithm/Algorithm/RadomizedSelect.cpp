/**	根据输入数组找出第i小的元素算法	*/
/*
#include <iostream>
#include <ctime>
#include <cstdlib>	
using namespace std;

//1°划分函数（第二种见Petrol.cpp）
int partition(int *a,int p,int r){
	int x=a[p];//选取主元素（枢轴变量）
	while(p<r){
		while(p<r&&a[r]>=x) r--;
		if(p<r) {a[p]=a[r];p++;}
		while(p<r&&a[p]<=x) p++;
		if(p<r) {a[r]=a[p];r--;}
	}
	a[p]=x;
	return p;
}

//随机划分函数
int radomizedPartition(int *a,int p,int r){
	srand((unsigned)time(0));
	int len=r-p+1;
	int i=rand()%len+p;//产生p-r之间的随机数i	//cout<<"i	"<<i<<endl;//for test
	int temp=a[i];//交换随机选择的元素和主元素
	a[i]=a[p];
	a[p]=temp;
	return partition(a,p,r);
}

//随机选择第i小的元素
int radomizedSelect(int *a,int p,int r,int i){
	if(p==r)return a[p];
	int position=radomizedPartition(a,p,r);
	int k=position-p+1;
	if(k==i)return a[position];//注意返回的是a[position]不是a[k]
	else if(k<i)
		return radomizedSelect(a,position+1,r,i-k);
	else
		return radomizedSelect(a,p,position-1,i);
}

int main(){
	int a[]={2,2,4,-2,3};
	int len=sizeof(a)/sizeof(int);
	int midian=radomizedSelect(a,0,len-1,(len+1)/2);//求a[]的中位数
	cout<<"midian: "<<midian<<endl;
	system("pause");
	return 0;
}
*/