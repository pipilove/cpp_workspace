#include <stdio.h>
#include <stdlib.h>
#include "GetWordStruct.h"

word* all_word[256];
int word_index;

/*	从file中获取单词	*/
void getWord(){
	FILE* fp;
	word* word1;
	char* str = (char*)malloc(sizeof(char)*20);
	if( (fp = fopen("testFun.dyd","r")) == NULL){
		printf("testFun.dyd file open fail !!!\n");
		system("pause");
		exit(-1);
	}
	while( (fscanf(fp,"%s",str)) == 1){	//自动去除空格以及省略第二次空格\EOLN之后的内容	
		word1 = (word*)malloc(sizeof(word));
		word1->name = str;
		fscanf(fp,"%d",&word1->category);
		all_word[word_index++] = word1;
		str = (char*)malloc(sizeof(char)*20);//每次str要在堆中重新申请空间存入新的word name,否则总是最后一个字符EOF	25
		/*
		printf("%d : ",all_word[word_index-1]->category);
		printf("%s\n",all_word[word_index-1]->name);*/
	}
	fclose(fp);
}
