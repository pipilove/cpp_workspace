#include <stdio.h>
#include <stdlib.h>
#include "GetWordStruct.h"

word* all_word[256];
int word_index;

/*	��file�л�ȡ����	*/
void getWord(){
	FILE* fp;
	word* word1;
	char* str = (char*)malloc(sizeof(char)*20);
	if( (fp = fopen("testFun.dyd","r")) == NULL){
		printf("testFun.dyd file open fail !!!\n");
		system("pause");
		exit(-1);
	}
	while( (fscanf(fp,"%s",str)) == 1){	//�Զ�ȥ���ո��Լ�ʡ�Եڶ��οո�\EOLN֮�������	
		word1 = (word*)malloc(sizeof(word));
		word1->name = str;
		fscanf(fp,"%d",&word1->category);
		all_word[word_index++] = word1;
		str = (char*)malloc(sizeof(char)*20);//ÿ��strҪ�ڶ�����������ռ�����µ�word name,�����������һ���ַ�EOF	25
		/*
		printf("%d : ",all_word[word_index-1]->category);
		printf("%s\n",all_word[word_index-1]->name);*/
	}
	fclose(fp);
}
