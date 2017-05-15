// PythonInvoke.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<Python.h>
#include <iostream>
using namespace std;

int main(){
	Py_Initialize(); /*初始化python解释器,告诉编译器要用的python编译器*/
	PyRun_SimpleString("import helloworld"); /*调用python文件*/
	PyRun_SimpleString("helloworld.printHello()");/*调用python文件中的函数*/

	Py_Finalize(); /*结束python解释器，释放资源*/
	system("pause");
	//getchar();
	return 0;
}
