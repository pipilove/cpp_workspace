/*	��һ�޶���ȫ�ֱ���	(ÿ�����̶����Լ�������ҳ��exe�ļ������ض�λ�����Ե�ַ��ͬ�������ַ���Բ�ͬ)
#include <stdio.h>
int gi=12345678;

void main(int argCount,char**args){
	//printf("gi = %d --- &gi = %o\n",gi,&gi);
	if(argCount!=2){printf("please input s to set gi   or   d to display gi ...\n");getchar();return;}
	if(args[1][0]=='s'){
		gi=0x12;
		printf("gi = %d --- &gi = %o\n",gi,&gi);
		getchar();
	}
	else if(args[1][0]=='d'){
		printf("gi = %d --- &gi = %o\n",gi,&gi);
		getchar();
	}
	else
		printf("please input s to set gi   or   d to display gi ...\n");
	getchar();
	return;
}
*/