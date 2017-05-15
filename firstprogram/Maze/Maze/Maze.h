//#pragma once
const int MAXN = 100+5;

class Maze{
private:
	int width,length,entranceX,entranceY,exitX,exitY;
	bool noPath;
	char maze[MAXN][MAXN];
	bool vis[MAXN][MAXN];
	int path[MAXN][MAXN];//用来记录路径上点[x][y]的前一个点的坐标

	void drawPath(int x,int y);
	void printPath();
public:
	Maze();
	bool setEntrance(int x,int y);
	bool setExit(int x,int y);
	void setLW(int width,int length);
	bool getMaze();
	void getPath();
};

typedef struct Node{
	int x,y;
	int cost;//从起点到当前点已经花费的距离
	double h;//距离终点的直线距离，贪心选择
}node;


class Heap{
private:
	int count;
	node r[MAXN*MAXN];

	void sift();
public:
	Heap();
	void pop(node x);
	node push();
	bool isEmpty();
};