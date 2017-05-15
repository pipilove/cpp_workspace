#include "binary2txt.h"
#include "stdio.h"
#include <Locale.h>
int main(){
	//生成随机数据并以二进制形式存入binarydata.dat文件中
	//generateBinary();
	//从二进制文件binarydata.dat中读取数据并转换为十进制txt文件
	char binaryfname[20];
	printf("please input the name of binary file you want to convert to decimal.txt\n");
	gets(binaryfname);
	_wsetlocale(LC_ALL, L"chs");	//显示中文，locale.h中
	binary2txt(binaryfname,"decimal.txt");

	return 0;
}