/*	全局变量强制指针转换	
int i;

int *pi;
char *pc;
short *ps;

void main(){
	pi = &i;	//0B67140h i的地址是怎么得到的？？？
	ps = (short *)&i;	//00B61378 mov dword ptr ds:[00B67138h],0B67140h 不体现指针类型
	pc = (char *)&i;

	*pi=0x1234;
	*ps=0x1234;
	//mov eax,1234h  mov ecx,dword ptr ds:[01167138h]  mov word ptr [ecx],ax  在此处体现指针类型
	*pc=0x12;
}
*/