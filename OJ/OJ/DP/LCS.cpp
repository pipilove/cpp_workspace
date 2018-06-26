/*
__title__ = '最长公共子序列'
  @param A, B: Two strings.
  @return: The length of longest common subsequence of A and B.
__author__ = 'pipi'
__mtime__ = '6/4/17'
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

void printLCS(string A, string B, int i, int j, int **opt);

int longestCommonSubsequence0(string A, string B) {
    /*
     * 仅输出lcs最优值(空间可以更少，弃用)
     */
    unsigned long la = A.length() + 1;
    unsigned long lb = B.length() + 1;
    unsigned long l_min = la <= lb ? la : lb;
    unsigned long l_max = la > lb ? la : lb;
    int *opt[2];
    for (int i = 0; i < 2; i++)
        opt[i] = new int[l_min]();
//    int opt[la][lb] = {};
    string min_p, max_p;
    if (l_min == la) {
        min_p = A;
        max_p = B;
    } else {
        min_p = B;
        max_p = A;
    }
    for (int i = 1; i < l_max; i++)
        for (int j = 1; j < l_min; j++) {
            if (max_p[i - 1] == min_p[j - 1])
                opt[i % 2][j] = opt[(i - 1) % 2][j - 1] + 1;
            else
                opt[i % 2][j] = max(opt[(i - 1) % 2][j], opt[i % 2][j - 1]);
        }
    return opt[(l_max - 1) % 2][lb - 1];
}

int longestCommonSubsequence1(string A, string B) {
    /*
     * 仅输出lcs最优值
     */
    unsigned long la = A.length();
    unsigned long lb = B.length();
    unsigned long l_min = la <= lb ? la : lb;
    unsigned long l_max = la > lb ? la : lb;
    int *opt = new int[l_min + 1]();
    string min_p, max_p;
    if (l_min == la) {
        min_p = A;
        max_p = B;
    } else {
        min_p = B;
        max_p = A;
    }

    int old, tmp;
    for (int i = 1; i <= l_max; i++) {
        old = 0;
        for (int j = 1; j <= l_min; j++) {
            tmp = opt[j];
            if (max_p[i - 1] == min_p[j - 1])
                opt[j] = old + 1;
            else
                opt[j] = max(opt[j], opt[j - 1]);
            old = tmp;
        }
    }
    return opt[l_min];
}

int longestCommonSubsequence(string A, string B) {
    /*
     * 输出lcs最优值和最优解
     */
    unsigned long la = A.length() + 1;
    unsigned long lb = B.length() + 1;
    int **opt = new int *[la];
    for (int i = 0; i < la; i++)
        opt[i] = new int[lb]();
//    int opt[la][lb] = {};
    for (int i = 1; i < la; i++)
        for (int j = 1; j < lb; j++) {
            if (A[i - 1] == B[j - 1])
                opt[i][j] = opt[i - 1][j - 1] + 1;
            else
                opt[i][j] = max(opt[i - 1][j], opt[i][j - 1]);
        }
    printLCS(A, B, (int) A.length(), (int) B.length(), opt);
    cout << endl;
    return opt[la - 1][lb - 1];
}

void printLCS(string A, string B, int i, int j, int **opt) {
    /*
     * 输出lcs最优解
     */
    if (i <= 0 || j <= 0)
        return;

    if (A[i - 1] == B[j - 1]) {
        printLCS(A, B, i - 1, j - 1, opt);
        cout << A[i - 1];
    } else if (opt[i - 1][j] >= opt[i][j - 1])
        printLCS(A, B, i - 1, j, opt);
    else
        printLCS(A, B, i, j - 1, opt);
}


//int main() {
int main_lcs() {
//    string A = "ABCBDAB", B = "BDCABA";
//    string A = "B", B = "A";
//    cout << longestCommonSubsequence0(A, B) << endl;
//    cout << longestCommonSubsequence1(A, B) << endl;
//    cout << longestCommonSubsequence(A, B) << endl;


//    string A = "plasma", B = "altruism";
    string A = "PLASMA", B = "ALTRUISM";
    cout << longestCommonSubsequence1(A, B) << endl;
    cout << "Edit Dist: " << A.length() + B.length() - 2 * longestCommonSubsequence1(A, B) << endl;
    return 0;
}
