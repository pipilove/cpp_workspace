/*	独一无二的全局变量	(每个进程都有自己独立的页表，exe文件不会重定位，线性地址相同但物理地址可以不同)
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