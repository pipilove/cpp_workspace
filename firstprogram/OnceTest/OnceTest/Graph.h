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
	Node<Edge>  *e=new Node<Edge>(ed);
	Node<Edge>  *p=vertexlist[i].adjlink.head;
	Node<Edge>  *q=vertexlist[j].adjlink.head;
	Node<Edge>  *t;
	if(p==NULL) {vertexlist[i].adjlink.head=e;}
	if (p!=NULL)
	{   
		while((p!=NULL)&&(p->data.dest<j))
		{

			if(p->data.start<i) { t=p;p=p->nextD;if(p==NULL){t->nextD=e;e->nextD=p;}}
			else{t=p;p=p->nextR;if(p==NULL){t->nextR=e;e->nextR=p;}}
			/* cout<<p<<"----"<<t<<"----"<<t->data<<"-----p值，p的前面t值，t边的内容"<<endl;*/	}
		if(t->data.start!=i){t->nextD=e;e->nextD=p;}
		if(t->data.start==i){t->nextR=e;e->nextR=p;}
	}
	if(q==NULL) {vertexlist[j].adjlink.head=e;}
	if(q!=NULL)
	{
		while((q!=NULL)&&(q->data.start<=i))
		{
			t=q;q=q->nextD;
		}
		t->nextD=e; e->nextD=q;
	}
}

	void shortPath();
};
const int MAX=9999;

void Graph::shortPath(){
	int n=vertCount,a,b;
	for( a=0;a<n;a++)
		for( b=0;b<n;b++)
			adj[a][b]=MAX;

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