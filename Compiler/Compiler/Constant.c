#include <string.h>
extern char token[];

/*	ȫ�ֳ�����	*/
char* constTable[256];
int const_full;		//�������

int constant(){
	int const_index = 0;
	while( const_index < const_full && strcmp(constTable[const_index++],token) );
	if( const_index == const_full ){	//δ�ҵ�����������
		constTable[const_full] = token;
		return const_full++;
	}
	return const_index-1;
}
