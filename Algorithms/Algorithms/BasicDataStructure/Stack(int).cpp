/****************************************************************************/
/*			数据结构与算法chap2线性表 - 栈(int)		皮皮 2014-8-20		  */
/****************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

enum status{success, fail, fatal, overflow, underflow};

#define ETYPE int
#define MAX_SIZE 5
typedef struct stack{
	int top;
	ETYPE entry[MAX_SIZE];
}stack, *stackPtr;

/*	栈初始化(对于s是动态分配的空间)	*/
static status stackInit(stackPtr *s){							//修改s则传入s的地址，s又是一个stackPtr类型变量
	status outcome = fatal;
	stack *p = (stack*)malloc(sizeof(stack));
	if( p ){
		p->top = -1;
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
		s->entry[++s->top] = e;
		outcome = success;
	}
	return outcome;
}

/*	出栈		*/
static status stackPop(stackPtr s, ETYPE *e){
	status outcome = underflow;
	if( !stackEmpty(s) ){
		*e = s->entry[s->top--];
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


static void aryConverse();
#define OPND_TYPE int
static void evaluateExp();

int __286465main(){
	while(0){
		//aryConverse();
		printf("last test ends!!!\n");
	}
	evaluateExp();/*
	char c = getchar();
	while( c != EOF && c != '\n' ){
		c = getchar();
		printf("%c", c);
	}
*/
	system("pause");
	return 0;
}


/*	数制转换(十进制转换为其他进制)	*/
void aryConverse(){
	int dec;
	int r;
	scanf("%d%d", &dec, &r);

	stackPtr s;
	stackInit(&s);

	do{
		stackPush(s, dec % r);
	}while( dec /= r );

	while( stackPop(s, &r) != underflow )
		printf("%d", r);
	printf("\n");

	stackDestroy(&s);
}

/*	表达式求值	*/
static char optrs[] = {'+', '-', '*', '/', '(', ')', '#'};
/*	判断是否是运算符	*/
bool isoptr(char c){
	int optrs_len = sizeof(optrs) / sizeof(optrs[0]);
	for( int i = 0; i < optrs_len; i++)
		if(c == optrs[i])
			return true;
	return false;
	//return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')') || (c == '#');
}
/*	运算符优先级比较	*/
char optrCompare(char c1, char c2){
	switch(c1){
	case '+':
	case '-':
		if( c2 == '*' || c2 == '/' || c2 == '(')
			return '<';
		return '>';
	case '*':
	case '/':
		if( c2 == '(' )
			return '<';
		return '>';
	case '(':
		if( c2 == ')' )
			return '=';
		else if( c2 == '#'){
			printf("grammer error !!! \n");
			system("pause");
			exit(0);
		}
		return '<';
	case ')':
		if( c2 == '('){
			printf("grammer error !!! \n");
			system("pause");
			exit(0);
		}
		return '>';
	case '#':
		//if( c2 == '#' )					//应该不能比较
		//return '=';
		//else 
		if( c2 == ')'){
			printf("grammer error !!! \n");
			system("pause");
			exit(0);
		}
		return '<';
	}
}
//char t[][7]={
//	{'>','>','<','<','<','>','>'},
//	{'>','>','<','<','<','>','>'},
//	{'>','>','>','>','<','>','>'},
//	{'>','>','>','>','<','>','>'},
//	{'<','<','<','<','<','=',0},
//	{'>','>','>','>',0,'>','>'},
//	{'<','<','<','<','<',0,'='}    
//};														//<=>optrCompare()
//char  precede(char a,char b){	
//	return t[opt[a]][opt[b]];
//}

/*	二元运算a θ b的函数	*/
OPND_TYPE operate( OPND_TYPE a, char optr, OPND_TYPE b){
	switch(optr){
	case '+':	return a + b;
	case '-':	return a - b;
	case '*':	return a * b;
	case '/':	return a / b;
	}
	throw "no this operation:" + optr;
}

void evaluateExp(){	
	if( !freopen("BasicDataStructure\\stack_eva_exp.txt", "r", stdin) ){	//test for evaluateExp()
		printf("open test file fail!!!\n");
		system("pause");									//暂停不住，stdin有内容？？？？
		exit(0);
	}
	while(1){
		stackPtr opnd;
		stackInit(&opnd);

		stackPtr optr;
		stackInit(&optr);
		stackPush(optr, '#');

		ETYPE topOptr;
		stackTop(optr, &topOptr);
		ETYPE c = getchar();
		char opnd_char[4];

		while( c != '#' || topOptr != '#' ){
			int i = 0;	//数字处理部分
			memset(opnd_char, 0, sizeof(opnd_char) );				//opnd_char清0
			while( !isoptr(c) ){									//不是运算符则入栈opnd
				if( c == 'e' ){	//输入结束							//结束行计算标志'e'，程序结构不好？？？
					stackDestroy(&opnd);
					stackDestroy(&optr);
					fflush(stdin);									//不能清除缓冲区???
					fclose(stdin);									//关闭文件
					return;
				}
				opnd_char[i++] = c;
				c = getchar();
			}
			if( opnd_char[0] != NULL ){
				ETYPE opnd_c = atoi(opnd_char);
				stackPush(opnd, opnd_c);		
			}else{		//运算符处理部分
				stackTop(optr, &topOptr);
				switch( optrCompare(topOptr, c) ){
				case '<':											//topOptr优先级低则不能计算，新的c入栈
					stackPush(optr, c);
					c = getchar();
					break;
				case '=':											//topOptr = ( && c == )时脱括号
					stackPop(optr, &c);
					c = getchar();
					break;
				case '>':
					OPND_TYPE opnd1, opnd2;
					stackPop(opnd, &opnd2);							//取出第一个操作数（顺序不能反）
					stackPop(opnd, &opnd1);							//取出第二个操作数
					ETYPE theta;
					stackPop(optr, &theta);							//取运算符
					stackPush(opnd, operate(opnd1, theta, opnd2));	//计算两个操作数的值并压栈保存
					break;
				}
				stackTop(optr, &topOptr);							//取可能新的栈顶元素
			}
		}

		ETYPE res;													//每一行结束计算输出结果
		stackTop(opnd, &res);
		printf("%d\n", res);
	}
}
