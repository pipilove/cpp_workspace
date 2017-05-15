#include <string.h>
extern char token[];

/*	全局常量表	*/
char* constTable[256];
int const_full;		//已填常量数

int constant(){
	int const_index = 0;
	while( const_index < const_full && strcmp(constTable[const_index++],token) );
	if( const_index == const_full ){	//未找到常量，填入
		constTable[const_full] = token;
		return const_full++;
	}
	return const_index-1;
}
