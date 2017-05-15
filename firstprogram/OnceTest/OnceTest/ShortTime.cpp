#include <iostream>
#include <stack>
#include <stdio.h>
const int M=100;
const int N=100;
const int INF=100001;
//const int INT_MAX=100001;
const int CASES=31;
using namespace std;

typedef struct node{
	int matrix[N][M];
	int n; 
	int e;
}MGraph;

void FloydPath(MGraph g,int dist[N][M],int path[N][M]){
	int i,j,k;
	for(i=0;i<g.n;i++)
		for(j=0;j<g.n;j++){
			if(g.matrix[i][j]>0){
				dist[i][j]=g.matrix[i][j];
				path[i][j]=i;
			}
			else{
				if(i!=j){
					dist[i][j]=INT_MAX;
					path[i][j]=-1;
				}
				else{
					dist[i][j]=0;
					path[i][j]=i;
				}
			}
		}
		for(k=0;k<g.n;k++)
			for(i=0;i<g.n;i++)
				for(j=0;j<g.n;j++){
					if((dist[i][k]>0&&dist[i][k]<INT_MAX)&&(dist[k][j]>0&&dist[k][j]<INT_MAX)&&dist[i][k]+dist[k][j]<dist[i][j]){
						dist[i][j]=dist[i][k]+dist[k][j];
						path[i][j]=path[k][j];
					}
				}
}

int __main(){
	int i,j,T,n,m,s,e,p1,p2,k,v,t,w,minTime[CASES],cases=0,minTime1,minTime2,distp,minTimeP;
	scanf("%d",&T);
	MGraph g;
	while(cases!=T){
		scanf("%d%d",&n,&m);
		g.n=n;
		g.e=m;
		int dist[N][M],path[N][M];
		for(i=0;i<g.n;i++)
			for(j=0;j<g.n;j++)
				g.matrix[i][j]=INF;
		for(i=0;i<g.e;i++){
			scanf("%d%d%d",&v,&t,&w);
			g.matrix[v][t]=w;
			g.matrix[t][v]=w;
		}
		scanf("%d%d%d%d%d",&s,&e,&p1,&p2,&k);


		FloydPath(g,dist,path);

		minTime1=dist[s][p1];	printf("minTime1:%d\n",minTime1);
		minTime2=dist[p2][e];	printf("minTime2:%d\n",minTime2);
		distp=dist[p2][p1]*(k-1);	printf("disp:%d\n",distp);
		//g.matrix[p1][p2]=INF;
		g.matrix[p2][p1]=INF;
		FloydPath(g,dist,path);
		if(dist[p2][e]==INF)
			minTimeP=minTime1+minTime2+distp;
		else
			minTimeP=minTime1+minTime2;				printf("minTimeP:%d\n",minTimeP);

		for(i=0;i<n-1;i++)
			g.matrix[i][p1]=INF;
		FloydPath(g,dist,path);
		minTime[cases]=dist[s][e];					printf("minTime[%d]:%d\n",cases,minTime[cases]);

		if(minTime[cases]>minTimeP)
			minTime[cases]=minTimeP;

		cases++;
	}

	for(i=0;i<T;i++){
		if(minTime[i]==INF)
			printf("Case #%d:-1\n",i+1);
		else
			printf("Case #%d:%d\n",i+1,minTime[i]);
	}
	//system("pause");
	return 0;
}
