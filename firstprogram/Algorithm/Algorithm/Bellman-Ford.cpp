/*
* About:  Bellman-Ford算法 
*用边来记录图
*/  
/*#include <iostream>  
using namespace std; 

const int maxnum = 100;  
const int maxint = 99999;  

typedef struct Edge{  
	int u, v;    // 起点，终点  
	int weight;  // 边的权值  
}Edge;  

Edge edge[maxnum];  
int  dist[maxnum];     // 结点到源点最小距离  

int nodenum, edgenum, source;    // 结点数，边数，源点  

// 初始化图  
void init(){  
	cout<<"输入结点数，边数，源点: ";
	cin >> nodenum >> edgenum >> source;
	for(int i=1; i<=nodenum; ++i)  
		dist[i] = maxint;  
	dist[source] = 0;  
	cout<<"请输入"<<edgenum<<"条边"<<endl;
	for(int i=1; i<=edgenum; ++i){  
		cin >> edge[i].u >> edge[i].v >> edge[i].weight;  
		if(edge[i].u == source)          //设置初始情况  
			dist[edge[i].v] = edge[i].weight;  
	}
}  

// 松弛计算  
bool relax(int u, int v, int weight){  
	bool relaxed=false;
	if(dist[v] > dist[u] + weight){  
		dist[v] = dist[u] + weight;
	relaxed=true;
	}
	return relaxed;
}  

bool Bellman_Ford(){  
	bool relaxed=false;
	for(int i=1; i<=nodenum-1; ++i){
		for(int j=1; j<=edgenum; ++j)  
			if(relax(edge[j].u, edge[j].v, edge[j].weight))
				relaxed=true;
		if(!relaxed)break;//算法优化，如果没有边进行松弛操作就直接跳出
	}
	bool flag = 1;  

	// 判断是否有负环路  
	for(int i=1; i<=edgenum; ++i)  
		if(dist[edge[i].v] > dist[edge[i].u] + edge[i].weight){  
			flag = 0;  
			break;  
		}
	return flag;  
}  

int main(){  
	freopen("input.txt", "r", stdin);  
	//while(1){//for test
	init();  
	if(Bellman_Ford())
		for(int i = 1 ;i <= nodenum; i++)  
		cout<<"从源节点到节点"<<i<<"的最短路径为："<<dist[i] << endl; 
	else
		cout<<"存在负环路，不能求出最短路径！"<<endl;
	//}
	getchar();
	getchar();
	system("pause");
	return 0;  
}
*/