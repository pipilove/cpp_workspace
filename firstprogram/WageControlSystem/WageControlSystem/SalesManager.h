#ifndef    DC_SC_SC
#define    DC_SC_SC
#include "SalesMan.h"
#include "Manager.h"
#include <iostream>
using namespace std;

class SalesManager  :public Manager,public SalesMan{
public:
	SalesManager(){															//���캯����ʼ���̶����ʺ������
		fixPay=5000;
		commRate=0.005;
	}
	SalesManager(const SalesManager &sm){									//�������캯��
		Manager::name=sm.Manager::name;
		Manager::num=sm.Manager::num;
		Manager::monthpay=sm.Manager::monthpay;
	}

	void setFixPay(double fixPay);											//���ù̶�����

	virtual void pay();														//������н

	double showPay();														//��ȡ��н

	friend ostream & operator<<(ostream &,SalesManager &);					//���ء�<<����������������Ϣ(��������š���н���̶����ʡ����۶����ʡ���н�ļ��㷽��)
};
#endif
