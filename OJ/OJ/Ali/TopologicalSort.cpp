/*
__title__ = 'Topological Sorting'
一个测试环境中需要安装很多软件包，这些软件包之间有互相依赖。安装一个包之前，需要先安装它依赖的所有的包。如A依赖B和C，那么要先安装B、C之后，才能安装A。现有一个包依赖关系文件，文件的每一行的有若干个包的名字，空格分隔，第一个包依赖其后的若干个包。如果一行只有一个包，那么这个包不依赖其它包。
写一个程序，读取依赖关系文件，输出一个可行的包安装顺序。
例：
sheep    cow    orange
apple    orange
orange    dog    cat
dog    cow
cow
cat
输出：
cow
dog
cat
orange
sheep
apple
或者cat cow dog orange sheep apple等等都可以
__author__ = 'pipi'
__mtime__ = '5/3/17'
__email__ = 'pipijob@126.com'*/
/* code is far away from bugs with the god animal protecting
    I love animals. They taste delicious.
              ┏┓    ┏┓
            ┏━┛┻━━━━┛┻━┓
            ┃     ☃    ┃
            ┃  ┳┛  ┗┳  ┃
            ┃     ┻    ┃
            ┗━┓      ┏━┛
              ┃      ┗━━━┓
              ┃  神兽保佑  ┣┓
              ┃　永无BUG！ ┏┛
              ┗━┓┓┏━━┳┓┏━┛
                ┃┫┫  ┃┫┫
                ┗┻┛  ┗┻┛
*/
#include<iostream>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <string.h>


using namespace std;

/************************类声明************************/
template<typename T>
class Graph {
    long V;             // 顶点个数
//    list <T> *adj;
    typedef list <T> list_star;
    map<T, list_star> adj;     // 邻接表
    queue<T> q;      // 维护一个入度为0的顶点的集合
//    int *indegree;
    map<string, int> indegree;     // 记录每个顶点的入度
public:
    Graph(set<T> node_set);                   // 构造函数
    ~Graph();                       // 析构函数
    void addEdge(T s, T e);     // 添加边
    bool topological_sort();        // 拓扑排序
};

/************************类定义************************/
template<typename T>
Graph<T>::Graph(set<T> node_set) {
    this->V = node_set.size();
//    adj = new list<int>[node_set];
//    indegree = new int[node_set];  // 入度全部初始化为0
//    for (int i = 0; i < node_set; ++i)
    typename set<T>::iterator it;
    for (it = node_set.begin(); it != node_set.end(); it++)// 入度全部初始化为0
        indegree[*it] = 0;
}

template<typename T>
Graph<T>::~Graph() {
}

template<typename T>
void Graph<T>::addEdge(T s, T e) {
    adj[s].push_back(e);
    ++indegree[e];
}

template<typename T>
bool Graph<T>::topological_sort() {
    typename map<T, int>::iterator it;
    for (it = indegree.begin(); it != indegree.end(); it++)
        if (it->second == 0)
            q.push(it->first);         // 将所有入度为0的顶点入队


    int count = 0;             // 计数，记录当前已经输出的顶点数
    while (!q.empty()) {
        T v = q.front();      // 从队列中取出一个顶点
        q.pop();

        cout << v << " ";      // 输出该顶点
        ++count;
        // 将所有v指向的顶点的入度减1，并将入度减为0的顶点入栈
        typename list<T>::iterator beg = adj[v].begin();
        for (; beg != adj[v].end(); ++beg)
            if (!(--indegree[*beg]))
                q.push(*beg);   // 若入度为0，则入栈
    }

    if (count < V)
        return false;           // 没有输出全部顶点，有向图中有回路
    return true;            // 拓扑排序成功
}

//int main() {
int main_topological() {
    const char *d = " ,*";
    char *p;
    set<string> str_set;
    vector<vector<string> > data;
    data.reserve(8);

    int size = 1024;
    char *line = (char *) malloc(size);
    while (NULL != fgets(line, size, stdin)) {        // read lines
        if (strlen(line) <= 1)
            break;
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        vector<string> temp;
        p = strtok(line, d);
        while (p) {
            string str = p;
//            printf("***%s***", p);
            str_set.insert(str);
            temp.push_back(str);
            p = strtok(NULL, d);
        }
        //  vector<string> v = split(line, " "); //可按多个字符来分隔;
//        printf("%s\n", line.split());
        data.push_back(temp);
    }

    Graph<string> g(str_set);   // 通过顶点创建图

    vector<vector<string> >::iterator it;
    for (it = data.begin(); it != data.end(); it++) {
        int size = (*it).size();
        if (size > 1)
            for (int i = 1; i < size; i++) {
                // g.addEdge((*it)[0],(*it)[i]);
                g.addEdge((*it)[i], (*it)[0]);//图中加边
            }
    }
    g.topological_sort();

    return 0;
}
