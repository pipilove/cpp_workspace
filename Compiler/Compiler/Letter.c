extern char character;

/*	ÅĞ¶Ï×ÖÄ¸µÄº¯Êı,²»ĞŞ¸Äanything		*/
int letter(){
	if(character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z')
		return 1;
	return 0;
}
