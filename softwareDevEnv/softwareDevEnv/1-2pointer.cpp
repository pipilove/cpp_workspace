/*	ȫ�ֱ���ǿ��ָ��ת��	
int i;

int *pi;
char *pc;
short *ps;

void main(){
	pi = &i;	//0B67140h i�ĵ�ַ����ô�õ��ģ�����
	ps = (short *)&i;	//00B61378 mov dword ptr ds:[00B67138h],0B67140h ������ָ������
	pc = (char *)&i;

	*pi=0x1234;
	*ps=0x1234;
	//mov eax,1234h  mov ecx,dword ptr ds:[01167138h]  mov word ptr [ecx],ax  �ڴ˴�����ָ������
	*pc=0x12;
}
*/