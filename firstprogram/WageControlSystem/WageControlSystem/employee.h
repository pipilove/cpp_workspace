#ifndef    DS_E_E
#define    DS_E_E
#include <string>
#include <iostream>
using namespace std;

class Employee{
protected:
	string name;				//ְԱ����
	double num;					//ְԱ���
	double monthpay;			//��н�ܶ�
public:
	Employee(){								//�Զ��幹�캯��
	}
	Employee(string na,double nu){
		name=na;
		num=nu;
	}
	Employee(const Employee & em){			//�������캯��
		name=em.name;
		num=em.num;
	}

	string setName(string);					//��������
	string showName();						//��ȡ����
	void setNum(double);					//���ø��˱��
	double showNum();						//��ȡ���˱��
	virtual void pay();						//������н
	double showPay();						//��ȡ��н

	template <class T1,class T2>			//���������������н�Ƚ�
	friend void operator > (T1,T2);
};

template <class T1,class T2>				//��н�Ƚ�
void operator > (T1 em1,T2 em2){
	cout << em1.monthpay>em2.monthpay ? True:False ;
	cout<<"("<<"em1.monthpay= "<<em1.monthpay<<","<<"em2.monthpay= "<<em2.monthpay<<")"<<endl;
}
#endif