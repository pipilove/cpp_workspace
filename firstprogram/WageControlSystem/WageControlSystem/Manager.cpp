#include "Manager.h"
#include <iostream>

void Manager::setFixPay(double fix){					//设置固定工资
	fixPay=fix;
}
void Manager::Pay(){				//计算经理月薪
	monthpay=fixPay;
}

ostream & operator<<(ostream &output,Manager &ma){			//重载“<<”用于输出对象的信息(姓名、编号、月薪、固定工资、月薪的计算方法)
	output<<"\tName: "<<ma.name<<endl;
	output<<"\tNumber: "<<ma.num<<endl;
	output<<"\tMonthpay: "<<ma.monthpay<<endl;
	output<<"\tfixPay: "<<ma.fixPay<<endl;
	output<<"\t\t(monthpay = fixPay...)"<<endl;
	return output;
}