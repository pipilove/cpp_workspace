#include "Technician.h"
#include <iostream>

void Technician::setRate(double hR){				//���ü���ÿСʱн��
	hourlyRate=hR;
}
void Technician::sethour(double h){					//���ü�������ʱ��
	hour=h;
}
void Technician::pay(){				//���㼼����н
	monthpay = hourlyRate * hour;
}

ostream & operator<<(ostream &output,Technician &te){			//���ء�<<����������������Ϣ(��������š���н��Сʱ���ʡ�����ʱ�䡢��н�ļ��㷽��)
	output<<"\tName: "<<te.name<<endl;
	output<<"\tNumber: "<<te.num<<endl;
	output<<"\tMonthpay: "<<te.monthpay<<endl;
	output<<"\thourlyRate: "<<te.hourlyRate<<endl;
	output<<"\thour: "<<te.hour<<endl;
	output<<"\t(monthpay = hourlyRate * hour...)"<<endl;
	return output;
}