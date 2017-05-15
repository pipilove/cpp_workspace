// findcellphone.cpp : Defines the entry point for the console application.
//����Ƶ绰������

#include "stdafx.h"
#include "iostream"
#include "string"

using namespace std;

class CellPhone{
private:
	
	string name[20];						//���linkman��������20��
	string number[20];
	static int count;						//�洢����ϵ�˸����ļ�����static 
public:
	void addLinkman(string,string);
	void findNum(string);
	void DispPhones();
};
int CellPhone::count=0;
void CellPhone::addLinkman(string addName,string addNum){			//����linkman,ע��count
	name[count]=addName;
	number[count++]=addNum;
}
void CellPhone::findNum(string subStr){								//����substrģ������linkman
	bool iffind=false;
	for(int j=0;j<count;j++){
		bool flag=true;
		for(int i=0;i<subStr.length();i++){								//subStr.length()����substr���ַ�
			if (subStr[i]!=name[j][i]&&subStr[i]!=number[j][i])			//�Ƚ�substr��i���ַ���number[j]��name[j]�ĵ�i���ַ�
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
void CellPhone::DispPhones(){											//��ʾ������ϵ��
	for(int i=0;i<count;i++)
		cout<<name[i]<<" "<<number[i]<<endl;
}


int main()
{
	int n;
	string addName,addNum,subStr;
	
	cout<<"The number of your linkmans and their phone numbers: ";			//��ϵ�˸���
	cin>>n;
	if(n>20){
		cout<<"The number of the linkman is overdo!"<<endl;
		return 0;
	}
	CellPhone book1;														//������ϵ��
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
		if(subStr =="exit") break;											//�ж��Ƿ��˳�,����һֱѭ������
		else book1.findNum(subStr);
	}
	
	return 0;
}
