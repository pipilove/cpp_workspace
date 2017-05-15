/*	网络编程无法沟通的对齐问题	
#include <stdio.h>

typedef struct{
	short id;
	char c;
	char p;
	short data;
}hdr;

void main(){
	char buf[100];
	short* id;
	char* c;
	short* data;
	id=(short*)&buf[0];
	*id=18;
	data=(short*)&buf[4];
	*data=1234;

	hdr* bufpointer=(hdr*)buf;
	printf("bufpointer->data=%d",bufpointer->data);
}
*/