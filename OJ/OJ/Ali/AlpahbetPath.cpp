/*
__title__ = '字母矩阵中寻找以A开头的连续字母最长路径'
 给定一个文本文件，内容为是一个字母矩阵。寻找一条以A开头的连续字母最长路径（允许横向、纵向、对角方向），输出长度。
例：
ABE
CFG
BDH
ABC

输出：4
说明：
最长路径为：
AB.
C..
.D.
...

例：
DCCBZ
DCXBA
输出：3
说明：
最长路径为：
..C..
...BA
__author__ = 'pipi'
__mtime__ = '5/4/17'
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
//#include "stdafx.h"
#include<iostream>
#include<fstream>

using namespace std;


//M*NµÄ¶þÎ»×ÖÄ¸¾ØÕó
int letter_len = 0;   //Á¬Ðø×Ö·ûÊý
int maxlen = 0;       //×î´óÁ¬Ðø×Ö·ûÊý
char Letter[999][999];//¶þÎ¬×Ö·ûÊý×é£¬ÓÉÓÚÎÄ¼þÖÐÃ»ÓÐÌáÇ°¸ø¶¨¾ØÕóµÄ¿íºÍ¸ß£¬ËùÒÔÉêÇëÏÈÉêÇëÒ»¸ö¹Ì¶¨µÄ½Ï´óµÄÊý×é
int M = 0, N = 0;   //¶þÎ»×Ö·ûÊý×éµÄ³¤£¬¿í
int x, y;          //×ÖÄ¸AµÄÎ»ÖÃ

void ReadFile() {
    char a;
    ifstream infile("/home/pipi/files/mine/cpp_workspace/OJ/OJ/Ali/Letter.txt");
    infile >> noskipws;
    if (!infile) {
        cout << "cannot open!" << endl;
        return;
    }
    int i = 1, j = 1;
    while (infile) {
        j = 1;
        //Letter[i][j] = '*';
        infile.get(a);
        while (a != '\n') {
            Letter[i][j] = a;
            j++;
            infile.get(a);
            if (infile.eof()) break;
        }
        if (infile.eof()) break;
        N = j;
        i++;
        M++;

    }
    M = M + 2;
    N++;
    //cout << M << "  " << N << endl;
    for (i = 0; i++; i < N) {
        Letter[0][i] = '*';
        Letter[M][i] = '*';
    }

    for (i = 0; i++; i < M) {
        Letter[i][0] = '*';
        Letter[i][N] = '*';
    }

    infile.close();
}

int LongestPath(int x, int y) {
    letter_len++;
    if ((x - 1) >= 0 && Letter[x - 1][y] - Letter[x][y] == 1)//ÉÏ(x-1,y)£»´æÔÚÇÒÊÇµ±Ç°×ÖÄ¸µÄÏÂÒ»¸ö
    {
        LongestPath(x - 1, y);
    }

    if ((x + 1) < N && Letter[x + 1][y] - Letter[x][y] == 1)//ÏÂ(x+1,y)£»´æÔÚÇÒÊÇµ±Ç°×ÖÄ¸µÄÏÂÒ»¸ö
    {
        LongestPath(x + 1, y);
    }

    if ((y - 1) >= 0 && Letter[x][y - 1] - Letter[x][y] == 1)//×ó(x,y-1)£»´æÔÚÇÒÊÇµ±Ç°×ÖÄ¸µÄÏÂÒ»¸ö
    {
        LongestPath(x, y - 1);
    }

    if ((y + 1) < M && Letter[x][y + 1] - Letter[x][y] == 1)//ÓÒ(x,y+1)£»´æÔÚÇÒÊÇµ±Ç°×ÖÄ¸µÄÏÂÒ»¸ö
    {
        LongestPath(x, y + 1);
    }

    if ((y + 1) < M && (x + 1) < N && Letter[x + 1][y + 1] - Letter[x][y] == 1)//ÓÒÏÂ(x,y+1)£»´æÔÚÇÒÊÇµ±Ç°×ÖÄ¸µÄÏÂÒ»¸ö
    {
        LongestPath(x + 1, y + 1);
    }
    if ((y - 1) > 0 && (x - 1) > 0 && Letter[x - 1][y - 1] - Letter[x][y] == 1)//×óÉÏ(x,y+1)£»´æÔÚÇÒÊÇµ±Ç°×ÖÄ¸µÄÏÂÒ»¸ö
    {
        LongestPath(x - 1, y - 1);
    }
    if ((x + 1) < N && (y - 1) > 0 && Letter[x + 1][y - 1] - Letter[x][y] == 1)//ÓÒÉÏ(x,y+1)£»´æÔÚÇÒÊÇµ±Ç°×ÖÄ¸µÄÏÂÒ»¸ö
    {
        LongestPath(x + 1, y - 1);
    }
    if ((y + 1) < M && (x - 1) > 0 && Letter[x - 1][y + 1] - Letter[x][y] == 1)//×óÏÂ(x,y+1)£»´æÔÚÇÒÊÇµ±Ç°×ÖÄ¸µÄÏÂÒ»¸ö
    {
        LongestPath(x - 1, y + 1);

    }

    if (maxlen < letter_len) {
        maxlen = letter_len;

    }
    letter_len--;
    return maxlen;
}


void Find_A_Position() {

}

//int main() {
int main_alphapath() {
    ReadFile();
    int i, j;
    int result = 0;
    for (i = 1; i < M; i++) {
        for (j = 1; j < N; j++) {
            if (Letter[i][j] == 'A') {
                letter_len = 0;
                maxlen = 0;
                result = max(result, LongestPath(i, j));

            }

        }
    }

    cout << result << endl;
}

