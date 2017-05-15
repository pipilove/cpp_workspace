#include "GetChar.h"
extern char character;

/*	¶ÁÈë·Ç¿Õ°××Ö·û	*/
void getnbc(){
		getChar();
	while(character == ' ' || character == 9)	//°üÀ¨tab¼ü
		getChar();
}
