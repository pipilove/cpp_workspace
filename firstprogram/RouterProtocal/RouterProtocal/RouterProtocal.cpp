// RouterProtocal.cpp : Defines the entry point for the console application.
/*	����С��     ����Ƥͦ ���棺���� ���ԣ��½���	*/

#include "StdAfx.h"
#include <iostream>  
#include <cstdlib>		//���ж���RAND_MAX�������������ֵ32767
#include <windows.h>
#include <ctime>		//����ʱ��ͷ�ļ�����ʼ��������֤ÿ���и���ͬ���������
using namespace std;  

const int MAXN = 100;
const int INF=1000;		//����һ����������INF�Ŀ����������ģ������ɴ�
const int virtualINF = 25;		//�������������ֻҪ�Ǵ���virtualINF�Ķ���Ϊ�����
const int RAND = 1000; 

int matrix[MAXN][MAXN];		//����ͼ���ڽӱ�  
int minPath[MAXN];			//�洢��ÿ���ڵ㵽�յ�����·��
int trace[MAXN];			//��¼�������·  
int vNum;					//�ڵ����  

int MinDistance(int v){  
	if(minPath[v]>0) return minPath[v];		//���仯����,����һ�����ұ��洢����ÿ���ڵ㵽�յ�����·��  
	if(v==vNum-1) return 0;     //�߽�ֵ�����յ�
	int min = INF,minTemp,i,j = 0;		//���·���洢Ϊmin����ʼ��ΪINF
	for(i=v+1;i<vNum;i++){				//��v+1��ʼ����ֹ����
		if(matrix[v][i]<INF){		//��v�ɴ���ڽӵ�   
			minTemp = matrix[v][i]+MinDistance(i);  
			if(minTemp<min){ min=minTemp; j=i;}
		}  
	}  
	minPath[v]=min;  
	trace[v]=j;		//trace[i]��ֵΪ����һ���ڵ��ֵ   
	return minPath[v];  
}  

int main(){ 
	int i,j,randNum,minD;
	printf("�����붥��ĸ�����(<=100)\t");
	scanf("%d",&vNum);printf("\n");

	while(1){
		memset(minPath,0,sizeof(int)*MAXN);
		memset(trace,0,sizeof(int)*MAXN); 		//��ʼ��minPath0��traceΪ0��
		srand((unsigned)time(0));		//�õ�ǰʱ����Ϊ������ӣ�����ÿ�����в�ͬ��0��NULL��
		for(i=0;i<vNum;i++){			//���ƶ���ͼ
			for(j=i;j<vNum;j++){
				randNum=rand()/RAND+1;		//�������һ��[1,RAND_MAX/RAND]�����������
				if(i==j){					//���㵽�Լ�·������Ϊ0
					matrix[i][j] = 0;
					matrix[j][i] = 0;
				}
				else if(randNum>virtualINF){		//�����������������virtualINF��ı�·������ΪINF�����
					matrix[i][j] = INF;
					matrix[j][i] = INF;
				}
				else{								//����Ϊ�����������
					matrix[i][j] = randNum;
					matrix[j][i] = randNum;
				}
			}
		}

		printf("·����������ͼ���ڽӾ���\n");
		for(i=0;i<vNum;i++)		//��ӡ������������·��
			for(int j=0;j<vNum;j++){
				printf("%d-",matrix[i][j]);
				if(j==vNum-1) printf("\n");
			}
			printf("\n");

			minD = MinDistance(0);
			printf("���·�����ȣ�%d\n",minD);  
			i=0;
			printf("·��Ϊ ��1-->");  
			while(minD>0){			//��ӡ�����������·����
				printf("%d-->",trace[i]+1);
				minD = minD-matrix[i][trace[i]];  
				i = trace[i];  
			}  
			printf("�յ㵽��\n\n");
			//Sleep(10000);		//ÿ��10S�Ӿ�����������и���·��
			//system("pause");		//for test
			Sleep(1000);		//for test
			system("cls");
	}
	return 0;  
} 