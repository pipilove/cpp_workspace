#include "binary2txt.h"
#include "stdio.h"
#include <Locale.h>
int main(){
	//����������ݲ��Զ�������ʽ����binarydata.dat�ļ���
	//generateBinary();
	//�Ӷ������ļ�binarydata.dat�ж�ȡ���ݲ�ת��Ϊʮ����txt�ļ�
	char binaryfname[20];
	printf("please input the name of binary file you want to convert to decimal.txt\n");
	gets(binaryfname);
	_wsetlocale(LC_ALL, L"chs");	//��ʾ���ģ�locale.h��
	binary2txt(binaryfname,"decimal.txt");

	return 0;
}