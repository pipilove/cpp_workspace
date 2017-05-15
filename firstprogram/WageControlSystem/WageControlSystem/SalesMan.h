#ifndef    DS_S_S
#define    DS_S_S
#include "Employee.h"
#include <iostream>
using namespace std;

class SalesMan :virtual public Employee{
protected:
	double sales;
	double commRate;
public:
	SalesMan(){															//构造函数初始化销售额和提成率
		sales=0;
		commRate=0;
	}
	SalesMan(string name,double nu,double sa,double com):Employee(name,nu){
		sales=sa;
		commRate=com;
	}
	SalesMan(const SalesMan &sam){										//拷贝构造函数
		name=sam.name;
		num=sam.num;
		sales=sam.sales;
		commRate=sam.commRate;
		monthpay=sam.monthpay;
	}

	void setSales(double sa);											//设置销售额

	void setCom(double com);											//设置销售员的提成率

	virtual void pay();													//计算销售员的月薪

	friend ostream & operator<<(ostream &,const SalesMan &);			//重载“<<”用于输出对象的信息(姓名、编号、月薪、销售额、提成率、月薪的计算方法)

};
#endif