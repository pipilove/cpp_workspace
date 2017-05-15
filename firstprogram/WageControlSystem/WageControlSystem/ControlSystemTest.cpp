#include "manu.h"
#include "operation.h"

int main(){
	int n;					//选择主菜单上的操作（添加）
	mainmanu();				//显示主菜单
	while(1){
		cin>>n;
		system("cls");		//清除主菜单
		switch(n){
		case 1:				//添加职员
			submanu1();
			addStaff();
			mainmanu();
			break;
		case 2:				//删除职员
			submanu2();
			delete1();
			mainmanu();
			break;
		case 3:				//查找职员
			find();
			mainmanu();
			break;
		case 4:				//显示所有人信息
			cout<<"Output all the staff..."<<endl;
			output();
			mainmanu();
			break;
		case 5:				//退出系统
			exit(0);
		default:
			cout<<"Input error ! Please input again!"<<endl;
		}
	}
	return 0;
}