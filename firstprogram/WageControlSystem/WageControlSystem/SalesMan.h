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
	SalesMan(){															//���캯����ʼ�����۶�������
		sales=0;
		commRate=0;
	}
	SalesMan(string name,double nu,double sa,double com):Employee(name,nu){
		sales=sa;
		commRate=com;
	}
	SalesMan(const SalesMan &sam){										//�������캯��
		name=sam.name;
		num=sam.num;
		sales=sam.sales;
		commRate=sam.commRate;
		monthpay=sam.monthpay;
	}

	void setSales(double sa);											//�������۶�

	void setCom(double com);											//��������Ա�������

	virtual void pay();													//��������Ա����н

	friend ostream & operator<<(ostream &,const SalesMan &);			//���ء�<<����������������Ϣ(��������š���н�����۶����ʡ���н�ļ��㷽��)

};
#endif