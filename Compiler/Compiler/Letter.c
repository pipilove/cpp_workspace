extern char character;

/*	�ж���ĸ�ĺ���,���޸�anything		*/
int letter(){
	if(character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z')
		return 1;
	return 0;
}
