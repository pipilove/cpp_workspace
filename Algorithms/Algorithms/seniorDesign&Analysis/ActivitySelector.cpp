///*	̰���㷨 - �ѡ������(multimapʵ��)	2013.12.26	ƤƤ		*/
#include "ActivitySelector.h"
using namespace std;
vector<int> activitySelector(multimap<int,int> actMultimap){//F�������
	vector<int> A;						//�ڶ��Ϸ����ڴ棿
	A.push_back(0);						//�±��0��ʼ
	multimap<int,int>::iterator actIt,curActIt;
	curActIt = actMultimap.begin();
	int i = 0;
	for(actIt = actMultimap.begin();actIt != actMultimap.end();i++,actIt++)
		if(actIt->second > curActIt->first){//if is actMap,��actMap[m]������key = mʱ��ֵ;multimap����ʹ��[]
			A.push_back(i);
			curActIt = actIt;
		}
	return A;							//����ѡ��Ļ�±꣨��0��ʼ��
}
