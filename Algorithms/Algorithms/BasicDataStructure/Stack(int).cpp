/****************************************************************************/
/*			���ݽṹ���㷨chap2���Ա� - ջ(int)		ƤƤ 2014-8-20		  */
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

/*	ջ��ʼ��(����s�Ƕ�̬����Ŀռ�)	*/
static status stackInit(stackPtr *s){							//�޸�s����s�ĵ�ַ��s����һ��stackPtr���ͱ���
	status outcome = fatal;
	stack *p = (stack*)malloc(sizeof(stack));
	if( p ){
		p->top = -1;
		*s = p;
		outcome = success;
	}
	return outcome;
}

/*	ջ����	*/
static void stackDestroy(stackPtr *s){							//���s����Ҫ��stackPtr *
	if( *s ){
		free(*s);
		*s = NULL;
	}
}

/*	ջ���	*/
static void stackClear(stackPtr s){								//�޸�s�Ĳ���������stack *
	//if( s )
	s->top = -1;
}
//void stackClear(stackPtr *s){
//		(*s)->top = -1;
//}

/*	ջ�п�	*/
static bool stackEmpty(stackPtr s){
	return ( s->top <= -1 );
}

/* ջ����	*/
static bool stackFull(stackPtr s){
	return ( s->top >= MAX_SIZE - 1 );
}

/*	��ջ		*/
static status stackPush(stackPtr s, ETYPE e){
	status outcome = overflow;
	if( !stackFull(s) ){
		s->entry[++s->top] = e;
		outcome = success;
	}
	return outcome;
}

/*	��ջ		*/
static status stackPop(stackPtr s, ETYPE *e){
	status outcome = underflow;
	if( !stackEmpty(s) ){
		*e = s->entry[s->top--];
		outcome = success;
	}
	return outcome;
}

/*	ȡջ��Ԫ��	*/
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


/*	����ת��(ʮ����ת��Ϊ��������)	*/
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

/*	���ʽ��ֵ	*/
static char optrs[] = {'+', '-', '*', '/', '(', ')', '#'};
/*	�ж��Ƿ��������	*/
bool isoptr(char c){
	int optrs_len = sizeof(optrs) / sizeof(optrs[0]);
	for( int i = 0; i < optrs_len; i++)
		if(c == optrs[i])
			return true;
	return false;
	//return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')') || (c == '#');
}
/*	��������ȼ��Ƚ�	*/
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
		//if( c2 == '#' )					//Ӧ�ò��ܱȽ�
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

/*	��Ԫ����a �� b�ĺ���	*/
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
		system("pause");									//��ͣ��ס��stdin�����ݣ�������
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
			int i = 0;	//���ִ�����
			memset(opnd_char, 0, sizeof(opnd_char) );				//opnd_char��0
			while( !isoptr(c) ){									//�������������ջopnd
				if( c == 'e' ){	//�������							//�����м����־'e'������ṹ���ã�����
					stackDestroy(&opnd);
					stackDestroy(&optr);
					fflush(stdin);									//�������������???
					fclose(stdin);									//�ر��ļ�
					return;
				}
				opnd_char[i++] = c;
				c = getchar();
			}
			if( opnd_char[0] != NULL ){
				ETYPE opnd_c = atoi(opnd_char);
				stackPush(opnd, opnd_c);		
			}else{		//�����������
				stackTop(optr, &topOptr);
				switch( optrCompare(topOptr, c) ){
				case '<':											//topOptr���ȼ������ܼ��㣬�µ�c��ջ
					stackPush(optr, c);
					c = getchar();
					break;
				case '=':											//topOptr = ( && c == )ʱ������
					stackPop(optr, &c);
					c = getchar();
					break;
				case '>':
					OPND_TYPE opnd1, opnd2;
					stackPop(opnd, &opnd2);							//ȡ����һ����������˳���ܷ���
					stackPop(opnd, &opnd1);							//ȡ���ڶ���������
					ETYPE theta;
					stackPop(optr, &theta);							//ȡ�����
					stackPush(opnd, operate(opnd1, theta, opnd2));	//����������������ֵ��ѹջ����
					break;
				}
				stackTop(optr, &topOptr);							//ȡ�����µ�ջ��Ԫ��
			}
		}

		ETYPE res;													//ÿһ�н�������������
		stackTop(opnd, &res);
		printf("%d\n", res);
	}
}
