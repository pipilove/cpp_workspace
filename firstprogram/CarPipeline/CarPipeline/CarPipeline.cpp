#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

int line1[8];//流水线一
int line2[8];//流水线二
int trans[7];//流水线之间切换时的时间
int fast[2][8];//fast[i][j]代表到达流水线i的第j（从0开始）个装配站
int path[2][8];//记录fast[][]的前一个装配站=1代表由line1得到;全局变量默认为0
int e1,e2,x1,x2;//起点到流水线和流水线到终点的时间
int min1,min2,min3,min4;

void trace(int i,int j,int path[2][8]);
int main(){
	int i,j;
	memset(path,-1,sizeof(path));
	//File * filestream=freopen("test.txt","r",stdin);
	cin>>e1;
	cin>>e2;
	cin>>x1;
	cin>>x2;
	cout<<"请输入流水线一装配站的时间"<<endl;
	for(i=0;i<8;i++)
		cin>>line1[i];
	cout<<"请输入流水线二装配站的时间"<<endl;
	for(i=0;i<8;i++)
		cin>>line2[i];
	cout<<"请输入流水线切换的时间"<<endl;
	for(i=0;i<7;i++)
		cin>>trans[i];
	fast[0][0]=e1+line1[0];
	fast[1][0]=e2+line2[0];
	for(j=1;j<8;j++){
		min1=fast[0][j-1]+line1[j];//由line1得到
		min2=fast[1][j-1]+line1[j]+trans[j-1];//由line2得到
		min3=fast[1][j-1]+line2[j];//由line1得到
		min4=fast[0][j-1]+line2[j]+trans[j-1];//由line1得到
		if(min1>min2){
			fast[0][j]=min2;
			path[0][j]=1;//代表由line1得到
		}
		else{
			fast[0][j]=min1;
			path[0][j]=2;//代表由line2得到
		}
		if(min3>min4){
			fast[1][j]=min4;//代表由line1得到
			path[1][j]=1;
		}
		else{
			fast[1][j]=min3;
			path[1][j]=2;
		}
	}
	if((fast[1][7]+x2)>(fast[0][7]+x1)){
		cout<<"最短时间为"<<fast[0][7]+x1<<endl;
		trace(7,1,path);
	}
	else{
		//cout<<fast[1][0]<<"*"<<fast[1][2]<<"*"<<fast[1][3]<<"*"<<fast[1][4]<<"*"<<fast[1][5]<<"*"<<fast[1][6]<<"*";
		cout<<"最短时间为"<<fast[1][7]+x2<<endl;
		trace(7,2,path);
	}
	//fclose(freopen);
	getchar();
	getchar();
	getchar();
	getchar();
	system("pause");
	return 0;
}

void trace(int i,int j,int path[2][8]){
	if(i==0&&j==1)
		cout<<"start-->line1-0";
	else if(i==0&&j==2)
		cout<<"start-->line2-0";
	if(j==1&&path[0][i]==1){
		trace(i-1,1,path);
		cout<<"-->"<<"line1-"<<i;
	}
	else if(j==1&&path[0][i]==2){
		trace(i-1,2,path);
		cout<<"-->"<<"line1-"<<i;
	}
	else if(j==2&&path[1][i]==1){
		trace(i-1,1,path);
		cout<<"-->"<<"line2-"<<i;
	}
	else if(j==2&&path[1][i]==2){
		trace(i-1,2,path);
		cout<<"-->"<<"line2-"<<i;
	}
}