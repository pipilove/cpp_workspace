#include "SalesManager.h"

void SalesManager::setFixPay(double fix){					//���ù̶�����
	fixPay=fix;
}

	void SalesManager::pay(){						//������н
		Manager::monthpay =sales*commRate+fixPay;
	}
	double SalesManager::showPay(){			//��ȡ��н
		return Manager::monthpay;
	}

	ostream & operator<<(ostream &output,SalesManager &sm){					//���ء�<<����������������Ϣ(��������š���н���̶����ʡ����۶����ʡ���н�ļ��㷽��)
		output<<"\tName: "<<sm.Manager::name<<endl;
		output<<"\tNumber: "<<sm.Manager::num<<endl;
		output<<"\tMonthpay: "<<sm.Manager::monthpay<<endl;
		output<<"\tFixPay: "<<sm.fixPay<<endl;
		output<<"\tSales: "<<sm.sales<<endl;
		output<<"\tCommRate: "<<sm.commRate<<endl;
		output<<"\t(monthpay =sales*commRate+fixPay...)"<<endl;
		return output;
	}