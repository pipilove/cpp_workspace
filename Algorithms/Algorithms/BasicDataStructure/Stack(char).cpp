/****************************************************************************/
/*			数据结构与算法chap2线性表 - 栈(char)		皮皮 2014-8-19			 */
/****************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

enum status{success, fail, fatal, overflow, underflow};

#define ETYPE char
#define MAX_SIZE 100
typedef struct stack{
	int top;				//栈顶
	int size;				//当前栈的大小,栈中元素个数
	ETYPE entry[MAX_SIZE];
}stack, *stackPtr;

/*	栈初始化(对于s是动态分配的空间)	*/
static status stackInit(stackPtr *s){							//修改s则传入s的地址，s又是一个stackPtr类型变量
	status outcome = fatal;
	stack *p = (stack*)malloc(sizeof(stack));
	if( p ){
		p->top = -1;
		p->size = 0;
		*s = p;
		outcome = success;
	}
	return outcome;
}

/*	栈销毁	*/
static void stackDestroy(stackPtr *s){							//清除s本身要用stackPtr *
	if( *s ){
		free(*s);
		*s = NULL;
	}
}

/*	栈清空	*/
static void stackClear(stackPtr s){								//修改s的部分内容用stack *
	//if( s )
	s->top = -1;
	s->size = 0;
}
//void stackClear(stackPtr *s){
//		(*s)->top = -1;
//}

/*	栈判空	*/
static bool stackEmpty(stackPtr s){
	return ( s->top <= -1 );
}

/* 栈判满	*/
static bool stackFull(stackPtr s){
	return ( s->top >= MAX_SIZE - 1 );
}

/*	入栈		*/
static status stackPush(stackPtr s, ETYPE e){
	status outcome = overflow;
	if( !stackFull(s) ){
		s->entry[++(s->top)] = e;
		s->size++;
		outcome = success;
	}
	return outcome;
}

/*	出栈		*/
static status stackPop(stackPtr s, ETYPE *e){
	status outcome = underflow;
	if( !stackEmpty(s) ){							//非空的时候才会出栈
		*e = s->entry[s->top--];
		s->size--;
		outcome = success;
	}
	return outcome;
}

/*	取栈顶元素	*/
static status stackTop(stackPtr s, ETYPE *e){	
	status outcome = underflow;
	if( !stackEmpty(s) ){
		*e = s->entry[s->top];
		outcome = success;
	}
	return outcome;
}


static void inputReverse();
static void bracketCheck();
static void aryConverse();
static void lineEdit();

int __5main(){
	while(1){
		//inputReverse();
		//bracketCheck();						//test cases:	{a * d + c) - ki]  {({a * d + c) - k[i] }
		//lineEdit();							//test cases:	whli##ilr#e(s#*s)
		//					outcha@putchar(*s=#++);

		printf("last test ends!!!\n");
	}

	system("pause");
	return 0;
}

/*	逆序输出输入的字符串	*/
void inputReverse(){	
	stack *s;
	if( stackInit(&s) == fatal )
		exit(0);

	char c;
	while( (c = getchar()) != '\n' ){
		if( stackFull(s) ){
			printf("stack overflow !!! \n");
			break;
		}
		stackPush(s, c);
	}
	while( !stackEmpty(s) ){
		stackPop(s, &c);
		putchar(c);
	}

	stackDestroy(&s);
	printf("\n");
}

/*	表达式括号匹配算法	*/
void bracketCheck(){
	char c;
	char check;
	stackPtr s;
	stackInit(&s);

	while(	(c = getchar()) != '\n' ){
		switch( c ){
		case '(':
		case '[':
		case '{':
			if( stackPush(s, c) == overflow )					//是左括号就入栈
				printf("the stack is overflow !!!\n");
			break;

		case ')':
		case ']':
		case '}':
			//if( stackPop(s, &check) == underflow )			//右括号则出栈比较
			if( stackTop(s, &check) == underflow )				//右括号则取出比较
				printf("match for bracket %c missed ! \n", c);
			else if( (c == ')' && check != '(') || (c == ']' && check != '[') || (c == '}' && check != '{') )
				printf("brackets %c doesn't match %c, bracket crossed!!\n", c, check);
			else												//右括号匹配成功才出栈
				stackPop(s, &check);
			break;
		default:
			//do sth
			break;
		}
	}

	while( stackPop(s, &check) != underflow ){					//入栈的左括号有多余则提示
		switch(check){
		case '(':
		case '[':
		case '{':
			printf("bracket %c is more than its match \n", check);
			break;
		}
	}

	stackDestroy(&s);
}

/*	行编辑程序	*/
void lineEdit(){
	stackPtr s;
	stackInit(&s);
	char c = getchar();
	while( c != EOF){
		while( c != EOF && c != '\n' ){
			if( c == '#' )							//&& !stackEmpty(s) )stackPop中处理，栈不为空才会出栈
				stackPop(s, &c);
			else if( c == '@' )
				stackClear(s);
			else if( stackPush(s, c) == overflow ){	//其他字符入栈
				printf("stack overflow!!!\n");
				exit(0);
			}
			c = getchar();
		}

		for(int i = 0; i < s->size ; i++)			//输出到缓冲区
			putchar(s->entry[i]);
		printf("\n");

		stackClear(s);
		if( c != EOF )
			c = getchar();
	}
	stackDestroy(&s);
}
