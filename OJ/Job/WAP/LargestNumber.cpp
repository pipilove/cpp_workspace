/*
__title__ = ''
__author__ = 'pipi'
__mtime__ = '5/26/17'
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

#include <vector>
#include <sstream>

#include <bits/stdc++.h>

using namespace std;


//int main() {
int main_largestnum() {
//    istringstream oss("5 100"
//                              "I 96"
//                              "Q 1"
//                              "I 97"
//                              "Q 1"
//                              "Q 2");
//    cin.rdbuf(oss.rdbuf());


    int m, mod;
//    cin >> m >> mod;
    scanf("%d%d", &m, &mod);
//    cout << m << '*' << mod << endl;

    vector<int> v_largest;
    v_largest.reserve(100000);
    char o;
    int num, t = 0, inst;
    while (m--) {
//        cin >> o >> num;
        scanf("\n%c%d", &o, &num);
        if (o == 'Q') {
            t = v_largest[v_largest.size() - num];
            printf("%d\n", t);
        } else if (o == 'I') {
            inst = (num + t) % mod;
//            v0.push_back(inst);
            vector<int>::reverse_iterator it;
            for (it = v_largest.rbegin(); it != v_largest.rend(); it++) {
                if (inst > *it)
                    *it = inst;
            }
            v_largest.push_back(inst);
        }
    }
    return 0;
}

