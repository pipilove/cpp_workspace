///*	贪心算法 - 活动选择问题(multimap实现)	2013.12.26	皮皮		*/
#include "ActivitySelector.h"
using namespace std;
vector<int> activitySelector(multimap<int,int> actMultimap){//F是升序的
	vector<int> A;						//在堆上分配内存？
	A.push_back(0);						//下标从0开始
	multimap<int,int>::iterator actIt,curActIt;
	curActIt = actMultimap.begin();
	int i = 0;
	for(actIt = actMultimap.begin();actIt != actMultimap.end();i++,actIt++)
		if(actIt->second > curActIt->first){//if is actMap,则actMap[m]即代表key = m时的值;multimap不能使用[]
			A.push_back(i);
			curActIt = actIt;
		}
	return A;							//返回选择的活动下标（从0开始）
}
