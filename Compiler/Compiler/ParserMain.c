/****************************************************************************/
/*			�ʷ��������﷨����������ı�����ʵ�� ƤƤ 2014-5-20			    */
/****************************************************************************/
#include "Pro.h"
#include "GetWordStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "CopyFile.h"

extern int runLexAnalyzer();
void lex_prompt();
void parser_prompt();

FILE* errorfp;	//.err
FILE* varfp;	//.var
FILE* profp;	//.pro

int main(){
	runLexAnalyzer();	//�ʷ�����������
	lex_prompt();
	system("pause");
	printf("\n\n");
	if(	( (errorfp = fopen("testFun.err","w"))	&&	(varfp	= fopen("testFun.var","w")) && 
		(profp	= fopen("testFun.pro","w"))	)== NULL){
		printf("file open fail !!!\n");
		system("pause");
		exit(-1);
	}
	getWord();			//�Ӵʷ�����ļ��л�ȡ����
	procedure();		//�﷨����������
	parser_prompt();

	fclose(errorfp);
	fclose(varfp);
	fclose(profp);
	copyFile();
	system("pause");
	return 0;
}

//��ʾ���
void lex_prompt(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("�ʷ���������  ... \n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
}
void parser_prompt(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("�﷨��������  ... \n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
}

