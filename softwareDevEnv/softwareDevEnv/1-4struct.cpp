/*	结构体	
&p.age和(void *)(ebp-0ch)验证age位置	
探究结构体在内存中的特性：项目属性-配置属性-c++-优化-优化-禁用；改为release版本???	

#include "stdio.h" 

struct Person{
	int age;
	int no;	//	比age先压栈
};

void main(){
	Person p;
	p.age=1;
	p.no=2;
	printf("%x",&p.age);
}
*/