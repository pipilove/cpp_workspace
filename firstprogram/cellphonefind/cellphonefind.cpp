// cellphonefind.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
//#include "String";
using namespace std;

struct Book{
	char name[20]; //string name;�ַ������ܶ��壿
	char number[15];
}CellBook[]={{"13547815046","Pipi"},
{"18200292573","Titi"},
{"15624978546","GaoWei"},
{"13846857964","�¼�"},
{"15654876846","����"},
{"15046868946","�Ʊ�"},
{"13446876466","����"},
{"15880464855","������"},
{"13946781316","����"},
{"13434235465","���"}
};
bool Find(char * List,char * input){
	if((strlen(List)<strlen(input))||strlen(input)==0)
		return false;
	int i=0;
	while(List[i]!='\0'&&input[i]!='\0'&&input[i]==List[i])
		i++;
	if(input[i]=='\0')
		return true;
	else
		return false;
}
int main()
{
	int phones=sizeof(CellBook)/sizeof(Book);
	char input[20];
	cout<<"Please input a name or a phone number"<<endl;
	cin>>input;
	for(int i=0;i<phones;i++){
		if(Find(CellBook[i].number,input))
			cout<<CellBook[i].name<<"\t"<<CellBook[i].number<<endl;
	}
	for(i=0;i<phones;i++){ //�����ظ����� int i=0;
		if(Find(CellBook[i].name,input))
			cout<<CellBook[i].name<<"\t"<<CellBook[i].number<<endl;
	}
	
	return 0;
}