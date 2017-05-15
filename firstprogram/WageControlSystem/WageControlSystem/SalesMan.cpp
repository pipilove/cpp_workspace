#include "SalesMan.h"
#include <iostream>

void SalesMan::setSales(double sa){					//设置销售额
	sales=sa;
}
void SalesMan::setCom(double com){					//设置销售员的提成率
	commRate=com;
}
void SalesMan::pay(){							//计算销售员的月薪
	monthpay =sales*commRate;
}

ostream & operator<<(ostream &output,const SalesMan &sa){				//重载“<<”用于输出对象的信息(姓名、编号、月薪、销售额、提成率、月薪的计算方法)
	output<<"\tName: "<<sa.name<<endl;
	output<<"\tNumber: "<<sa.num<<endl;
	output<<"\tMonthpay: "<<sa.monthpay<<endl;
	output<<"\tSales: "<<sa.sales<<endl;
	output<<"\tCommRate: "<<sa.commRate<<endl;
	output<<"\t(monthpay =sales*commRate...)"<<endl;
	return output;
}
