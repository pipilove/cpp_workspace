#include <bitset>
#include <iostream>
//#include "Signal.h"

#define input Signal;
#define output Signal;
#define wire Signal;

using namespace std;

int main() {

    bitset<14> bs1("01110010100110");
    bitset<5> bs2;
    bitset<5> bs3(bs1.to_string(), 4, 5);
    bs2 = bs3;
    //bs2 = 0x1011;
    cout << bs1.to_ulong() << endl;
    cout << bs2 << endl;//.to_ulong()<<endl;

    //Signal<16> sig1;
    //sig1 = 0x2546;
    //Signal<5> sig2;
    //sig2 = sig1.sub(0,4);
    //cout<<sig1.value<<endl;
    //cout<<sig2.value<<endl;
//	system("pause");
    return 0;
}


