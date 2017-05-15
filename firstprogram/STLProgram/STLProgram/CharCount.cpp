/**********************************************************************************
	> File Name: CharCount.cpp
    > Description:采用for_each并设计仿函数统计list中6个字符串字符出现的个数进行统计
    > System & Compiler: windows7旗舰版 & Visual_Studio2010_Professional
    > Author: 皮挺
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
	list<string> list_str(str,str+6);			//将以上6个字符串装入list容器中
	cout<<"In the list,there are six strings :"<<endl;
	for_each(list_str.begin(),list_str.end(),print);			//采用for_each对list中每个字符串进行打印输出
	cout<<endl;
	cout<<"In the list,the number of each letter in its string is :"<<endl;
	for_each(list_str.begin(),list_str.end(),count1);				//采用for_each对list中每个字符串中字符出现的个数进行统计
	system("pause");
	return 0;
}

void print(string str){
	cout<<str<<" ";
}
int count1(string str){				//统计每个字符串中每个字符的数目并输出
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

