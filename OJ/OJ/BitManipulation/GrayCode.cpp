/*
__title__ = ''
__author__ = 'pipi'
__mtime__ = '5/16/17'
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
#include <vector>
#include <sstream>

using namespace std;

vector<string> gray0(int n) {
    /*
     * 格雷码字符串的直接排列递归实现
     * 思路:1、获得n-1位生成格雷码的数组
     *      2、由于n位生成的格雷码位数是n-1的两倍，故只要在n为格雷码的前半部分加0，后半部分加1即可。
     */
    if (n == 0)
        return vector<string>{"0"};
    else if (n == 1) {
        return vector<string>({"0", "1"});
    } else {
        vector<string> new_gray_code;
        vector<string> gray_code = gray0(n - 1);
//        vector<string> gray_code = vector<string>({"0", "1"});

        vector<string>::iterator gc_it;
        for (gc_it = gray_code.begin(); gc_it != gray_code.end(); gc_it++)
            new_gray_code.push_back("0" + *gc_it);

        vector<string>::reverse_iterator gc_rit;
        for (gc_rit = gray_code.rbegin(); gc_rit != gray_code.rend(); gc_rit++)
            new_gray_code.push_back("1" + *gc_rit);
        return new_gray_code;
    }
}


vector<string> gray1(int n) {
    /*
     * 格雷码字符串的镜射排列非递归实现
     */
    if (n == 0)
        return vector<string>{"0"};

    vector<string> gray_code = vector<string>({"0", "1"});
    while (--n) {
        vector<string> new_gray_code;

        vector<string>::iterator gc_it;
        for (gc_it = gray_code.begin(); gc_it != gray_code.end(); gc_it++)
            new_gray_code.push_back("0" + *gc_it);

        vector<string>::reverse_iterator gc_rit;
        for (gc_rit = gray_code.rbegin(); gc_rit != gray_code.rend(); gc_rit++)
            new_gray_code.push_back("1" + *gc_rit);

        gray_code = new_gray_code;
    }
    return gray_code;
}

vector<int> gray2(int n) {
    /*
     * 格雷码二进制整数的镜射排列实现
     */
    vector<int> gray_code = vector<int>{0};
    gray_code.reserve((unsigned long) (1 << n));

    int high_bit_pos = 1;
    vector<int>::reverse_iterator gray_it;
    for (int i = 0; i < n; i++) {
        //逆序最高位置1
        for (gray_it = gray_code.rbegin(); gray_it != gray_code.rend(); gray_it++)
            gray_code.push_back(high_bit_pos | *gray_it);
        high_bit_pos <<= 1;
    }
    return gray_code;
}

vector<int> gray3(int n) {
    /*
     * 通过二进制数转换成格雷码二进制数
     */
    vector<int> gray_code = vector<int>{};
    gray_code.reserve((unsigned long) (1 << n));

    int size = 1 << n;
    for (int i = 0; i < size; i++)
        gray_code.push_back((i >> 1) ^ i);
    return gray_code;
}

void test_bray_str(int n, int func = 1) {
    vector<string> (*gray)(int) = NULL;
    if (func == 0) {
        gray = gray0;
        cout << "testing gray 0" << endl;
    } else if (func == 1) {
        gray = gray1;
        cout << "testing gray 1" << endl;
    }

    vector<string> gray_code = gray(n);
    vector<string>::iterator gc_it;
    for (gc_it = gray_code.begin(); gc_it != gray_code.end(); gc_it++)
        cout << *gc_it << endl;
}

void test_bray_int(int n, int func = 3) {
    vector<int> (*gray)(int) = NULL;
    if (func == 2) {
        gray = gray2;
        cout << "testing gray 2" << endl;
    } else if (func == 3) {
        gray = gray3;
        cout << "testing gray 3" << endl;
    }

    vector<int> gray_code = gray(n);
    vector<int>::iterator gc_it;
    for (gc_it = gray_code.begin(); gc_it != gray_code.end(); gc_it++)
        cout << *gc_it << endl;
}

//int main() {
int main_graycode() {
    istringstream oss("3");
    std::cin.rdbuf(oss.rdbuf());

    int n;
    cin >> n;

    test_bray_str(n, 1);
    test_bray_int(n, 2);

    return 0;
}
