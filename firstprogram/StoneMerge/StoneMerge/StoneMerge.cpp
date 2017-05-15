/**	圆排列石子合并问题	*/
#include <iostream>
using namespace std;

int minFuction();

int main(){
	int n,i,j,k;
	cout<<"请输入石子堆数： ";
	cin>>n;
	int *stone=new int[n];
	cout<<"请输入各堆石子的个数： ";	
	for(i=0;i<n;i++)
		cin>>stone[i];

	int **m=new int*[n];
	for(i=0;i<n;i++)
		m[i]=new int[n];
	//m[i][j]表示从从第i到第j堆石子合并的最少移动量
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			if(i==j)m[i][j]=0;//单独组合，即本身不移动则移动量为0
			else
				m[i][j]=-1;//初始化
		};
	for(i=0,j=1;i<n;i++,j++)//两两组合，直接求解
			m[i][j]=stone[i]+stone[j];
	for(k=3;k<n;k++)
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
			m[i][j]

	int minFuction();
	return 0;
}

int minFuction();