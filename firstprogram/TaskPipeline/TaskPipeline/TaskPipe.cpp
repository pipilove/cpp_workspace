/**	独立任务最优调度（算法设计与分析习题3.3）	*/
#include <iostream>
using namespace std;

int main(){
	int i,n,j,k,max=0,nmax;
	cout<<"输入任务个数：";
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	int *a=new int[n];//动态给a,b分配内存
	int *b=new int[n];
	cout<<"输入处理机A,B处理作业的时间";
	for(i=0;i<n;i++){
		cin>>a[i];
		if(a[i]>max)
			max=a[i];
	}
	for(i=0;i<n;i++){
		cin>>b[i];
		if(b[i]>max)
			max=b[i];
	}
	//for test
	/*cout<<endl;
	for(i=0;i<n;i++)
		cout<<a[i]<<"*";
	for(i=0;i<n;i++)
		cout<<b[i]<<"*";
	cout<<endl;*/
	nmax=n*max;//A或B处理时间i，j的最大值

	bool ***p=new bool**[nmax+1];//动态建立三维bool类型数组
	for(i=0;i<=nmax;i++)
		p[i]=new bool*[nmax+1];
	for(i=0;i<=nmax;i++)
		for(j=0;j<=nmax;j++)
			p[i][j]=new bool[n+1];

	for(i=0;i<=nmax;i++)//初始化bool数组
		for(j=0;j<=nmax;j++){
			p[i][j][0]=true;
			for(k=1;k<=n;k++)
				p[i][j][k]=false;
		};

	for(k=1;k<=n;k++)//实现动态规划算法
		for(i=0;i<=nmax;i++)
			for(j=0;j<=nmax;j++){
				if(i-a[k-1]>=0){
					p[i][j][k]=p[i-a[k-1]][j][k-1];
					//cout<<"p["<<i<<"]["<<j<<"]["<<k<<"]="<<p[i][j][k]<<endl;
				}
				if(j-b[k-1]>=0){
					p[i][j][k]=(p[i][j][k]||p[i][j-b[k-1]][k-1]);//满足一个就为true
					//cout<<"*p["<<i<<"]"<<"["<<j<<"]"<<"["<<k<<"]="<<p[i][j][k]<<endl;
				}
			};

	int mintime=nmax,tempmax;
	for(i=0;i<=nmax;i++)//计算最短的时间
		for(j=0;j<=nmax;j++)
				if(p[i][j][n]){
					tempmax=(i>j)? i:j;
					if(tempmax<mintime)
						mintime=tempmax;
				};
	cout<<"最短时间为："<<mintime<<endl;

	void traceback();//实现？？？

	system("pause");
	return 0;
}

void traceback(){
}