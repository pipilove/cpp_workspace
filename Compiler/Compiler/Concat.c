extern char token[];
extern char character;
int token_index;

void concat(){
	token[token_index++] = character;
	token[token_index] = '\0';	/*	设置结尾标志	*/
}
