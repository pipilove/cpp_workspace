#include "SalesMan.h"
#include <iostream>

void SalesMan::setSales(double sa){					//�������۶�
	sales=sa;
}
void SalesMan::setCom(double com){					//��������Ա�������
	commRate=com;
}
void SalesMan::pay(){							//��������Ա����н
	monthpay =sales*commRate;
}

ostream & operator<<(ostream &output,const SalesMan &sa){				//���ء�<<����������������Ϣ(��������š���н�����۶����ʡ���н�ļ��㷽��)
	output<<"\tName: "<<sa.name<<endl;
	output<<"\tNumber: "<<sa.num<<endl;
	output<<"\tMonthpay: "<<sa.monthpay<<endl;
	output<<"\tSales: "<<sa.sales<<endl;
	output<<"\tCommRate: "<<sa.commRate<<endl;
	output<<"\t(monthpay =sales*commRate...)"<<endl;
	return output;
}
