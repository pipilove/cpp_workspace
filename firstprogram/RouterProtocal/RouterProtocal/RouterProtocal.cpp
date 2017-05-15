// RouterProtocal.cpp : Defines the entry point for the console application.
/*	第六小组     程序：皮挺 报告：高乐 测试：郝江涛	*/

#include "StdAfx.h"
#include <iostream>  
#include <cstdlib>		//其中定义RAND_MAX，即整数的最大值32767
#include <windows.h>
#include <ctime>		//引入时间头文件，初始化函数保证每次有个不同的随机序列
using namespace std;  

const int MAXN = 100;
const int INF=1000;		//设置一个数，大于INF的看作是无穷大的，即不可达
const int virtualINF = 25;		//随机产生的数中只要是大于virtualINF的都视为无穷大
const int RAND = 1000; 

int matrix[MAXN][MAXN];		//无向图的邻接表  
int minPath[MAXN];			//存储这每个节点到终点的最短路径
int trace[MAXN];			//记录下最短线路  
int vNum;					//节点个数  

int MinDistance(int v){  
	if(minPath[v]>0) return minPath[v];		//记忆化搜索,建立一个查找表，存储的是每个节点到终点的最短路径  
	if(v==vNum-1) return 0;     //边界值，即终点
	int min = INF,minTemp,i,j = 0;		//最短路径存储为min，初始化为INF
	for(i=v+1;i<vNum;i++){				//从v+1开始，防止回溯
		if(matrix[v][i]<INF){		//点v可达的邻接点   
			minTemp = matrix[v][i]+MinDistance(i);  
			if(minTemp<min){ min=minTemp; j=i;}
		}  
	}  
	minPath[v]=min;  
	trace[v]=j;		//trace[i]的值为其下一个节点的值   
	return minPath[v];  
}  

int main(){ 
	int i,j,randNum,minD;
	printf("请输入顶点的个数：(<=100)\t");
	scanf("%d",&vNum);printf("\n");

	while(1){
		memset(minPath,0,sizeof(int)*MAXN);
		memset(trace,0,sizeof(int)*MAXN); 		//初始化minPath0和trace为0！
		srand((unsigned)time(0));		//用当前时间作为随机种子，这样每次序列不同；0即NULL！
		for(i=0;i<vNum;i++){			//绘制顶点图
			for(j=i;j<vNum;j++){
				randNum=rand()/RAND+1;		//随机产生一个[1,RAND_MAX/RAND]的随机整数！
				if(i==j){					//顶点到自己路径长度为0
					matrix[i][j] = 0;
					matrix[j][i] = 0;
				}
				else if(randNum>virtualINF){		//随机产生的书若大于virtualINF则改变路径长度为INF无穷大
					matrix[i][j] = INF;
					matrix[j][i] = INF;
				}
				else{								//否则为产生的随机数
					matrix[i][j] = randNum;
					matrix[j][i] = randNum;
				}
			}
		}

		printf("路由器的无向图的邻接矩阵：\n");
		for(i=0;i<vNum;i++)		//打印出各个顶点间的路径
			for(int j=0;j<vNum;j++){
				printf("%d-",matrix[i][j]);
				if(j==vNum-1) printf("\n");
			}
			printf("\n");

			minD = MinDistance(0);
			printf("最短路径长度：%d\n",minD);  
			i=0;
			printf("路径为 ：1-->");  
			while(minD>0){			//打印出求解出的最短路径！
				printf("%d-->",trace[i]+1);
				minD = minD-matrix[i][trace[i]];  
				i = trace[i];  
			}  
			printf("终点到达\n\n");
			//Sleep(10000);		//每隔10S钟就随机产生数列更新路径
			//system("pause");		//for test
			Sleep(1000);		//for test
			system("cls");
	}
	return 0;  
} 