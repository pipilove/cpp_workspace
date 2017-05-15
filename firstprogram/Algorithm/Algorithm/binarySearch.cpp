//有序数组的二分查找
/*#include <iostream>
using namespace std;

int binarySearch(int a[],int x,int n){
	int low=0,high=n-1;
	int mid;
	while(low<=high){	//	<=
		mid=(low+high)/2;
		if(x==a[mid])return mid;
		else if(x<a[mid])high=mid-1;
		else low=mid+1;
	}
	return 0;
}

int main(){
	int n,i,x,pos;
	int *a;
	cout<<"输入数组大小：";
	cin>>n;
	a=new int[n];
	cout<<"输入数组元素(0-"<<n<<")：";
	for(i=0;i<n;i++)
		cin>>a[i];
	cout<<"输入要查询的数：";
	cin>>x;
	pos=binarySearch(a,x,n);
	cout<<"要查找的数字的位置为："<<pos<<endl;
	system ("pause");
	return 0;
}
*/