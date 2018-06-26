/*
__title__ = '未完成'
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
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

int solve(string s) {
//    string::iterator it;
//    for (it = s.begin(); it != s.end(); it++) {
//        cout << "&&" << *it << "&&" << endl;
//    }
    int size = s.size();
    int sum = 0;
    for (int k = 0; k < size; k++) {
//        if (k != 2)
//            continue;
        int dp[k + 1][size - k];
        memset(dp, 0, sizeof(dp));
        int delta = 0;
        for (int i = k - 1; i >= 0; i--)
            for (int j = k + 1; j < size; j++) {
                int x0y0 = dp[k - i - 1][j - k - 1];
                int x0y1 = dp[k - i][j - k - 1];
                int x1y0 = dp[k - i - 1][j - k];
                if (s[i] == s[j]) {//可能需要一个set保存ij之间的那个回文字符串，如果有相同的再进行处理
                    int max = x1y0 > x0y1 ? x1y0 : x0y1;
                    max = x0y0 > max ? x0y0 : max;
                    if (s[i + 1] == s[j - 1] && i != k - 1)
                        delta += 1;
                    dp[k - i][j - k] = max + 1;
                } else
                    dp[k - i][j - k] = x1y0 > x0y1 ? x1y0 : x0y1;
            }
        printf("%d, ", delta);
        printf("%d\n", (1 << dp[k][size - k - 1]) - 2 * delta);
        sum += (1 << dp[k][size - k - 1]) - 2 * delta;
    }
    return sum;
}

//int main() {
int main__oddpalindrome() {
//    stringstream oss("axbcba");
    stringstream oss("aacaa");
    cin.rdbuf(oss.rdbuf());

    string line;
    cin >> line;
    cout << solve(line) << endl;
    return 0;
}

