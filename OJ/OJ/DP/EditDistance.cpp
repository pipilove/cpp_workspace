/*
__title__ = '编辑距离'
__author__ = 'pipi'
__mtime__ = '6/8/17'
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
#include <iostream>

using namespace std;

int minDistance(string word1, string word2) {
    int l1 = (int) word1.length();
    int l2 = (int) word2.length();
    int minl = l1 < l2 ? l1 : l2;
    int maxl = l1 > l2 ? l1 : l2;
    string longs, shorts;
    if (maxl == l1) {
        longs = word1;
        shorts = word2;
    } else {
        longs = word2;
        shorts = word1;
    }

    int *dist = new int[minl + 1];
    for (int j = 0; j <= minl; j++)
        dist[j] = j;

    int tmp, old; //old = 没有修改过的dist[j-1]
    for (int i = 1; i <= maxl; i++) { //对长字符串迭代
        dist[0] = i;
        old = i - 1;
        for (int j = 1; j <= minl; j++) { //对短字符串迭代
            tmp = dist[j];
            if (longs[i - 1] == shorts[j - 1])
                dist[j] = old;
            else
                dist[j] = min(dist[j] + 1, min(old + 1, dist[j - 1] + 1));
            old = tmp;
        }
    }
    return dist[minl];
}

//int main() {
int main_edit_dist() {
//    string word1 = "", word2 = "";
//    string word1 = "", word2 = "bcduve";
//    string word1 = "abcde", word2 = "bcduve";
//    string word1 = "plasma", word2 = "altruism";//6
    string word1 = "bedaacbade", word2 = "dccaeedbeb"; //10
    cout << minDistance(word1, word2) << endl;
    return 0;
}

