#include "SalesManager.h"

void SalesManager::setFixPay(double fix){					//设置固定工资
	fixPay=fix;
}

	void SalesManager::pay(){						//计算月薪
		Manager::monthpay =sales*commRate+fixPay;
	}
	double SalesManager::showPay(){			//提取月薪
		return Manager::monthpay;
	}

	ostream & operator<<(ostream &output,SalesManager &sm){					//重载“<<”用于输出对象的信息(姓名、编号、月薪、固定工资、销售额、提成率、月薪的计算方法)
		output<<"\tName: "<<sm.Manager::name<<endl;
		output<<"\tNumber: "<<sm.Manager::num<<endl;
		output<<"\tMonthpay: "<<sm.Manager::monthpay<<endl;
		output<<"\tFixPay: "<<sm.fixPay<<endl;
		output<<"\tSales: "<<sm.sales<<endl;
		output<<"\tCommRate: "<<sm.commRate<<endl;
		output<<"\t(monthpay =sales*commRate+fixPay...)"<<endl;
		return output;
	}