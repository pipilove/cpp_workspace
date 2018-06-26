/****************************************************************************/
/*	 CCF软件能力认证考试模拟题 —— 出现次数最多的数	皮皮 2014-8-30			*/
/****************************************************************************/
#include <assert.h>
#include <iostream>
#include <map>
using namespace std;

int __516541616main(){
	//assert( freopen("CCF\\mostOftenNum.in", "r", stdin) );
	int n, num;
	typedef map<int, int> intIntMap;
	intIntMap numCount;

	cin>>n;
	for(int i = 0; i < n; i++){
		cin>>num;
		numCount[num]++;
	}

	int max_num = INT_MIN, max = -1;
	for(intIntMap::iterator pos = numCount.begin(); pos != numCount.end(); pos++){
		//cout<<pos->first << " : " << pos->second << endl;
		if( pos->second > max || (pos->second == max && pos->first < max_num)){
			max = pos->second;
			max_num = pos->first;
		}
	}
	cout<< max_num << endl;

	//fclose(stdin);
	return 0;
}
