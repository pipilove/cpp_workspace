#ifndef    DS_M_M
#define    DS_M_M
#include "Employee.h"
#include <iostream>
using namespace std;

class Manager :virtual public Employee{
protected:
	double fixPay;												//�̶�����
public:
	Manager(){													//��ʼ���̶�����
		fixPay=8000;
	};
	Manager(string name,double num):Employee(name,num){};
	Manager(string name,double num,double fix):Employee(name,num){
		fixPay=fix;
	};
	Manager(const Manager &ma){									//�������캯��(�����const!)
		name=ma.name;
		num=ma.num;
		fixPay=ma.fixPay;
		monthpay=ma.monthpay;
	}

	void setFixPay(double fixPay);								//���ù̶�����
	 
	virtual void Pay();											//���㾭����н

	friend ostream & operator<<(ostream &,Manager &);			//���ء�<<����������������Ϣ(��������š���н���̶����ʡ���н�ļ��㷽��)
};
#endif