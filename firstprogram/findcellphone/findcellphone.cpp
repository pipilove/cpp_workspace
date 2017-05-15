// findcellphone.cpp : Defines the entry point for the console application.
//类设计电话本程序

#include "stdafx.h"
#include "iostream"
#include "string"

using namespace std;

class CellPhone{
private:
	
	string name[20];						//如果linkman人数超过20？
	string number[20];
	static int count;						//存储的联系人个数的计数器static 
public:
	void addLinkman(string,string);
	void findNum(string);
	void DispPhones();
};
int CellPhone::count=0;
void CellPhone::addLinkman(string addName,string addNum){			//增加linkman,注意count
	name[count]=addName;
	number[count++]=addNum;
}
void CellPhone::findNum(string subStr){								//根据substr模糊查找linkman
	bool iffind=false;
	for(int j=0;j<count;j++){
		bool flag=true;
		for(int i=0;i<subStr.length();i++){								//subStr.length()读尽substr的字符
			if (subStr[i]!=name[j][i]&&subStr[i]!=number[j][i])			//比较substr第i个字符和number[j]或name[j]的第i个字符
				flag=false;
		}
		if(flag){
			cout<<name[j]<<" "<<number[j]<<endl;
			iffind=true;
		}
	}
	if(!iffind)
		cout<<"Sorry,the linkman is not found!"<<endl;
}
void CellPhone::DispPhones(){											//显示所有联系人
	for(int i=0;i<count;i++)
		cout<<name[i]<<" "<<number[i]<<endl;
}


int main()
{
	int n;
	string addName,addNum,subStr;
	
	cout<<"The number of your linkmans and their phone numbers: ";			//联系人个数
	cin>>n;
	if(n>20){
		cout<<"The number of the linkman is overdo!"<<endl;
		return 0;
	}
	CellPhone book1;														//创建联系人
	for(int i=1;i<=n;i++){
		cout<<"Please input your linkmans("<<i<<") and their phone numbers:(space to separate)"<<endl;
		cin>>addName>>addNum;												//space is ignored!
		book1.addLinkman(addName,addNum);
	}
	cout<<"Linkmans in your phonebook:"<<endl;
	book1.DispPhones();
	
	for(i=0;;i++){
		cout<<"Please input the linkman or his subnumber to find(input exit to exit):"<<endl;
		cin>>subStr;
		if(subStr =="exit") break;											//判断是否退出,否则一直循环查找
		else book1.findNum(subStr);
	}
	
	return 0;
}
