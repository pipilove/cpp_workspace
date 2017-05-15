#ifndef    DC_SC_SC
#define    DC_SC_SC
#include "SalesMan.h"
#include "Manager.h"
#include <iostream>
using namespace std;

class SalesManager  :public Manager,public SalesMan{
public:
	SalesManager(){															//构造函数初始化固定工资和提成率
		fixPay=5000;
		commRate=0.005;
	}
	SalesManager(const SalesManager &sm){									//拷贝构造函数
		Manager::name=sm.Manager::name;
		Manager::num=sm.Manager::num;
		Manager::monthpay=sm.Manager::monthpay;
	}

	void setFixPay(double fixPay);											//设置固定工资

	virtual void pay();														//计算月薪

	double showPay();														//提取月薪

	friend ostream & operator<<(ostream &,SalesManager &);					//重载“<<”用于输出对象的信息(姓名、编号、月薪、固定工资、销售额、提成率、月薪的计算方法)
};
#endif
