/************************************************************************************
> File Name: InforFind.cpp
> Description:��map����װ��ѧ����Ϣ��ͳ��ѧ�����������������������ѧ�Ŷ��������в�ѯ
> System & Compiler: windows7�콢�� & Visual_Studio2010_Professional
> Author: Ƥͦ
> Mail: xingshang1992@163.com
> Created Time: 11/29/2012 Thu. 15:00
**************************************************************************************/
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

void countor(const pair<string, string> &stu){				//ͳ��2011,2012,2010��ѧ�����������
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
	map_stu.insert(make_pair("zhangsan","2011123"));			//��������Ϊkey��ѧ����Ϊvalue,����map��������װ��
	map_stu.insert(make_pair("wanger","2011235"));
	map_stu.insert(make_pair("liuqi","2012009"));
	map_stu.insert(make_pair("tangliu","2012676"));
	map_stu.insert(make_pair("tangba","2010527"));

	for_each(map_stu.begin(),map_stu.end(),countor);			//����for_eachͳ��2011,2012,2010��ѧ�����������
	while(1){													//����������ѧ�ź������������Ϣ��ѯ
		cout<<"Please input the name or the studentID to find it : (-1 to exit!)"<<endl;
		string find;
		cin>>find;
		if(find=="-1") break;					//����-1�˳�ѭ��
		map<string,string>::iterator pos;
		for (pos = map_stu.begin(); pos != map_stu.end(); pos++)
			if (pos->first == find||pos->second == find) {
				cout << pos->first <<":"<< pos->second << endl;			//�ҵ���������ѧ�ź����Ӧ��������ѧ�����
				break;
			}
			if(pos==map_stu.end())
				cout<<"The name or the studentID is not found!"<<endl;
	}
	system("pause");
	return 0;
}
