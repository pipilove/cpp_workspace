/**	c++��sort����	��ʽ��
*	template<class RanIt>    void sort(RanIt first, RanIt last);
*	template<class RanIt, class Pred>    void sort(RanIt first, RanIt last, Pred pr);
*/

/*
#include <algorithm>
#include <iostream>
using namespace std;

int cmp(const int a,const int b){
	if(a>b)	//��Ϊ<���Զ���Ϊ����
		return 1;
	else
		return 0;
}

int main(){
	int i;
	int a[]={48,10,13,5,10,51,33,43,10,4,14,1,41,41};
	int len=sizeof(a)/sizeof(a[0]);

	for(i=0;i<len;i++)
	cout<<a[i]<<", ";
	cout<<endl;

	sort(a,a+len);//Ĭ��Ϊ����
	for(i=0;i<len;i++)
	cout<<a[i]<<", ";
	cout<<endl;

	sort(a,a+len,cmp);//�Զ���Ϊ����
	for(i=0;i<len;i++)
	cout<<a[i]<<", ";
	cout<<endl;

	system("pause");
	return 0;
}
*/