/*	SPFA算法的邻接矩阵实现	*/
/*
#include <string.h>
#include <iostream>
#include<deque>
using namespace std;

const int MAXN = 10000+2; 
const int INF=999999;
int map[MAXN][MAXN]; //初始输入的i到j的距离
int  dis[MAXN];  
char vst[MAXN];//判断是否在队列中

// n表示结点数，s表示源点  
int SPFA(int n, int s){
    int i, pri, end, p, t;		// pri对头指针，end队尾指针
    memset(vst, 0, sizeof(vst)); //sizeof(vst)=1002
	int *Q=new int[n];
    for(int i=0; i<n; ++i)  
        Q[i] = 0;  
    for (i=0; i<n; i++)  
        dis[i] = INF;  
    dis[s] = 0;  
    vst[s] = 1;  
    Q[0] = s; pri = 0; end = 1;  
    while (pri < end){  
        p = Q[pri];  
        for (i=0; i<n; ++i){
            if (dis[p]+map[p][i] < dis[i]){  
                dis[i] = dis[p]+map[p][i];  
                if (!vst[i]) {  
                    Q[end++] = i;  
                    vst[i] =1;
                }  
            }  
        }  
        vst[p] = 0;   // 置出队的点为未标记  
        pri++;  
    }  
    return 1;  
}  

int main(){
	//freopen("SPFA0input.txt","r",stdin);
	int n,e,s,i,j,v1,v2,flag;
	cout<<"请输入顶bbgfbg点数,边数和源点： ";
	cin>>n>>e>>s;
	cout<<"请输入图的边：";
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			if(i==j)
			map[i][j]=0;
			else
			map[i][j]=INF;
		}
	for(i=0;i<e;i++){
		cin>>v1>>v2;
		cin>>map[v1][v2];
		//cout<<map[v1][v2];
	}
	flag=SPFA(n,s);
	for(i=0;i<n;i++)
		cout<<"从"<<s<<"到顶点"<<i<<"的距离为："<<dis[i]<<endl;
	system("pause");
	return 0;
}
*/