#include <string.h>
extern char token[];

/*	ȫ�ַ��ű�	*/
char* symbolTable[256];
int symbol_full;		//���������

/*	����ű�	*/
int symbol(){
	int symbol_index = 0;
	while( symbol_index<symbol_full && strcmp(symbolTable[symbol_index++],token) );
	if(symbol_index == symbol_full){	//δ�ҵ���־��������
		symbolTable[symbol_full] = token;
		return symbol_full++;			//����symbol_full����++�޸�symbol_full
	}
	return symbol_index-1;
}
