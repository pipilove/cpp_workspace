#include "GetWordStruct.h"
#include <stdio.h>

int category;
//int next_category;
int next_next_category;
extern word* all_word[256];
int advance_index;
int line_counter = 1;

/*	ȡ��һ����ƥ�������������category	*/
void advance(){
	//printf("%s\n",all_word[advance_index]->name);
	category = all_word[advance_index++]->category;
	//next_category = all_word[advance_index]->category;
	next_next_category = all_word[advance_index+1]->category;
	if(category == 24){//��ӵ�EOLN�ַ�,�Ѿ���ȡ��һ��
		//printf("%s\n",all_word[advance_index]->name);
		category = all_word[advance_index++]->category;
		//next_category = all_word[advance_index]->category;
		++line_counter;//��¼������1�����ڴ�����
	}
}
