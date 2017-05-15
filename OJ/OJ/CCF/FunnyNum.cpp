//*******************************************************************/
//*		CCF软件能力认证考试模拟题 —— 有趣的数	皮皮 2014-9-20		*/
//*******************************************************************/
#include <assert.h>
#include <stdio.h>
#include <set>
using namespace std;

static int digit;
static int count = 0;
static multiset<int> set_num;
/*	回溯法	TLE	20分???????????????????????????	*/
static void funnyNum(int deepth){								//deepth从0开始
	if(deepth >= digit){										//已找到一条路径（解）
		//0, 1, 2, 3四个数字都出现过至少一次
		if( set_num.find(0) != set_num.end() && set_num.find(1) != set_num.end() && set_num.find(2) != set_num.end() &&set_num.find(3) != set_num.end()){
			count++;
			count %= 1000000007;
		}
	}else{
		if(deepth == 0){
			//for(int i = 1; i <= 3; i++){
			set_num.insert(2);									//只能以2开头，否则总是不满足四个数字都出现过至少一次
			funnyNum(deepth + 1);
			//set_num.erase(set_num.find(i));					//回溯时erase掉
			//}
		}else{
			for(int i = 0; i <= 3; i++){						//第deepth+1位上的数字
				if(i == 0 && set_num.find(1) == set_num.end()){	//前面位置上有1则当前位置上不能是0，所有的0都出现在所有的1之前，而所有的2都出现在所有的3之前
					set_num.insert(0);
					funnyNum(deepth + 1);
					set_num.erase(set_num.find(0));
				}else if(i == 2 && set_num.find(3) == set_num.end()){
					set_num.insert(2);
					funnyNum(deepth + 1);
					set_num.erase(set_num.find(2));
				}else if( i== 1 || i == 3){
					set_num.insert(i);
					funnyNum(deepth + 1);
					set_num.erase(set_num.find(i));
				}
			}
		}
	}
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <list>
static long long f[2000][3][2]; // f[seq_k to place][0: to place 0 , 1: ethier 0 or 1, 2 : must be 1][3 is placed ? 1 : 0]
/*	ccf标准算法	看不懂	*/
static int dp(int n, int p1, int p3) {
    long long &now = f[n][p1][p3];
    if (now != -1)
        return now;
    if (n == 0) {
        if (p1 == 2 && p3 == 1) {
            now = 1;
        } else {
            now = 0;
        }
        return now;
    }
    now = 0;
    if (p1 == 0) {
        now += dp(n-1, 1, p3); // go 0
    } else if (p1 == 1) {
        now += dp(n-1, 1, p3); // go 0
        now += dp(n-1, 2, p3); // go 1
    } else { // p1 == 2
        now += dp(n-1, 2, p3); // go 1
    }
    if (p3 == 0) {
        now += dp(n-1, p1, p3); // go 2;
        now += dp(n-1, p1, 1); // go 3;
    } else {
        now += dp(n-1, p1, 1); // go 3;
    }
    now %= 1000000007;
}


int __654116main(){
	assert( freopen("ccf\\FunnyNum.in", "r", stdin) );

	scanf("%d", &digit);				//位数

	/*funnyNum(0);
	printf("%d\n", count);*/

    memset(f, -1, sizeof(f));
	printf("%d\n", dp(digit - 1, 0, 0));// seq[n] is 2

	//fclose(stdin);
	return 0;
}
