/*
__title__ = '400.Nth Digit'
Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, …
Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 2^31).
输入描述:
Only one integer: n
输出描述:
The nth digit
输入例子:
3
输出例子:
3
__author__ = 'pipi'
__mtime__ = '6/3/17'
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
#include <math.h>

using namespace std;

int findNthDigit(int n) {
    unsigned int period_start = 1;
    int digits_num = 1;
    //9 * period_start * digits_num可能超出边界
    while (n > 9 * period_start * digits_num) {
        n -= 9 * period_start * digits_num;
        digits_num++;
        period_start *= 10;
    }
    int digit = n % digits_num;
    int less = period_start + n / digits_num - 1;
    int r;
    if (digit)
        r = (less + 1) / int(pow(10, digits_num - digit)) % 10;
    else
        r = less % 10;
    return r;
}

//int main() {
int main_nthdigit() {
    int n;
//    cin >> n;
    int k = 13;
    int ns[k] = {1000000000, 1, 6, 9, 10, 15, 189, 190, 194, 198, 2883, 2886, 2889};
    for (int i = 0; i < k; i++) {
        n = ns[i];
        cout << findNthDigit(n) << endl;
    }
}


