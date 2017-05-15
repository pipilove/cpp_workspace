/*	构建赋值语句;	void *在64位为8bits	
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int gi;
char buf[10];
char *p;
void main(){
	gi=12;
	buf[0]=0xc7;
	buf[1]=0x05;
	//printf("%s",buf);	//只能放在函数里面运行？
	//memcpy(&buf[2],pi,4);
	*(void**)&buf[2]=&gi;//buf[2]里面装的是gi的地址<=>	*(char**)&buf[2]=(char*)&gi;
	//*(&buf[6])=0x1234;//&buf[6]类型为char*,byte赋值为0x34
	*(int *)(&buf[6])=13;
	//*(int *)0x00417144=13;
	p=buf;
	_asm jmp p	//_asm jmp buf则jmp到地址c705....
	//int *pi;
	//printf("%x",pi);
	system("pause");
}
*/