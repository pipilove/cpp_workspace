#include "Manager.h"
#include <iostream>

void Manager::setFixPay(double fix){					//���ù̶�����
	fixPay=fix;
}
void Manager::Pay(){				//���㾭����н
	monthpay=fixPay;
}

ostream & operator<<(ostream &output,Manager &ma){			//���ء�<<����������������Ϣ(��������š���н���̶����ʡ���н�ļ��㷽��)
	output<<"\tName: "<<ma.name<<endl;
	output<<"\tNumber: "<<ma.num<<endl;
	output<<"\tMonthpay: "<<ma.monthpay<<endl;
	output<<"\tfixPay: "<<ma.fixPay<<endl;
	output<<"\t\t(monthpay = fixPay...)"<<endl;
	return output;
}