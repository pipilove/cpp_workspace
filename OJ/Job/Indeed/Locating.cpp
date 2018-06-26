/*
__title__ = 'Weighted Median: Indeed station choose'
__author__ = 'pipi'
__mtime__ = '5/13/17'
__email__ = 'pipijob@126.com'
 Time limit : 2sec / Memory limit : 256MB
Problem Statement

There is a road with a length of L meters that runs east-west, and there are N houses built along this road.The i-th house from the west is located xi meters east of the west end of the road, and there are ri people who live in the house.

A station is going to be built on this road, and there was a discussion on the location of the station.Let the location of the station be P meters east of the west end of the road.According to the law, P must be a integer satisfying 0≤P≤L.After the discussion, it was decided that the location of the station will be chosen so that it minimizes the disutility calculated as follows:
    (disutility) = (the sum of (|xi−P|×ri) over all i (1≤i≤N))
Here, |a| denotes the absolute value of a.
Find the disutility when the location of the station is chosen to minimize it.
Constraints
    All input values are integers.
    1≤L≤1010
    1≤N≤105
    0≤x1<x2<…<xN≤L
    1≤ri≤103

Input
The input is given from Standard Input in the following format:
L N
x1 r1
x2 r2
:
xN rN

Output
Print the disutility when the location of the station is chosen to minimize it.

Sample Input 1
100 3
20 3
50 2
70 1

Sample Output 1
110
When P=40, the disutility is |20−40|×3+|50−40|×2+|70−40|×1=110. There is no location with a lower disutility.

Sample Input 2
100 2
0 1
100 10

Sample Output 2
100
There may be houses at both ends of the road, and the station may also be built at these locations.

Sample Input 3
10000000000 5
3282894320 391
4394338332 929
6932893249 181
7823822843 440
9322388365 623

Sample Output 3
5473201404068

The input values or the expected output may not fit into 32-bit integers.
 */
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

#define N 100000
using namespace std;

struct Node {
    long long value;
    long long weight;
};
Node nodes[N];

//产生一个随即下标，用其对应的数组元素作为比较标准(即一趟快速的主元）
int random(int m, int n) {
    srand((unsigned) time(NULL));
    return m + (rand() % (n - m + 1));
}

//一趟快速排序
int qartition(Node *nodes, int begin, int end) {
    int i = begin - 1, j = begin;
    long long x = nodes[end].value;
    while (j < end) {
        if (nodes[j].value <= x) {
            i++;
            Node temp = nodes[i];
            nodes[i] = nodes[j];
            nodes[j] = temp;
        }
        j++;
    }
    Node temp = nodes[end];
    nodes[end] = nodes[i + 1];
    nodes[i + 1] = temp;
    return i + 1;
}

//一趟随机化快速排序
int random_qartition(Node *nodes, int begin, int end) {
    int q = random(begin, end);
    Node temp = nodes[end];
    nodes[end] = nodes[q];
    nodes[q] = temp;
    return qartition(nodes, begin, end);
}

//随机化快速排序
void random_fast_sort(Node *nodes, int begin, int end) {
    if (begin < end) {
        int p = random_qartition(nodes, begin, end);
        random_fast_sort(nodes, begin, p - 1);
        random_fast_sort(nodes, p + 1, end);
    }
}

//得到带权的中位数
Node GetMidWeight(Node *nodes, int begin, int end, long long SumWeight) {
    long long midSum = 0;
    int i;
    for (i = begin; i <= end; i++) {
        midSum += nodes[i].weight;
        if (midSum >= SumWeight / 2)
            break;
    }
    return nodes[i];
}

int main_locating() {
//int main() {
    long long l;
    cin >> l;
    int n;//数据个数
    cin >> n;
    int i;
    long long sum = 0;
    for (i = 0; i < n; i++) {//每一点值和其权值
        cin >> nodes[i].value >> nodes[i].weight;
        sum += nodes[i].weight;
    }
    random_fast_sort(nodes, 0, n - 1);
//    cout << "邮局位置为：" << endl;
    Node node = GetMidWeight(nodes, 0, n - 1, sum);
//    cout << node.value << endl;
//    cout << "总代价为：" << endl;
    long long sumValue = 0;
    for (i = 0; i < n; i++)
        sumValue += abs(nodes[i].value - node.value) * nodes[i].weight;
//    cout << std::fixed<<sumValue << endl;
    printf("%lld", sumValue);
    return 0;
}
