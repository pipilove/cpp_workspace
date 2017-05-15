#ifndef    DS_M_M
#define    DS_M_M
#include "Employee.h"
#include <iostream>
using namespace std;

class Manager :virtual public Employee{
protected:
	double fixPay;												//固定工资
public:
	Manager(){													//初始化固定工资
		fixPay=8000;
	};
	Manager(string name,double num):Employee(name,num){};
	Manager(string name,double num,double fix):Employee(name,num){
		fixPay=fix;
	};
	Manager(const Manager &ma){									//拷贝构造函数(必须加const!)
		name=ma.name;
		num=ma.num;
		fixPay=ma.fixPay;
		monthpay=ma.monthpay;
	}

	void setFixPay(double fixPay);								//设置固定工资
	 
	virtual void Pay();											//计算经理月薪

	friend ostream & operator<<(ostream &,Manager &);			//重载“<<”用于输出对象的信息(姓名、编号、月薪、固定工资、月薪的计算方法)
};
#endif