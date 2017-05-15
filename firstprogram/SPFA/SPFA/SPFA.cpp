// SPFA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<deque>
#include<stack> 
using namespace std;

const int maxn=1001;
const int INF=0x7fffffff;

struct edge{
	int to;
	int cost;
}; 
vector<edge> myV[maxn];  //�����ڽӱ���·��ͼ��ÿ��vector���͵Ķ������洢maxn����
int numNode,numEdge;    //������������
int dist[maxn];       //���·
int path[maxn];        //path[a]=b��˵��a��ǰ��Ϊb 
int startNode,endNode;           //��㡢�յ� 
bool inQ[maxn];          //�Ƿ���� 

void inputItial(){
	int i,from,to,cost;
	for(i=0;i<maxn;i++){  //�����ʹ�� 
		myV[i].clear();
	}
	for(i=0;i<numEdge;i++){   //������ͼ
		printf("������ߵ�����ȥ�򣬴��ۣ�");
		scanf("%d%d%d",&from,&to,&cost); 
		edge e;
		e.cost=cost;
		e.to=to;
		myV[from].push_back(e);		//������ı߼��뵽��Ӧ���������
		e.to=from;
		myV[to].push_back(e);          
	}
}
void output(int start,int end){
	if(dist[end]==INF){
		printf("No Such Path Exist!\n\n");
	} 
	else if(start==end){
		printf("From %d to %d :\n",start,end);
		printf("Path: %d\n",start);
		printf("Total cost : 0\n\n");
	}
	else{ 
		printf("From %d to %d :\n",start,end);  
		printf("Path: %d",start);
		int temp=end; 
		stack<int> s;
		s.push(temp); 
		while(path[temp]!=start){   
			temp=path[temp];
			s.push(temp);    
		}
		while(!s.empty()){
			printf("-->%d",s.top());
			s.pop();
		} 
		printf("\n");
		printf("�����ܴ���: %d\n",dist[end]);
	} 
} 
void SPFA(int start,int end){
	memset(inQ,false,sizeof(inQ));		//��ʼ��inQΪfalse!
	inQ[start]=true;
	for(int j=0;j<maxn;j++) dist[j]=INF;		//��ʼ������Ϊ����
	dist[start]=0;

	deque<int> myQ;		//����һ����������������Ż��Ľ��
	myQ.push_back(start);

	int now,to,cost;
	while(!myQ.empty()){
		now=myQ.front();
		myQ.pop_front();
		inQ[now]=false;
		int min;		//����myQ�ܵ������С�ľ���ĵ�

		if(!myV[now].empty()){		//��ǰ���п��Խ����ɳ��жϵı�			
				min=myV[now][0].cost;
			for(int k=0;k<myV[now].size();k++){		//�Գ��еĵ��ܵ���ı߽����ɳڲ���,k�������
				to=myV[now][k].to;
				cost=myV[now][k].cost+dist[now];
				if(dist[to]>cost){
					path[to]=now;    //��¼��to����ԴΪnow 
					dist[to]=cost;
					if(!inQ[to]){		//�����ڶ����еĽڵ���뵽������
						inQ[to]=true;
						if(myV[now][k].cost<min)
							myQ.push_front(to);
						else
							myQ.push_back(to);
					}
				}
			}
		}
	}

	output(start,end);      
}
int main(){
	printf("�������ĸ����ͱߵĸ���\n");
	while(scanf("%d%d",&numNode,&numEdge)==2,numNode || numEdge){
		inputItial();
	printf("�����������յ� : ");
	while(scanf("%d%d",&startNode,&endNode)==2,startNode!=-1 && endNode!=-1){
			SPFA(startNode,endNode);
		}
	}
	system("pause");   
	return 0;
}

