#include "Employee.h"
#include <iostream>
using namespace std;

class Technician : public Employee {
protected:
	double hourlyRate;					//����ÿСʱн��
	double hour;						//��������ʱ��
public:
	Technician(){
		hourlyRate=0;
		hour=0;
	}
	Technician(string name,double nu,double hR,double h):Employee(name,nu){
		hourlyRate=hR;
		hour=h;
	}
	Technician(const Technician &te){			//�������캯��
		name=te.name;
		num=te.num;
		monthpay=te.monthpay;
	}

	void setRate(double hR);					//���ü���ÿСʱн��

	void sethour(double h);						//���ü�������ʱ��

	virtual void pay();							//���㼼����н

	friend ostream & operator<<(ostream &,Technician &);			//���ء�<<����������������Ϣ(��������š���н��Сʱ���ʡ�����ʱ�䡢��н�ļ��㷽��)

};
