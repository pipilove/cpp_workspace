#include<iostream>
#include<cstring>
#include<cmath>
#include"Maze.h"
using namespace std;

//代表前进的方向，上下左右
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

//创建路径上的节点
node* create(int x,int y,int cost,double h){
	node* p = new node();
	p->x = x;
	p->y = y;
	p->cost = cost;
	p->h = h;
	return p;
}

Maze::Maze(){
	width = length = entranceX = entranceY = exitX = exitY = 0;
	noPath = true;
	memset(maze,0,sizeof(maze));
	memset(vis,0,sizeof(vis));
	memset(path,0,sizeof(path));
}

//get the infomation of maze
bool Maze::getMaze(){
	for(int i=0;i<width;i++)
		for(int j=0;j<length;j++){
			cin>>maze[i][j];
			if(maze[i][j]!='0'&&maze[i][j]!='1')
				return false;
			path[i][j] = i*1000+j;
		}
		return true;
}

//get the fast way out of maze
void Maze::getPath(){
	Heap* heap = new Heap();//小顶堆，用来存储找到的路径
	bool finished = false;
	node* p = create(entranceX,entranceY,0,0);
	heap->pop(*p);
	vis[entranceX][entranceY] = true;
	delete p;
	while(!heap->isEmpty()&&!finished){
		node tmp = heap->push();
		for(int i = 0;i<4;i++){//往四个方向上移动
			int xx = tmp.x+dx[i],yy = tmp.y+dy[i];
			if(xx>=0&&xx<width&&yy>=0&&yy<length)
				if(!vis[xx][yy]&&maze[xx][yy] == '1'){//可达并且未访问过
					vis[xx][yy] = true;
					path[xx][yy] = tmp.x*1000+tmp.y;
					if((xx==exitX)&&(yy==exitY)){
						finished = true;
						noPath = false;//找到最短路径了
						break;
					}
					else{
						node* temp = create(xx,yy,tmp.cost+1,sqrt((double)((xx-exitX)*(xx-exitX)+(yy-exitY)*(yy-exitY))));
						heap->pop(*temp);
						delete temp;
					}
				}
		}
	}
	delete heap;//删除堆，路径记录在path数组中
	printPath();
}

//mark the way
void Maze::drawPath(int x,int y){//将找到的最短路径标志为*
	maze[x][y] = '*';
	int xx = path[x][y]/1000,/*path/1000即求得x坐标*/yy = path[x][y]%1000;
	if(xx!=x||yy!=y)
		drawPath(xx,yy);
}

//print the way
void Maze::printPath(){
	if(noPath){
		cout<<"There's no way out of maze."<<endl;
		return ;
	}
	drawPath(exitX,exitY);
	cout<<"the shortest way out of maze is as follows:"<<endl;
	for(int i=0;i<width;i++){//输出路径标识为*的路径图
		for(int j=0;j<length;j++)
			cout<<maze[i][j];
		cout<<endl;
	}
}

//set the coordinate of entrance
bool Maze::setEntrance(int x,int y){
	if((x!=0&&x!=width-1)||(y!=0&&y!=length-1))
		return false;
	entranceX = x;
	entranceY = y;
	return true;
}

//set the coordinate of exit
bool Maze::setExit(int x,int y){
	if((x!=0 &&x!=width-1)||(y!=0&&y!=length-1))
		return false;
	exitX = x;
	exitY = y;
	return true;
}

//set the width and length of maze
void Maze::setLW(int width,int length){
	this->width = width;
	this->length = length;
}

Heap::Heap(){
	memset(r,0,sizeof(r));
	count = 0;
}

bool Heap::isEmpty(){
	return count==0;
}

void Heap::pop(node x){//保持最小的代价路径在小顶堆堆顶
	int i = count++,j = (i-1)/2;
	bool finished = false;
	while(i&&!finished){
		if((double)r[j].cost+r[j].h<=(double)x.cost+x.h)
			finished = true;
		else{
			r[i] = r[j];
			i = j;
			j = (i-1)/2;
		}
	}
	r[i] = x;
}

node Heap::push(){
	node ans = r[0];
	r[0] = r[--count];
	sift();
	return ans;
}

void Heap::sift(){
	int i = 0,j = 1;
	node x = r[0];
	bool finished = false;
	while(j<count&&!finished){
		if(j<count&&(double)r[j].cost+r[j].h>(double)r[j+1].cost+r[j+1].h)
			j++;
		if((double)x.cost+x.h<=(double)r[j].cost+r[j].h)
			finished = true;
		else{
			r[i] = r[j];
			i = j;
			j = 2*i+1;
		}
	}
	r[i] = x;
}