/*	用push和jmp代替call指令
#include <stdio.h>

int minus(int a,int b){
	int ans;
	ans=a-b;
	return ans;
}

int main(){
	int a=2,b=1,k;
	k=minus(a,b);
	void* addr;
	_asm{ 
		push     b  ;
		push     a ;
		mov addr,offset _rb;
		push addr;
		jmp minus;
_rb:
		add    esp,8  ;
		mov    dword ptr [ebp-20h],eax  ;
	}
	printf("%d",k);
	return 0;
}
*/