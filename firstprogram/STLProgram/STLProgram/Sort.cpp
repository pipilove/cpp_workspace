/*************************************************************************
	> File Name: sort.cpp
    > Description:采用某一种STL排序算法，对这6个字符串进行排序后输出
    > System & Compiler: windows7旗舰版 & Visual_Studio2010_Professional
    > Author: 皮挺
    > Mail: xingshang1992@163.com
    > Created Time: 11/25/2012 Fri. 0:03
**************************************************************************/
/*#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

void print(string str){		//设置函数对象，打印string类型元素
	cout<<str<<" ";
}

int main(){
	string str[]={"asayjk","bhjresaf","cebnmr","dttzlo","cqwsw","actrfs"};
	vector<string> vec_str(str,str+6);			//初始化vector容器
	sort(vec_str.begin(),vec_str.end(),less<string>( ) );		//对vec_str升序排序
	cout<<"After sorting,the six strings :"<<endl;
	for_each(vec_str.begin(),vec_str.end(),print);		//打印排序后的vec_str
	cout<<endl;
	system("pause");
	return 0;
}*/