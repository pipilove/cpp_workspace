/*	º¯ÊıÖ¸Õë	
#include "stdio.h"

typedef int (*funcp)(int,int);

int add(int a,int b){
	int sum=a+b;
	return sum;
}
int main(){
	funcp myfuncp;
	myfuncp=add;	//Í¬&add
	int z=myfuncp(1,2);
	printf("%d",z);
	return 0;
}
*/