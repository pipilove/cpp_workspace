extern char str[];
extern char character;

int index_str;
/*	从str中读入一个字符	*/
void getChar(){
	character = str[index_str++];
}
