#ifndef    DS_O_O
#define    DS_O_O
#include "Manager.h"
#include "SalesMan.h"
#include "SalesManager.h"
#include "technician.h"
#include <vector>
#include <iostream>
using namespace std;

vector <Manager> Manager_vec;						//创建vector对象来记录不同职员的信息
vector <SalesMan> SalesMan_vec;
vector <SalesManager> SalesManager_vec;
vector <Technician> Technician_vec;

vector< Manager >::iterator it;						//用不同职员vector集合对象的迭代器进行操作（删除）
vector< Technician >::iterator it1;
vector< SalesMan >::iterator it2;
vector< SalesManager >::iterator it3;

Manager ma;											//创建不同职员对象，并通过addStaff()函数加入到vector容器中存储
SalesMan sa;
SalesManager sm;
Technician te;

string name;					//需要操作的名字
double num;						//需要操作的编号
double sales;					//需要操作的销售额
double fixPay;					//需要操作的固定工资
double commrate;				//需要操作的提成率
double hourlyRate;				//需要操作的小时工资
double hour;					//需要操作的小时数
int i;							//选择需要操作（添加、删除、查找）的职员类型

void addStaff(){				//添加职员函数
	bool errorInput;		//判断输入的数字是否正确，不正确则重新输入
	do{
		errorInput=false;
		cin>>i;
		switch (i){
		case 1:						//输入manager对象的信息(姓名、编号、固定工资）
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
			Manager_vec.push_back(ma);										//将对象压栈保存
			cout<<"Manager["<<Manager_vec.size()<<"] 已保存.."<<endl;
			system("pause");
			errorInput=false;												//输入正确不重新输入
			system("cls");
			break;
		case 2:						//输入Technician对象的信息(姓名、编号、小时工资、工作时间）
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
			cout<<"Technician["<<Technician_vec.size()<<"] 已保存..."<<endl;
			system("pause");
			errorInput=false;
			system("cls");
			break;
		case 3:							//输入SalesMan对象的信息(姓名、编号、销售额、提成率）
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
			cout<<"SalesMan["<<SalesMan_vec.size()<<"] 已保存..."<<endl;
			system("pause");
			errorInput=false;
			system("cls");
			break;
		case 4:									//输入SalesManager对象的信息(姓名、编号、固定工资、销售额、提成率）
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
			cout<<"SalesManager["<<SalesManager_vec.size()<<"] 已保存..."<<endl;
			system("pause");
			errorInput=false;
			system("cls");
			break;	
		case 5:																				//返回主菜单
			errorInput=false;
			system("cls");
			break;
		default:																			//输入错误则循环重新输入
			cout<<"输入错误，请重新输入： "<<endl;
			errorInput=true;
			break;
		}
	}while(errorInput);
}

void delete1(){
	bool errorInput;
	do{
		bool nofind=true;																	//判断是否找到
		errorInput=false;
		cin>>i;
		/*if(errorInput==false){
		system("cls");	//清除原来的显示
		}*/
		switch (i){
		case 1:																				//删除特定manager对象
			cout<<"请输入要删除的职员的姓名 ： ";
			cin>>name;
			for( it = Manager_vec.begin(); it != Manager_vec.end(); ++it )
				if((*it).showName() == name){												//查找需要删除职员的名字，(*it)必须加括号
					Manager_vec.erase(it);													//erase(pos)删除成员
					cout<<"Manager :"<<name<<" 已删除..."<<endl;
					nofind=false;
					break;
				}
				if(nofind)
					cout<<"This manager is not exit!"<<endl;								//未找到则输出提示
				system("pause");
				errorInput=false;
				system("cls");
				break;
		case 2:																				//删除Technician特定对象
			cout<<"请输入要删除的职员的姓名 ： ";
			cin>>name;
			for( it1 = Technician_vec.begin(); it1 != Technician_vec.end(); ++it1 )
				if((*it1).showName() == name){												//查找需要删除职员的名字
					Technician_vec.erase(it1);												//删除成员
					cout<<"Technician :"<<name<<" 已删除..."<<endl;
					nofind=false;
					break;
				}
				if(nofind)
					cout<<"This Technician is not exit!"<<endl;
				system("pause");
				errorInput=false;
				system("cls");
				break;
		case 3:																				//删除SalesMan特定对象
			cout<<"请输入要删除的职员的姓名 ： ";
			cin>>name;
			for( it2 = SalesMan_vec.begin(); it2 != SalesMan_vec.end(); ++it2 )
				if((*it2).showName() == name){												//查找需要删除职员的名字
					SalesMan_vec.erase(it2);												//删除成员
					cout<<"SalesMan :"<<name<<" 已删除..."<<endl;
					nofind=false;
					break;
				}
				if(nofind)
					cout<<"This SalesMan is not exit!"<<endl;
				system("pause");
				errorInput=false;
				system("cls");
				break;
		case 4:																				//删除SalesManager特定对象
			cout<<"请输入要删除的职员的姓名 ： ";
			cin>>name;
			for( it3 = SalesManager_vec.begin(); it3 != SalesManager_vec.end(); ++it3 )
				if((*it3).showName() == name){												//查找需要删除职员的名字
					SalesManager_vec.erase(it3);											//删除成员
					cout<<"SalesManager :"<<name<<" 已删除..."<<endl;
					nofind=false;
					break;
				}
				if(nofind)
					cout<<"This SalesManager is not exit!"<<endl;
				system("pause");
				errorInput=false;
				system("cls");
				break;
		case 5:																				//返回主菜单
			errorInput=false;
			system("cls");
			break;
		default:
			cout<<"输入错误，请重新输入： "<<endl;
			system("pause");
			break;
		}
	}while(errorInput);
}

void find(){
	bool nofind=true;				//判断是否找到
	cout<<"请输入要查找的职员的姓名 ： ";
	cin>>name;
	for( it = Manager_vec.begin(); it != Manager_vec.end(); ++it ){
		if((*it).showName() == name){												//查找具有此姓名的Manager职员并输出此人所有信息
			cout<<"Manager ["<<name<<"] 已找到..."<<endl;
			cout<<(*it);
			nofind=false;
		}
	}
	for( it1 = Technician_vec.begin(); it1 != Technician_vec.end(); ++it1 ){
		if((*it1).showName() == name){												//查找具有此姓名的Technician职员并输出此人所有信息
			cout<<"Technician ["<<name<<"] 已找到..."<<endl;
			cout<<(*it1);
			nofind=false;
		}
	}
	for( it2 = SalesMan_vec.begin(); it2 != SalesMan_vec.end(); ++it2 ){
		if((*it2).showName() == name){												//查找具有此姓名的SalesMan职员并输出此人所有信息
			cout<<"SalesMan ["<<name<<"] 已找到..."<<endl;
			cout<<(*it2);
			nofind=false;
		}
	}
	for( it3 = SalesManager_vec.begin(); it3 != SalesManager_vec.end(); ++it3 ){
		if((*it3).showName() == name){												//查找具有此姓名的SalesManager职员并输出此人所有信息
			cout<<"SalesManager ["<<name<<"] 已找到..."<<endl;
			cout<<(*it3);
			nofind=false;
		}
	}
	if(nofind)
		cout<<"This manager is not exit!"<<endl;									//未找到任何职员则输出提示
	system("pause");
}

void output(){																						//输出所有职员
	for( it = Manager_vec.begin(); it != Manager_vec.end(); ++it ){									//输出所有的manager职员
			cout<<"Manager ......"<<endl;
			cout<<(*it);
		}
	for( it1 = Technician_vec.begin(); it1 != Technician_vec.end(); ++it1 ){						//输出所有的Technician职员
			cout<<"Technician ......"<<endl;
			cout<<(*it1);
	}
	for( it2 = SalesMan_vec.begin(); it2 != SalesMan_vec.end(); ++it2 ){							//输出所有的SalesMan职员
			cout<<"SalesMan ......"<<endl;
			cout<<(*it2);
	}
	for( it3 = SalesManager_vec.begin(); it3 != SalesManager_vec.end(); ++it3 ){					//输出所有的SalesManager职员
			cout<<"SalesManager ......"<<endl;
			cout<<(*it3);
	}
}
#endif