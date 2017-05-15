#include "Employee.h"
#include <iostream>
using namespace std;

class Technician : public Employee {
protected:
	double hourlyRate;					//技工每小时薪资
	double hour;						//技工工作时间
public:
	Technician(){
		hourlyRate=0;
		hour=0;
	}
	Technician(string name,double nu,double hR,double h):Employee(name,nu){
		hourlyRate=hR;
		hour=h;
	}
	Technician(const Technician &te){			//拷贝构造函数
		name=te.name;
		num=te.num;
		monthpay=te.monthpay;
	}

	void setRate(double hR);					//设置技工每小时薪资

	void sethour(double h);						//设置技工工作时间

	virtual void pay();							//计算技工月薪

	friend ostream & operator<<(ostream &,Technician &);			//重载“<<”用于输出对象的信息(姓名、编号、月薪、小时工资、工作时间、月薪的计算方法)

};
