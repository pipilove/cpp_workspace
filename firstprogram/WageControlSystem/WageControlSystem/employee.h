#ifndef    DS_E_E
#define    DS_E_E
#include <string>
#include <iostream>
using namespace std;

class Employee{
protected:
	string name;				//职员姓名
	double num;					//职员编号
	double monthpay;			//月薪总额
public:
	Employee(){								//自定义构造函数
	}
	Employee(string na,double nu){
		name=na;
		num=nu;
	}
	Employee(const Employee & em){			//拷贝构造函数
		name=em.name;
		num=em.num;
	}

	string setName(string);					//设置姓名
	string showName();						//提取姓名
	void setNum(double);					//设置个人编号
	double showNum();						//提取个人编号
	virtual void pay();						//计算月薪
	double showPay();						//提取月薪

	template <class T1,class T2>			//重载运算符进行月薪比较
	friend void operator > (T1,T2);
};

template <class T1,class T2>				//月薪比较
void operator > (T1 em1,T2 em2){
	cout << em1.monthpay>em2.monthpay ? True:False ;
	cout<<"("<<"em1.monthpay= "<<em1.monthpay<<","<<"em2.monthpay= "<<em2.monthpay<<")"<<endl;
}
#endif