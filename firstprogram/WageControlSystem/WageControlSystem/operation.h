#ifndef    DS_O_O
#define    DS_O_O
#include "Manager.h"
#include "SalesMan.h"
#include "SalesManager.h"
#include "technician.h"
#include <vector>
#include <iostream>
using namespace std;

vector <Manager> Manager_vec;						//����vector��������¼��ְͬԱ����Ϣ
vector <SalesMan> SalesMan_vec;
vector <SalesManager> SalesManager_vec;
vector <Technician> Technician_vec;

vector< Manager >::iterator it;						//�ò�ְͬԱvector���϶���ĵ��������в�����ɾ����
vector< Technician >::iterator it1;
vector< SalesMan >::iterator it2;
vector< SalesManager >::iterator it3;

Manager ma;											//������ְͬԱ���󣬲�ͨ��addStaff()�������뵽vector�����д洢
SalesMan sa;
SalesManager sm;
Technician te;

string name;					//��Ҫ����������
double num;						//��Ҫ�����ı��
double sales;					//��Ҫ���������۶�
double fixPay;					//��Ҫ�����Ĺ̶�����
double commrate;				//��Ҫ�����������
double hourlyRate;				//��Ҫ������Сʱ����
double hour;					//��Ҫ������Сʱ��
int i;							//ѡ����Ҫ��������ӡ�ɾ�������ң���ְԱ����

void addStaff(){				//���ְԱ����
	bool errorInput;		//�ж�����������Ƿ���ȷ������ȷ����������
	do{
		errorInput=false;
		cin>>i;
		switch (i){
		case 1:						//����manager�������Ϣ(��������š��̶����ʣ�
			cout<<"\tName: ";
			cin>>name;
			cout<<"\tNumber: ";
			cin>>num;
			cout<<"\tfixPay: ";
			cin>>fixPay;
			ma.setName(name);
			ma.setNum(num);
			ma.setFixPay(fixPay);
			ma.Pay();
			Manager_vec.push_back(ma);										//������ѹջ����
			cout<<"Manager["<<Manager_vec.size()<<"] �ѱ���.."<<endl;
			system("pause");
			errorInput=false;												//������ȷ����������
			system("cls");
			break;
		case 2:						//����Technician�������Ϣ(��������š�Сʱ���ʡ�����ʱ�䣩
			cout<<"\tName: ";
			cin>>name;
			cout<<"\tNumber: ";
			cin>>num;
			cout<<"\thourlyRate: ";
			cin>>hourlyRate;
			cout<<"\tworkhour: ";
			cin>>hour;
			te.setName(name);
			te.setNum(num);
			te.setRate(hour);
			te.setRate(hourlyRate);
			te.sethour(hour);
			te.pay();
			Technician_vec.push_back(te);
			cout<<"Technician["<<Technician_vec.size()<<"] �ѱ���..."<<endl;
			system("pause");
			errorInput=false;
			system("cls");
			break;
		case 3:							//����SalesMan�������Ϣ(��������š����۶����ʣ�
			cout<<"\tName: ";
			cin>>name;
			cout<<"\tNumber: ";
			cin>>num;
			cout<<"\tsales: ";
			cin>>sales;
			cout<<"\tcommRate: ";
			cin>>commrate;
			sa.setName(name);
			sa.setNum(num);
			sa.setSales(sales);
			sa.setCom(commrate);
			sa.pay();
			SalesMan_vec.push_back(sa);
			cout<<"SalesMan["<<SalesMan_vec.size()<<"] �ѱ���..."<<endl;
			system("pause");
			errorInput=false;
			system("cls");
			break;
		case 4:									//����SalesManager�������Ϣ(��������š��̶����ʡ����۶����ʣ�
			cout<<"\tName: ";
			cin>>name;
			cout<<"\tNumber: ";
			cin>>num;
			cout<<"\tfixPay: ";
			cin>>fixPay;
			cout<<"\tsales: ";
			cin>>sales;
			cout<<"\tcommRate: ";
			cin>>commrate;
			sm.setName(name);
			sm.setNum(num);
			sm.setFixPay(fixPay);
			sm.setSales(sales);
			sm.setCom(commrate);
			sm.pay();
			SalesManager_vec.push_back(sm);
			cout<<"SalesManager["<<SalesManager_vec.size()<<"] �ѱ���..."<<endl;
			system("pause");
			errorInput=false;
			system("cls");
			break;	
		case 5:																				//�������˵�
			errorInput=false;
			system("cls");
			break;
		default:																			//���������ѭ����������
			cout<<"����������������룺 "<<endl;
			errorInput=true;
			break;
		}
	}while(errorInput);
}

void delete1(){
	bool errorInput;
	do{
		bool nofind=true;																	//�ж��Ƿ��ҵ�
		errorInput=false;
		cin>>i;
		/*if(errorInput==false){
		system("cls");	//���ԭ������ʾ
		}*/
		switch (i){
		case 1:																				//ɾ���ض�manager����
			cout<<"������Ҫɾ����ְԱ������ �� ";
			cin>>name;
			for( it = Manager_vec.begin(); it != Manager_vec.end(); ++it )
				if((*it).showName() == name){												//������Ҫɾ��ְԱ�����֣�(*it)���������
					Manager_vec.erase(it);													//erase(pos)ɾ����Ա
					cout<<"Manager :"<<name<<" ��ɾ��..."<<endl;
					nofind=false;
					break;
				}
				if(nofind)
					cout<<"This manager is not exit!"<<endl;								//δ�ҵ��������ʾ
				system("pause");
				errorInput=false;
				system("cls");
				break;
		case 2:																				//ɾ��Technician�ض�����
			cout<<"������Ҫɾ����ְԱ������ �� ";
			cin>>name;
			for( it1 = Technician_vec.begin(); it1 != Technician_vec.end(); ++it1 )
				if((*it1).showName() == name){												//������Ҫɾ��ְԱ������
					Technician_vec.erase(it1);												//ɾ����Ա
					cout<<"Technician :"<<name<<" ��ɾ��..."<<endl;
					nofind=false;
					break;
				}
				if(nofind)
					cout<<"This Technician is not exit!"<<endl;
				system("pause");
				errorInput=false;
				system("cls");
				break;
		case 3:																				//ɾ��SalesMan�ض�����
			cout<<"������Ҫɾ����ְԱ������ �� ";
			cin>>name;
			for( it2 = SalesMan_vec.begin(); it2 != SalesMan_vec.end(); ++it2 )
				if((*it2).showName() == name){												//������Ҫɾ��ְԱ������
					SalesMan_vec.erase(it2);												//ɾ����Ա
					cout<<"SalesMan :"<<name<<" ��ɾ��..."<<endl;
					nofind=false;
					break;
				}
				if(nofind)
					cout<<"This SalesMan is not exit!"<<endl;
				system("pause");
				errorInput=false;
				system("cls");
				break;
		case 4:																				//ɾ��SalesManager�ض�����
			cout<<"������Ҫɾ����ְԱ������ �� ";
			cin>>name;
			for( it3 = SalesManager_vec.begin(); it3 != SalesManager_vec.end(); ++it3 )
				if((*it3).showName() == name){												//������Ҫɾ��ְԱ������
					SalesManager_vec.erase(it3);											//ɾ����Ա
					cout<<"SalesManager :"<<name<<" ��ɾ��..."<<endl;
					nofind=false;
					break;
				}
				if(nofind)
					cout<<"This SalesManager is not exit!"<<endl;
				system("pause");
				errorInput=false;
				system("cls");
				break;
		case 5:																				//�������˵�
			errorInput=false;
			system("cls");
			break;
		default:
			cout<<"����������������룺 "<<endl;
			system("pause");
			break;
		}
	}while(errorInput);
}

void find(){
	bool nofind=true;				//�ж��Ƿ��ҵ�
	cout<<"������Ҫ���ҵ�ְԱ������ �� ";
	cin>>name;
	for( it = Manager_vec.begin(); it != Manager_vec.end(); ++it ){
		if((*it).showName() == name){												//���Ҿ��д�������ManagerְԱ���������������Ϣ
			cout<<"Manager ["<<name<<"] ���ҵ�..."<<endl;
			cout<<(*it);
			nofind=false;
		}
	}
	for( it1 = Technician_vec.begin(); it1 != Technician_vec.end(); ++it1 ){
		if((*it1).showName() == name){												//���Ҿ��д�������TechnicianְԱ���������������Ϣ
			cout<<"Technician ["<<name<<"] ���ҵ�..."<<endl;
			cout<<(*it1);
			nofind=false;
		}
	}
	for( it2 = SalesMan_vec.begin(); it2 != SalesMan_vec.end(); ++it2 ){
		if((*it2).showName() == name){												//���Ҿ��д�������SalesManְԱ���������������Ϣ
			cout<<"SalesMan ["<<name<<"] ���ҵ�..."<<endl;
			cout<<(*it2);
			nofind=false;
		}
	}
	for( it3 = SalesManager_vec.begin(); it3 != SalesManager_vec.end(); ++it3 ){
		if((*it3).showName() == name){												//���Ҿ��д�������SalesManagerְԱ���������������Ϣ
			cout<<"SalesManager ["<<name<<"] ���ҵ�..."<<endl;
			cout<<(*it3);
			nofind=false;
		}
	}
	if(nofind)
		cout<<"This manager is not exit!"<<endl;									//δ�ҵ��κ�ְԱ�������ʾ
	system("pause");
}

void output(){																						//�������ְԱ
	for( it = Manager_vec.begin(); it != Manager_vec.end(); ++it ){									//������е�managerְԱ
			cout<<"Manager ......"<<endl;
			cout<<(*it);
		}
	for( it1 = Technician_vec.begin(); it1 != Technician_vec.end(); ++it1 ){						//������е�TechnicianְԱ
			cout<<"Technician ......"<<endl;
			cout<<(*it1);
	}
	for( it2 = SalesMan_vec.begin(); it2 != SalesMan_vec.end(); ++it2 ){							//������е�SalesManְԱ
			cout<<"SalesMan ......"<<endl;
			cout<<(*it2);
	}
	for( it3 = SalesManager_vec.begin(); it3 != SalesManager_vec.end(); ++it3 ){					//������е�SalesManagerְԱ
			cout<<"SalesManager ......"<<endl;
			cout<<(*it3);
	}
}
#endif