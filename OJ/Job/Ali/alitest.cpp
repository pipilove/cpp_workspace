//
// Created by pipi on 3/26/17.
// 卜踆哉数对
//
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int mod(int a, int b, int m) {
    int result = 1;
    int base = a;
    while (b > 0) {
        if ((b & 1) == 1) {
            result = (result * base) % m;
        }
        base = (base * base) % m;
        b >>= 1;
    }
    return result;
}

int PowerMod(int a, int b, int c) {
    int ans = 1;
    a = a % c;
    while (b > 0) {
        if (b % 2 == 1)
            ans = (ans * a) % c;
        b = b / 2;
        a = (a * a) % c;
    }
    return ans;
}

int bcz(int b, int c, int d) {
//    if (mod(int(((b - 1) + sqrt(b * b - 1))), c, d))
    int result = (int) floor(pow((b - 1) + sqrt(b * b - 1), c)) % d;
    int result1 = (int) mod(int(((b - 1) + sqrt(b * b - 1))), c, d);
    int result2 = (int) PowerMod(int(((b - 1) + sqrt(b * b - 1))), c, d);
    cout << "result: " << result << endl;
    cout << "result1: " << result1 << endl;
    cout << "result2: " << result1 << endl;
    return result;
}

int main() {

    char filename[] = "OJ/OJ/Ali/in.txt";
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        printf("file open error: %s", filename);
        exit(0);
    }

    int b, c, d;
    while (fscanf(fp, "%d %d %d", &b, &c, &d) == 3) {
        printf("%d %d %d\n", b, c, d);

        int res;
//        int b, c, d;
//        cin >> b >> c >> d;

        time_t s_time, e_time;
        time(&s_time);
        res = bcz(b, c, d);
        time(&e_time);
        cout << "time:" << e_time - s_time << endl;
//        cout << res << endl;
        cout << endl;
        exit(0);
    }

    return 0;
}
