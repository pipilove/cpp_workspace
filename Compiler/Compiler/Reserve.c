extern char token[];
#include <string.h>

/*	�����ֱ�(Ҳ����������������	*/
char* key_word[23] = {"begin","end","integer","if","then","else","function","read","write"
						,"nop","nop","==","<>","<=","<",">=",">","-","*",":=","(",")",";"};


/*	��������	*/
int reserve(){
	int i = 0;
	while( strcmp(key_word[i],token) && i<=8 )
		i++;
	if(i == 9)
		return 0;	//δ�ҵ������Ǳ������򷵻�0
	return i+1;		//�ҵ��򷵻���������
}
