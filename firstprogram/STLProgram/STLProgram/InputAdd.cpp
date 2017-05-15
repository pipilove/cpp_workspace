/**********************************************************************************
> File Name: InputAdd.cpp
> Description:排序deque后，弹出前5个数据，再采用for_each对剩余数据进行累加并输出
> System & Compiler: windows7旗舰版 & Visual_Studio2010_Professional
> Author: 皮挺
> Mail: xingshang1992@163.com
> Created Time: 11/28/2012 Wed. 23:00
************************************************************************************/
/*#include <iostream>
#include <algorithm>
#include <deque>
#include <functional>
using namespace std;

void print(int a){			//打印每个int字符
	cout<<a<<" ";
}
class Add{				//将所有int字符相加保存到theValue，并通过return返回给for_each
private:
	int theValue;    
public:
	Add(){
		theValue=0 ;
	}
	void operator() (int& elem){
		theValue += elem;
	}
	operator int() {
		return theValue;
	}
};


int main(){
	int a[]={11,12,13,2,3,4,5,6,7,16,17,18};
	deque<int> deq_int;
	for(int i=0;i<12;i++)				//将数组中的数值压入deque_int中
		deq_int.push_back(a[i]);
	sort(deq_int.begin(),deq_int.end(),less<int>( ) );			//对deque_int中的数据进行排序
	cout<<"After sorting,the datas in the deque are ："<<endl;
	for_each(deq_int.begin(),deq_int.end(),print);				//采用for_each对deque中的数据打印出来
	for(int i=0;i<5;i++)						//采用pop_front弹出deque_int中前5个数据
		deq_int.pop_front();
	cout<<endl;
	cout<<"After pop_front the first five datas,the sum of the remained datas is :"<<endl;
	cout<<for_each(deq_int.begin(),deq_int.end(),Add())<<endl;					//采用for_each对剩余数据进行累加并输出
	system("pause");
	return 0;
}*/