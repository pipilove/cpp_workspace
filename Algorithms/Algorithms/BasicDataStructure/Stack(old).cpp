////*	����˳��ջ	2013.11.20	*/
//#define STACK_SIZE 500
//#define STACK_ELEMENT_TYPE int
//
//typedef struct stack{
//	int top;	//���ջ��Ԫ�ص��±꣬topΪ-1��ʾ��ջ
//	int size;
//	int maxsize;
//	STACK_ELEMENT_TYPE stackElement[STACK_SIZE];
//}stack;

////*	stack manipulate	*/
//#include "Stack.h"
//#include "myDataStructDefine.h"
//
////��ʼ��ջ��������ջ��
//void iniStack(stack s){	//����s�ʹ���*s������ô��
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
