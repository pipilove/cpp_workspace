#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

int line1[8];//��ˮ��һ
int line2[8];//��ˮ�߶�
int trans[7];//��ˮ��֮���л�ʱ��ʱ��
int fast[2][8];//fast[i][j]��������ˮ��i�ĵ�j����0��ʼ����װ��վ
int path[2][8];//��¼fast[][]��ǰһ��װ��վ=1������line1�õ�;ȫ�ֱ���Ĭ��Ϊ0
int e1,e2,x1,x2;//��㵽��ˮ�ߺ���ˮ�ߵ��յ��ʱ��
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
	cout<<"��������ˮ��һװ��վ��ʱ��"<<endl;
	for(i=0;i<8;i++)
		cin>>line1[i];
	cout<<"��������ˮ�߶�װ��վ��ʱ��"<<endl;
	for(i=0;i<8;i++)
		cin>>line2[i];
	cout<<"��������ˮ���л���ʱ��"<<endl;
	for(i=0;i<7;i++)
		cin>>trans[i];
	fast[0][0]=e1+line1[0];
	fast[1][0]=e2+line2[0];
	for(j=1;j<8;j++){
		min1=fast[0][j-1]+line1[j];//��line1�õ�
		min2=fast[1][j-1]+line1[j]+trans[j-1];//��line2�õ�
		min3=fast[1][j-1]+line2[j];//��line1�õ�
		min4=fast[0][j-1]+line2[j]+trans[j-1];//��line1�õ�
		if(min1>min2){
			fast[0][j]=min2;
			path[0][j]=1;//������line1�õ�
		}
		else{
			fast[0][j]=min1;
			path[0][j]=2;//������line2�õ�
		}
		if(min3>min4){
			fast[1][j]=min4;//������line1�õ�
			path[1][j]=1;
		}
		else{
			fast[1][j]=min3;
			path[1][j]=2;
		}
	}
	if((fast[1][7]+x2)>(fast[0][7]+x1)){
		cout<<"���ʱ��Ϊ"<<fast[0][7]+x1<<endl;
		trace(7,1,path);
	}
	else{
		//cout<<fast[1][0]<<"*"<<fast[1][2]<<"*"<<fast[1][3]<<"*"<<fast[1][4]<<"*"<<fast[1][5]<<"*"<<fast[1][6]<<"*";
		cout<<"���ʱ��Ϊ"<<fast[1][7]+x2<<endl;
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