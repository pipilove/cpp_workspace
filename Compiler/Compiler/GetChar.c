extern char str[];
extern char character;

int index_str;
/*	��str�ж���һ���ַ�	*/
void getChar(){
	character = str[index_str++];
}
