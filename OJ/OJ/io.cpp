//
// Created by pipi on 3/26/17.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
const int LEN = 50;    //定义要排序的数组的大小
#define ITEMTYPE int

void cpp_in() {
    istringstream oss("12 34\n"
                              "56 78");
    std::cin.rdbuf(oss.rdbuf());
}

void cpp_filein() {
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
}


void c_in() {
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
    char o;
    int num;
    scanf("\n%c%d", &o, &num);
}
