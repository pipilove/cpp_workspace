#include "Employee.h"
#include <iostream>
using namespace std;

string Employee::setName(string name){		//��������
	return this->name=name;
}
string Employee::showName(){			//��ȡ����
	return name;
}
void Employee::setNum(double num){		//���ø��˱��
	this->num=num;
}
double Employee::showNum(){				//��ȡ���˱��
	return num;
}
void Employee::pay(){}
double Employee::showPay(){			//��ȡ��н
	return monthpay;
}
