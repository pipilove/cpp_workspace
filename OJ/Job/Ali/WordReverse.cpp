/*
__title__ = 'Word Reverse'
程序读取文本，内容是英文文章，对每个单词作倒序处理。文件由用户指定。
注意：1.数字不作倒序    2.标点位置不变
例：
The    quick    brown    fox    jumps    over    the    lazy    dog.
I    have    100    bucks!
转换为：
ehT    kciuq    nworb    xof    spmuj    revo    eht    yzal    god.
I    evah    100    skcub!
__author__ = 'Cao Lingwei'
__mtime__ = '5/3/17'*/
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
#include <string.h>
#include<fstream>

using namespace std;

void reversestring(char word[]) {
    string str(&word[0], &word[strlen(word)]);
    string s(str.rbegin(), str.rend());
    cout << s;
}

void Reverse(string filename) {
    char a, Tword[30];
    ifstream infile(filename);
    infile >> noskipws;
    if (!infile) {
        cout << "cannot open!" << endl;
        return;
    }
    while (infile) {
        int i = 0;
        infile.get(a);
        Tword[0] = ' ';//±ê¼ÇÎ»ÓÃÓÚÅÐ¶ÏÊÇ·ñÎªÒ»¸öµ¥´Ê
        bool is_word = false;
        //	if (a == 0)  cout << " ";
        if (a == '\n') cout << "\n";
        while ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || Tword[0] == ' ') {
            if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z') {
                Tword[i] = a;
                i++;
                is_word = true;
            } else cout << a;
            infile.get(a);
            if (infile.eof()) break;
        }
        Tword[i] = '\0';
        reversestring(Tword);
        cout << a;
    }
    infile.close();
}


//int main() {
int main_wordreserve() {
    string filename;
    cin >> filename;
    Reverse(filename);
}
