#include <stdio.h>
#include <stdlib.h>

char str[1024];

/*	convert testfile into string */
void _getStr(char filename[]){
	int index = 0;
	FILE* fp;
	if( (fp = fopen(filename,"r") ) == NULL){
		printf("open test_file fail !!!\n");
		system("pause");
		exit(-1);
	}
	while((str[index++] = getc(fp))!=EOF);
	str[index] = '\0';	/*	Ω·Œ≤±Í÷æ	*/
	fclose(fp);
}
