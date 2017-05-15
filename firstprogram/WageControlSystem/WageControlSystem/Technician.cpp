#include "Technician.h"
#include <iostream>

void Technician::setRate(double hR){				//设置技工每小时薪资
	hourlyRate=hR;
}
void Technician::sethour(double h){					//设置技工工作时间
	hour=h;
}
void Technician::pay(){				//计算技工月薪
	monthpay = hourlyRate * hour;
}

ostream & operator<<(ostream &output,Technician &te){			//重载“<<”用于输出对象的信息(姓名、编号、月薪、小时工资、工作时间、月薪的计算方法)
	output<<"\tName: "<<te.name<<endl;
	output<<"\tNumber: "<<te.num<<endl;
	output<<"\tMonthpay: "<<te.monthpay<<endl;
	output<<"\thourlyRate: "<<te.hourlyRate<<endl;
	output<<"\thour: "<<te.hour<<endl;
	output<<"\t(monthpay = hourlyRate * hour...)"<<endl;
	return output;
}