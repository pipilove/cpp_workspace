/**********************************************************************************
	> File Name: CharCount.cpp
    > Description:����for_each����Ʒº���ͳ��list��6���ַ����ַ����ֵĸ�������ͳ��
    > System & Compiler: windows7�콢�� & Visual_Studio2010_Professional
    > Author: Ƥͦ
    > Mail: xingshang1992@163.com
    > Created Time: 11/28/2012 Wed. 22:00
************************************************************************************/
/*#include <iostream>
#include <algorithm>
#include <list>
#include <string>
using namespace std;

void print(string);
int count1(string);

int main(){
	string str[]={"asayjk","bhjresaf","cebnmr","dttzlo","cqwsw","actrfs"};
	list<string> list_str(str,str+6);			//������6���ַ���װ��list������
	cout<<"In the list,there are six strings :"<<endl;
	for_each(list_str.begin(),list_str.end(),print);			//����for_each��list��ÿ���ַ������д�ӡ���
	cout<<endl;
	cout<<"In the list,the number of each letter in its string is :"<<endl;
	for_each(list_str.begin(),list_str.end(),count1);				//����for_each��list��ÿ���ַ������ַ����ֵĸ�������ͳ��
	system("pause");
	return 0;
}

void print(string str){
	cout<<str<<" ";
}
int count1(string str){				//ͳ��ÿ���ַ�����ÿ���ַ�����Ŀ�����
	int countor[26]={0};
	char ch;
	for(int i=0;i<str.length();i++)
		countor[(str[i]-97)]++;
	for(int i=0;i<26;i++){
		ch=i+97;
		if(countor[i]!=0)
			cout<<ch<<":"<<countor[i]<<" ";
	}
	cout<<endl;
	return 1;
}*/

