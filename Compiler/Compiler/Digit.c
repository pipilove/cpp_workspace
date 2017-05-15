extern  char character;

int digit(){
	if(character >= '0' && character <= '9')
		return 1;
	return 0;
}
