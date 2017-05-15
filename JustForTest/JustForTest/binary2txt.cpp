/*	函数实现读取二进制文件并转换为十进制文件的功能	*/
#define random(low,upper) ((rand()*rand())%((upper)-(low)+1)+(low))
#define LEN    10
#define LOWER  0
#define UPPER  65535
typedef wchar_t ITEMTYPE;

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <locale.h>

//生成随机ITEMTYPE数据并以二进制形式存入binarydata.dat文件中
void generateBinary(){
	ITEMTYPE temp[LEN];
	FILE* fp;
	if((fp=fopen("binarydata.dat","wb"))==NULL){
		printf("file open fail");system("pause");exit(0);}
	srand((unsigned)time(0));
	for(int i=0;i<=LEN-1;i++){
		temp[i]=L'我';//(wchar_t)random(LOWER,UPPER);
		_wsetlocale(LC_ALL, L"chs");	//显示中文，locale.h中
		//wprintf(L"%c ",temp[i]);
		fwrite(&temp[i],sizeof(temp[0]),1,fp);
	}
	fclose(fp);
}

//从二进制文件inputfname.dat中读取数据并转换为十进制txt文件
void binary2txt(char* inputfname,char* outputfname){
	FILE* srs_fp;
	FILE* dst_fp;
	if((dst_fp=fopen(outputfname,"w"))==NULL){
		printf("open %s fail ......",outputfname);system("pause");exit(0);}
	if((srs_fp=fopen(inputfname,"rb"))==NULL){
		printf("open %s fail ......",inputfname);system("pause");exit(0);}

	ITEMTYPE temp;int i=10;
	while(i--){//feof(srs_fp)
		if((fread(&temp,sizeof(ITEMTYPE),1,srs_fp))!=1){	//读取文件inputfname.dat中的二进制数据,将二进制数据看成对应的ITEMTYPE类型
			printf("file %s read fail ......\n",inputfname);system("pause");exit(0);}		//?????
		fwprintf(dst_fp,L"%c ",temp);		//将数据以wchar_t形式写入文件outputfname.txt中!!!	
		wprintf(L"%c ",temp);
	}

	fclose(srs_fp);
	fclose(dst_fp);
}
