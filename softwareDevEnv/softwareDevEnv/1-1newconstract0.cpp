/*
int g;
void main(){
	g=12;
	*(int *)0x00417138=13;	//*0x00417138立即数
	*(int *)0x00007788=(long)&g;
	*(int **)0x00007788=&g;	//&g类型为int *
	//void**长度4，void*长度0
}
*/