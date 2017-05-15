extern char token[];
#include <string.h>

/*	保留字表(也包括运算符、界符表）	*/
char* key_word[23] = {"begin","end","integer","if","then","else","function","read","write"
						,"nop","nop","==","<>","<=","<",">=",">","-","*",":=","(",")",";"};


/*	处理保留字	*/
int reserve(){
	int i = 0;
	while( strcmp(key_word[i],token) && i<=8 )
		i++;
	if(i == 9)
		return 0;	//未找到，不是保留字则返回0
	return i+1;		//找到则返回其类别编码
}
