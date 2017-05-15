/****************************************************************************/
/*			���ݽṹ���㷨chap2���Ա� - ջ(char)		ƤƤ 2014-8-19			 */
/****************************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

enum status{success, fail, fatal, overflow, underflow};

#define ETYPE char
#define MAX_SIZE 100
typedef struct stack{
	int top;				//ջ��
	int size;				//��ǰջ�Ĵ�С,ջ��Ԫ�ظ���
	ETYPE entry[MAX_SIZE];
}stack, *stackPtr;

/*	ջ��ʼ��(����s�Ƕ�̬����Ŀռ�)	*/
static status stackInit(stackPtr *s){							//�޸�s����s�ĵ�ַ��s����һ��stackPtr���ͱ���
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
	s->size = 0;
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
		s->entry[++(s->top)] = e;
		s->size++;
		outcome = success;
	}
	return outcome;
}

/*	��ջ		*/
static status stackPop(stackPtr s, ETYPE *e){
	status outcome = underflow;
	if( !stackEmpty(s) ){							//�ǿյ�ʱ��Ż��ջ
		*e = s->entry[s->top--];
		s->size--;
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

/*	�������������ַ���	*/
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

/*	���ʽ����ƥ���㷨	*/
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
			if( stackPush(s, c) == overflow )					//�������ž���ջ
				printf("the stack is overflow !!!\n");
			break;

		case ')':
		case ']':
		case '}':
			//if( stackPop(s, &check) == underflow )			//���������ջ�Ƚ�
			if( stackTop(s, &check) == underflow )				//��������ȡ���Ƚ�
				printf("match for bracket %c missed ! \n", c);
			else if( (c == ')' && check != '(') || (c == ']' && check != '[') || (c == '}' && check != '{') )
				printf("brackets %c doesn't match %c, bracket crossed!!\n", c, check);
			else												//������ƥ��ɹ��ų�ջ
				stackPop(s, &check);
			break;
		default:
			//do sth
			break;
		}
	}

	while( stackPop(s, &check) != underflow ){					//��ջ���������ж�������ʾ
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

/*	�б༭����	*/
void lineEdit(){
	stackPtr s;
	stackInit(&s);
	char c = getchar();
	while( c != EOF){
		while( c != EOF && c != '\n' ){
			if( c == '#' )							//&& !stackEmpty(s) )stackPop�д���ջ��Ϊ�ղŻ��ջ
				stackPop(s, &c);
			else if( c == '@' )
				stackClear(s);
			else if( stackPush(s, c) == overflow ){	//�����ַ���ջ
				printf("stack overflow!!!\n");
				exit(0);
			}
			c = getchar();
		}

		for(int i = 0; i < s->size ; i++)			//�����������
			putchar(s->entry[i]);
		printf("\n");

		stackClear(s);
		if( c != EOF )
			c = getchar();
	}
	stackDestroy(&s);
}
