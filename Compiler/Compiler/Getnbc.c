#include "GetChar.h"
extern char character;

/*	����ǿհ��ַ�	*/
void getnbc(){
		getChar();
	while(character == ' ' || character == 9)	//����tab��
		getChar();
}
