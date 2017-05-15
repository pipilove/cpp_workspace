#include <string.h>
extern char token[];

/*	全局符号表	*/
char* symbolTable[256];
int symbol_full;		//已填符号数

/*	查符号表	*/
int symbol(){
	int symbol_index = 0;
	while( symbol_index<symbol_full && strcmp(symbolTable[symbol_index++],token) );
	if(symbol_index == symbol_full){	//未找到标志符，填入
		symbolTable[symbol_full] = token;
		return symbol_full++;			//返回symbol_full后再++修改symbol_full
	}
	return symbol_index-1;
}
