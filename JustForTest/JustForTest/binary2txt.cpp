/*	����ʵ�ֶ�ȡ�������ļ���ת��Ϊʮ�����ļ��Ĺ���	*/
#define random(low,upper) ((rand()*rand())%((upper)-(low)+1)+(low))
#define LEN    10
#define LOWER  0
#define UPPER  65535
typedef wchar_t ITEMTYPE;

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <locale.h>

//�������ITEMTYPE���ݲ��Զ�������ʽ����binarydata.dat�ļ���
void generateBinary(){
	ITEMTYPE temp[LEN];
	FILE* fp;
	if((fp=fopen("binarydata.dat","wb"))==NULL){
		printf("file open fail");system("pause");exit(0);}
	srand((unsigned)time(0));
	for(int i=0;i<=LEN-1;i++){
		temp[i]=L'��';//(wchar_t)random(LOWER,UPPER);
		_wsetlocale(LC_ALL, L"chs");	//��ʾ���ģ�locale.h��
		//wprintf(L"%c ",temp[i]);
		fwrite(&temp[i],sizeof(temp[0]),1,fp);
	}
	fclose(fp);
}

//�Ӷ������ļ�inputfname.dat�ж�ȡ���ݲ�ת��Ϊʮ����txt�ļ�
void binary2txt(char* inputfname,char* outputfname){
	FILE* srs_fp;
	FILE* dst_fp;
	if((dst_fp=fopen(outputfname,"w"))==NULL){
		printf("open %s fail ......",outputfname);system("pause");exit(0);}
	if((srs_fp=fopen(inputfname,"rb"))==NULL){
		printf("open %s fail ......",inputfname);system("pause");exit(0);}

	ITEMTYPE temp;int i=10;
	while(i--){//feof(srs_fp)
		if((fread(&temp,sizeof(ITEMTYPE),1,srs_fp))!=1){	//��ȡ�ļ�inputfname.dat�еĶ���������,�����������ݿ��ɶ�Ӧ��ITEMTYPE����
			printf("file %s read fail ......\n",inputfname);system("pause");exit(0);}		//?????
		fwprintf(dst_fp,L"%c ",temp);		//��������wchar_t��ʽд���ļ�outputfname.txt��!!!	
		wprintf(L"%c ",temp);
	}

	fclose(srs_fp);
	fclose(dst_fp);
}
