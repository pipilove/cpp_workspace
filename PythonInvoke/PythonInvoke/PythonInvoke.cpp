// PythonInvoke.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include<Python.h>
#include <iostream>
using namespace std;

int main(){
	Py_Initialize(); /*��ʼ��python������,���߱�����Ҫ�õ�python������*/
	PyRun_SimpleString("import helloworld"); /*����python�ļ�*/
	PyRun_SimpleString("helloworld.printHello()");/*����python�ļ��еĺ���*/

	Py_Finalize(); /*����python���������ͷ���Դ*/
	system("pause");
	//getchar();
	return 0;
}
