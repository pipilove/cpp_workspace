/*#include <iostream>
#include <stack>
#include <stdio.h>
const int INF=100001;
//const int INT_MAX=100001;
const int CASES=31;
using namespace std;

struct Edge{
	int start;
	int dest;
	int weight;
};

class Node{
public:
	Edge data;
	Node *nextR,*nextD;
	Node(){
		this->nextR=NULL;
		this->nextD=NULL;
	}
	Node(Edge data,Node *nextR=NULL,Node *nextD=NULL){
		this->data=data;
		this->nextR=nextR;
		this->nextD=nextD;
	}
};

class SinglyLinkedList{
public:
	Node *head;

	SinglyLinkedList(){
		this->head=NULL;
	}

	SinglyLinkedList(Edge value[],int n){
		this->head=NULL;

		if(n>0){
			head=new Node(value[0]);
			Node * rear=head;
			int i=1;
			while(i<n){
				rear=new Node (value[i]);
				rear->nextR=rear;
				i++;
				rear=rear->nextR;
			}
		}
	}
};

struct Vertex{
	int data;
	SinglyLinkedList adjlink;
};
template<class T>
class Graph{
public:
	Vertex<T>*vertexlist;
	int size;
	int vertCount;
	int edgeCount;
	int adj[100][100];

	Graph(int size=10){
		this->size=size<10?10:size;
		this->vertexlist=new Vertex<T>[this->size];
		this->vertCount=0;
	}

	Graph(T vert[],int vertCount,Edge edges[],int edgeCount){
		this->size=vertCount<10?10:vertCount;
		this->vertexlist=new Vertex<T>[this->size];
		this->vertCount=0;
		for(int i=0;i<vertCount;i++)
			insertVertex(vert[i]);
		for(int j=0;j<edgeCount;j++)
			insertEdge(edges[j]);
	}

	void insertVertex(T vertex){
		if(vertCount==size){
			Vertex<T>*temp=vertexlist;
			vertexlist=new Vertex<T>[size*2];
			for(int i=0;i<size;i++)
				vertexlist[i]=temp[i];
			size=size*2;
		}
		vertexlist[vertCount].data=vertex;
		vertCount++; 
	}

	void insertEdge(Edge edge){
		insertEdge(edge.start,edge.dest,edge.weight);
	}

	void insertEdge(int i,int j,int weight){
		Edge  ed={i,j,weight};
		Node  *e=new Node(ed);
		Node  *p=vertexlist[i].adjlink.head;
		Node  *q=vertexlist[j].adjlink.head;
		Node *t;
		if(p==NULL) {vertexlist[i].adjlink.head=e;}
		if (p!=NULL)	{   
			while((p!=NULL)&&(p->data.dest<j)){

				if(p->data.start<i) { t=p;p=p->nextD;if(p==NULL){t->nextD=e;e->nextD=p;}}
				else{t=p;p=p->nextR;if(p==NULL){t->nextR=e;e->nextR=p;}}}
			if(t->data.start!=i){t->nextD=e;e->nextD=p;}
			if(t->data.start==i){t->nextR=e;e->nextR=p;}
		}
		if(q==NULL) {vertexlist[j].adjlink.head=e;}
		if(q!=NULL){
			while((q!=NULL)&&(q->data.start<=i)){
				t=q;q=q->nextD;
			}
			t->nextD=e; e->nextD=q;
		}
	}

	void shortPath(){
		int n=vertCount,a,b;
		for( a=0;a<n;a++)
			for( b=0;b<n;b++)
				adj[a][b]=INF;

		for(a=0;a<n;a++)
			for(b=0;b<n;b++){
				Node  *p=vertexlist[a].adjlink.head;
				while(p!=NULL){
					adj[p->data.start][p->data.dest]=p->data.weight;
					adj[p->data.dest][p->data.start]=p->data.weight;
					if(p->data.start==a) p=p->nextR;
					else p=p->nextD;
				}
			}  
			int i,j;
			int **dish=new int*[n];
			int **path=new int*[n];
			for(i=0;i<n;i++){
				dish[i]=new int[n];
				path[i]=new int[n];
				for(j=0;j<n;j++){
					dish[i][j]=adj[i][j];
					if(i!=j&&dish[i][j]<MAX)
						path[i][j]=i;
					else
						path[i][j]=-1;
				}
			}

			for(int k=0;k<n;k++)
				for(i=0;i<n;i++)
					for(j=0;j<n;j++)
						if(i!=j&&(dish[i][j]>dish[i][k]+dish[k][j])){
							dish[i][j]=dish[i][k]+dish[k][j];
							path[i][j]=path[k][j];
						}

	}
};
const int MAX=9999;

int main(){
	int i,j,T,n,m,s,e,p1,p2,k,v,t,w,minTime[CASES],cases=0,minTime1,minTime2,distp,minTimeP;
	scanf("%d",&T);
	MGraph g;
	Edge e;
	while(cases!=T){
		scanf("%d%d",&n,&m);
		g.vertCount=n;
		g.edgeCount=m;
		for(i=0;i<g.edgeCount;i++){
			scanf("%d%d%d",&v,&t,&w);
			e.start=v;
			e.dest=t;
			e.weight=w;
			g.insertEdge(e);
		}
		scanf("%d%d%d%d%d",&s,&e,&p1,&p2,&k);


		g.shortPath();

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

*/