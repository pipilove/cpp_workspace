/**********************************************************************************
> File Name: InputAdd.cpp
> Description:����deque�󣬵���ǰ5�����ݣ��ٲ���for_each��ʣ�����ݽ����ۼӲ����
> System & Compiler: windows7�콢�� & Visual_Studio2010_Professional
> Author: Ƥͦ
> Mail: xingshang1992@163.com
> Created Time: 11/28/2012 Wed. 23:00
************************************************************************************/
/*#include <iostream>
#include <algorithm>
#include <deque>
#include <functional>
using namespace std;

void print(int a){			//��ӡÿ��int�ַ�
	cout<<a<<" ";
}
class Add{				//������int�ַ���ӱ��浽theValue����ͨ��return���ظ�for_each
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
	for(int i=0;i<12;i++)				//�������е���ֵѹ��deque_int��
		deq_int.push_back(a[i]);
	sort(deq_int.begin(),deq_int.end(),less<int>( ) );			//��deque_int�е����ݽ�������
	cout<<"After sorting,the datas in the deque are ��"<<endl;
	for_each(deq_int.begin(),deq_int.end(),print);				//����for_each��deque�е����ݴ�ӡ����
	for(int i=0;i<5;i++)						//����pop_front����deque_int��ǰ5������
		deq_int.pop_front();
	cout<<endl;
	cout<<"After pop_front the first five datas,the sum of the remained datas is :"<<endl;
	cout<<for_each(deq_int.begin(),deq_int.end(),Add())<<endl;					//����for_each��ʣ�����ݽ����ۼӲ����
	system("pause");
	return 0;
}*/