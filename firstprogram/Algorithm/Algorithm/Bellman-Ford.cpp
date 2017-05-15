/*
* About:  Bellman-Ford�㷨 
*�ñ�����¼ͼ
*/  
/*#include <iostream>  
using namespace std; 

const int maxnum = 100;  
const int maxint = 99999;  

typedef struct Edge{  
	int u, v;    // ��㣬�յ�  
	int weight;  // �ߵ�Ȩֵ  
}Edge;  

Edge edge[maxnum];  
int  dist[maxnum];     // ��㵽Դ����С����  

int nodenum, edgenum, source;    // �������������Դ��  

// ��ʼ��ͼ  
void init(){  
	cout<<"����������������Դ��: ";
	cin >> nodenum >> edgenum >> source;
	for(int i=1; i<=nodenum; ++i)  
		dist[i] = maxint;  
	dist[source] = 0;  
	cout<<"������"<<edgenum<<"����"<<endl;
	for(int i=1; i<=edgenum; ++i){  
		cin >> edge[i].u >> edge[i].v >> edge[i].weight;  
		if(edge[i].u == source)          //���ó�ʼ���  
			dist[edge[i].v] = edge[i].weight;  
	}
}  

// �ɳڼ���  
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
		if(!relaxed)break;//�㷨�Ż������û�б߽����ɳڲ�����ֱ������
	}
	bool flag = 1;  

	// �ж��Ƿ��и���·  
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
		cout<<"��Դ�ڵ㵽�ڵ�"<<i<<"�����·��Ϊ��"<<dist[i] << endl; 
	else
		cout<<"���ڸ���·������������·����"<<endl;
	//}
	getchar();
	getchar();
	system("pause");
	return 0;  
}
*/