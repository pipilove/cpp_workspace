/*	用邻接表来记录图？	*/
/*
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
vector<edge> myV[maxn];  //利用邻接表建立路径图，每个vector类型的顶点最多存储maxn条边
int numNode,numEdge;    //顶点数、边数
int dist[maxn];       //最短路
int path[maxn];        //path[a]=b，说明a的前驱为b 
int startNode,endNode;           //起点、终点 
bool inQ[maxn];          //是否入队 

void inputItial(){
	int i,from,to,cost;
	for(i=0;i<maxn;i++){  //清空再使用 
		myV[i].clear();
	}
	for(i=0;i<numEdge;i++){   //建无向图
		printf("请输入边的来向，去向，代价：");
		scanf("%d%d%d",&from,&to,&cost); 
		edge e;
		e.cost=cost;
		e.to=to;
		myV[from].push_back(e);		//将输入的边加入到对应的来向点中
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
		printf("到达总代价: %d\n",dist[end]);
	} 
} 
void SPFA(int start,int end){
	memset(inQ,false,sizeof(inQ));		//初始化inQ为false!
	inQ[start]=true;
	for(int j=0;j<maxn;j++) dist[j]=INF;		//初始化距离为无穷
	dist[start]=0;

	deque<int> myQ;		//设立一个队列用来保存待优化的结点
	myQ.push_back(start);

	int now,to,cost;
	while(!myQ.empty()){
		now=myQ.front();
		myQ.pop_front();
		inQ[now]=false;
		int min;		//设置myQ能到达的最小的距离的点

		if(!myV[now].empty()){		//当前点有可以进行松弛判断的边			
				min=myV[now][0].cost;
			for(int k=0;k<myV[now].size();k++){		//对出列的点能到达的边进行松弛操作,k代表边数
				to=myV[now][k].to;
				cost=myV[now][k].cost+dist[now];
				if(dist[to]>cost){
					path[to]=now;    //记录下to的来源为now 
					dist[to]=cost;
					if(!inQ[to]){		//将不在队列中的节点加入到队列中
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

int main(){//未完成
	inputItial();
	return 0;
}
*/