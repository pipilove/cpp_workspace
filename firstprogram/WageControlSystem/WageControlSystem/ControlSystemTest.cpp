#include "manu.h"
#include "operation.h"

int main(){
	int n;					//ѡ�����˵��ϵĲ�������ӣ�
	mainmanu();				//��ʾ���˵�
	while(1){
		cin>>n;
		system("cls");		//������˵�
		switch(n){
		case 1:				//���ְԱ
			submanu1();
			addStaff();
			mainmanu();
			break;
		case 2:				//ɾ��ְԱ
			submanu2();
			delete1();
			mainmanu();
			break;
		case 3:				//����ְԱ
			find();
			mainmanu();
			break;
		case 4:				//��ʾ��������Ϣ
			cout<<"Output all the staff..."<<endl;
			output();
			mainmanu();
			break;
		case 5:				//�˳�ϵͳ
			exit(0);
		default:
			cout<<"Input error ! Please input again!"<<endl;
		}
	}
	return 0;
}