/*#define MAXVER 100000
#define MAXLENGTH 200000
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int visited[ MAXVER];
int lock[ MAXVER][2];
int w;
typedef struct arcnode{
	int position;
    struct arcnode *next;
}arcnode;

typedef struct vernode{
	int lock;
    struct arcnode *first;
}vernode;
typedef struct Group{
    vernode  ver[MAXVER];
	int numver,numarc;
}Group;
int CreateALGraph(Group *g){
	int i,j,k,num;
	arcnode *e, *e1;
 	scanf("%d%d",&(g->numver),&(g->numarc));
	for(i=0;i<g->numver;i++){
		g->ver[i].first=NULL;
		g->ver[i].lock=0;
	}
	for(k=0;k<g->numarc;k++){
		scanf("%d%d",&i,&j);
		e1=(arcnode*)malloc(sizeof(arcnode));
		e1->position=i;
		e1->next=g->ver[j].first;
		g->ver[j].first=e1;
        e=(arcnode*)malloc(sizeof(arcnode));
		e->position=j;
		e->next=g->ver[i].first;
		g->ver[i].first=e;
	}
    scanf("%d",&w);
   for(k=0;k<w;k++){
      scanf("%d%d",&i,&j);
      lock[k][0]=i;
      lock[k][1]=j;
	  g->ver[i].lock=1;
    }
   return 0;}

int DFS(Group g,int i){
  int m,j,k,num;
  arcnode *edge;
  visited[i]=1;
  edge=g.ver[i].first;
  for(k=0;k<w;k++)
       if(lock[k][1]==i)
           break;
  if(k<w){
		g.ver[lock[k][0]].lock=0;
	 }
  while(edge){
	j=g.ver[i].first->position;
	if(g.ver[j].lock==1){
	    edge=edge->next;
		if(edge)
		j=edge->position;
    }
	else if(!visited[j])
       DFS(g,j);
	else{
	   edge=edge->next;
	   if(edge){
	   j=edge->position;
	   }
	}
}
return 0;
}

int DFSTraverse(Group g,int j){
 int i;
 for(i=0;i<g.numver;i++)
     visited[i]=0;
 i=0;
 DFS(g,i);
 for(i=0;i<g.numver;i++){
    if(!visited[i])
		break;
 }
	if(i<g.numver)
      printf("Case #%d:No\n",j);
    else
      printf("Case #%d:Yes\n",j);
 return 0;
  }
  int main(){
      Group g;
      int j,T;
      scanf("%d",&T);
      for(j=0;j<T;j++){
      CreateALGraph(&g);
      DFSTraverse(g,j+1);
      }
      return 0;
  }
  */