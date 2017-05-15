/****************************************************************************/
/*	 	POJ����ʼ�9.4 ���� �������ʽ2694		ƤƤ 2014-7-10				*/
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	�������ʽ�ǵݹ��㷨	*/
double PolNote1(){
	double op_stack[100];
	int stack_top = -1;
	char input[100][10];
	int i = -1;
	do{								//��ô���뻻�з���������������������������
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

/*	�������ʽ�ݹ��㷨	*/
double PolNote(){
	char input[10];
	scanf("%s", input);
	switch(input[0]){					//�����ַ����ַ��Ƿ��������
	case '+':
		return PolNote() + PolNote();
	case '-':
		return PolNote() - PolNote();
	case '*':
		return PolNote() * PolNote();
	case '/':
		return PolNote() / PolNote();
	default:
		return atof(input);				//�����ַ�������ת��Ϊdouble
	}
}

int __54846main(){
	printf("%f", PolNote1());
	printf("%f", PolNote());
	return 0;
}
