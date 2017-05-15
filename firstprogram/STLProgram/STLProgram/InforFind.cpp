/************************************************************************************
> File Name: InforFind.cpp
> Description:用map容器装载学生信息，统计学生个数并输出，输入姓名或学号对容器进行查询
> System & Compiler: windows7旗舰版 & Visual_Studio2010_Professional
> Author: 皮挺
> Mail: xingshang1992@163.com
> Created Time: 11/29/2012 Thu. 15:00
**************************************************************************************/
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

void countor(const pair<string, string> &stu){				//统计2011,2012,2010级学生个数并输出
	static int count[3];
	if(stu.second.substr(0,4)=="2010")
		++count[0];
	if(stu.second.substr(0,4)=="2011")
		++count[1];
	if(stu.second.substr(0,4)=="2012")
		++count[2];
	if(stu.first=="zhangsan"){
		cout<<"The number of 2010 students is : "<<count[0]<<endl;
		cout<<"The number of 2011 students is : "<<count[1]<<endl;
		cout<<"The number of 2012 students is : "<<count[2]<<endl;
	}
}


int main(){
	map<string,string> map_stu;
	map_stu.insert(make_pair("zhangsan","2011123"));			//将姓名作为key，学号作为value,采用map容器进行装载
	map_stu.insert(make_pair("wanger","2011235"));
	map_stu.insert(make_pair("liuqi","2012009"));
	map_stu.insert(make_pair("tangliu","2012676"));
	map_stu.insert(make_pair("tangba","2010527"));

	for_each(map_stu.begin(),map_stu.end(),countor);			//采用for_each统计2011,2012,2010级学生个数并输出
	while(1){													//输入姓名或学号后对容器进行信息查询
		cout<<"Please input the name or the studentID to find it : (-1 to exit!)"<<endl;
		string find;
		cin>>find;
		if(find=="-1") break;					//输入-1退出循环
		map<string,string>::iterator pos;
		for (pos = map_stu.begin(); pos != map_stu.end(); pos++)
			if (pos->first == find||pos->second == find) {
				cout << pos->first <<":"<< pos->second << endl;			//找到姓名或者学号后将其对应的姓名和学号输出
				break;
			}
			if(pos==map_stu.end())
				cout<<"The name or the studentID is not found!"<<endl;
	}
	system("pause");
	return 0;
}
