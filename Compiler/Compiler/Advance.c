#include "GetWordStruct.h"
#include <stdio.h>

int category;
//int next_category;
int next_next_category;
extern word* all_word[256];
int advance_index;
int line_counter = 1;

/*	取下一个待匹配符号类型送往category	*/
void advance(){
	//printf("%s\n",all_word[advance_index]->name);
	category = all_word[advance_index++]->category;
	//next_category = all_word[advance_index]->category;
	next_next_category = all_word[advance_index+1]->category;
	if(category == 24){//添加的EOLN字符,已经读取了一行
		//printf("%s\n",all_word[advance_index]->name);
		category = all_word[advance_index++]->category;
		//next_category = all_word[advance_index]->category;
		++line_counter;//记录行数加1，用于错误处理
	}
}
