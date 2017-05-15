////*	定义顺序栈	2013.11.20	*/
//#define STACK_SIZE 500
//#define STACK_ELEMENT_TYPE int
//
//typedef struct stack{
//	int top;	//存放栈顶元素的下标，top为-1表示空栈
//	int size;
//	int maxsize;
//	STACK_ELEMENT_TYPE stackElement[STACK_SIZE];
//}stack;

////*	stack manipulate	*/
//#include "Stack.h"
//#include "myDataStructDefine.h"
//
////初始化栈（建立空栈）
//void iniStack(stack s){	//传入s和传入*s有区别么？
//	s.top = -1;
//	s.size = 0;
//	s.maxsize = STACK_SIZE;
//}
//
//int push(stack s,STACK_ELEMENT_TYPE element){
//	if(s.top == s.size){
//		//printf("stack overflow !!!\n");
//		return 0;}
//	s.stackElement[++s.top] = element;
//	s.size++;
//}
//
//int pop(stack s){
//	if(s.top-1 == -1){
//		//printf("stack undweflow !!!\n");
//		return 0;}
//	s.top--;
//	s.size--;
//}
