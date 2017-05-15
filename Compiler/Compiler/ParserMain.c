/****************************************************************************/
/*			词法分析和语法分析主程序的编译器实现 皮皮 2014-5-20			    */
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
	runLexAnalyzer();	//词法分析主程序
	lex_prompt();
	system("pause");
	printf("\n\n");
	if(	( (errorfp = fopen("testFun.err","w"))	&&	(varfp	= fopen("testFun.var","w")) && 
		(profp	= fopen("testFun.pro","w"))	)== NULL){
		printf("file open fail !!!\n");
		system("pause");
		exit(-1);
	}
	getWord();			//从词法输出文件中获取单词
	procedure();		//语法分析主程序
	parser_prompt();

	fclose(errorfp);
	fclose(varfp);
	fclose(profp);
	copyFile();
	system("pause");
	return 0;
}

//提示语句
void lex_prompt(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("词法分析结束  ... \n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
}
void parser_prompt(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("语法分析结束  ... \n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
}

