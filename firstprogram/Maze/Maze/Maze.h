//#pragma once
const int MAXN = 100+5;

class Maze{
private:
	int width,length,entranceX,entranceY,exitX,exitY;
	bool noPath;
	char maze[MAXN][MAXN];
	bool vis[MAXN][MAXN];
	int path[MAXN][MAXN];//������¼·���ϵ�[x][y]��ǰһ���������

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
	int cost;//����㵽��ǰ���Ѿ����ѵľ���
	double h;//�����յ��ֱ�߾��룬̰��ѡ��
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