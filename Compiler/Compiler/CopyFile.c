#include <stdio.h>
#include <stdlib.h>

/*	�﷨������ȷ��copy�ļ�.dyd��.dys	*/
void copyFile(){
	FILE* dyd;		//.dyd
	FILE* dys;		//.dys
	char str[20];
	if(	( (dyd	= fopen("testFun.dyd","r"))  && (dys	= fopen("testFun.dys","w")) )== NULL){
		printf("file open fail !!!\n");
		system("pause");
		exit(-1);
	}
	while(fgets(str,20,dyd))
		fputs(str,dys);
	fclose(dyd);
	fclose(dys);
}
