//
// Created by pipi on 3/26/17.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
const int LEN = 50;    //定义要排序的数组的大小
#define ITEMTYPE int


void cpp_in() {
    /* c++输入 */
    string filename("OJ/OJ/Ali/in.txt");
    fstream file(filename, ios::in);

    if (!file) {
        cerr << "file open error: " << filename << endl;
        exit(0);
    }
    int x, y;
    while (!file.eof() && file.peek() != EOF) {
        file >> x >> y; //如果没有读到数字时（空行），xy值不变，但是却不报错！
        cout << x << ' ' << y << endl;
        file.get(); // 读取最后的回车符
    }

//    vector<ITEMTYPE> A;
//    ITEMTYPE data;
//    while ((data = cin.get()) != '\n') {//input any format data,end with ctl+z and return false 2 cin
//        cin.unget();
//        cin >> data;
//        A.push_back(data);
//        cout << data << endl;
//    }
//    fflush(stdin);    //清除stdin中的非法数据
//    cin.clear();    //set the state of stream as good
//    cout << "end";
}

void in() {
    /* c输入 */
    char filename[] = "OJ/OJ/Ali/in.txt";
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        printf("file open error: %s", filename);
        exit(0);
    }
    int x, y;
    while (fscanf(fp, "%d %d", &x, &y) == 2) {
        printf("%d %d\n", x, y);
    }
//    while (!feof(fp)) {
//        fscanf(fp, "%d %d", &x, &y);
//        printf("%d %d\n", x, y);
//    }
}

int main() {
    in();
    return 0;
}