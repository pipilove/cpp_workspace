#include "Employee.h"
#include <iostream>
using namespace std;

string Employee::setName(string name){		//设置姓名
	return this->name=name;
}
string Employee::showName(){			//提取姓名
	return name;
}
void Employee::setNum(double num){		//设置个人编号
	this->num=num;
}
double Employee::showNum(){				//提取个人编号
	return num;
}
void Employee::pay(){}
double Employee::showPay(){			//提取月薪
	return monthpay;
}
