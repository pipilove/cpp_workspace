/****************************************************************************/
/*		POJ����ʼ�9.2 ���� �Ʋ���������2753		ƤƤ 2014-7-10				*/
/****************************************************************************/
#include <stdio.h>

/*	�Ʋ��������еݹ�ʵ��	*/
int fibonacci(int index){
	if( index == 1 || index == 2 )
		return 1;
	return fibonacci(index - 2) + fibonacci(index - 1);
}

/*	�Ʋ��������зǵݹ�ʵ��1	*/
int fibonacci1(int index){					//1 0 1 1 2 3 5 ... (�����1 0��)
	int sum = 0;
	int pre_pre_sum, pre_sum = 1;
	while(index--){
		pre_pre_sum = pre_sum;				//��n-2���ֵ
		pre_sum = sum;						//��n-1���ֵ
		sum = pre_sum + pre_pre_sum;		//��n���ֵ
	}
	return sum;
}

/*	�Ʋ��������зǵݹ�ʵ��2	*/
int fibonacci2(int index){					//-1 1 0 1 1 2 3 5 ... (�����1 0��)
	int pre_pre_sum = -1, pre_sum = 1;
	while(index--){
		pre_sum = pre_sum + pre_pre_sum;	//��n-1���ֵ
		pre_pre_sum = pre_sum - pre_pre_sum;//��n-2���ֵ
	}
	return pre_sum + pre_pre_sum;			//��n���ֵ
}

//int main(){
//	int cases;
//	scanf("%d", &cases);
//	int index;
//	while(cases--){
//		scanf("%d", &index);
//		printf("\n%d\n", fibonacci(index));
//		printf("%d\n", fibonacci1(index));
//		printf("%d\n\n", fibonacci2(index));
//	}
//	return 0;
//}
