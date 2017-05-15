/****************************************************************************/
/*	 	POJ读书笔记9.4 —— 波兰表达式2694		皮皮 2014-7-10				*/
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	波兰表达式非递归算法	*/
double PolNote1(){
	double op_stack[100];
	int stack_top = -1;
	char input[100][10];
	int i = -1;
	do{								//怎么输入换行符结束？？？？？？？？？？？
		scanf("%s", input[++i]);
	}while( strcmp(input[i], "#") );
	i--;

	double a, b;
	while( i >= 0){
		switch(input[i][0]){
		case '+':
			op_stack[stack_top - 1] += op_stack[stack_top];
			stack_top--;
			break;
		case '-':
			op_stack[stack_top - 1] -= op_stack[stack_top];
			stack_top--;
			break;
		case '*':
			op_stack[stack_top - 1] *= op_stack[stack_top];
			stack_top--;
			break;
		case '/':
			op_stack[stack_top - 1] /= op_stack[stack_top];
			stack_top--;
			break;
		default:
			op_stack[++stack_top] = atof(input[i]);
			op_stack[++stack_top] = atof(input[--i]);
		}
		i--;
	}

	return op_stack[stack_top];

}

/*	波兰表达式递归算法	*/
double PolNote(){
	char input[10];
	scanf("%s", input);
	switch(input[0]){					//输入字符串字符是否是运算符
	case '+':
		return PolNote() + PolNote();
	case '-':
		return PolNote() - PolNote();
	case '*':
		return PolNote() * PolNote();
	case '/':
		return PolNote() / PolNote();
	default:
		return atof(input);				//输入字符串数字转换为double
	}
}

int __54846main(){
	printf("%f", PolNote1());
	printf("%f", PolNote());
	return 0;
}
