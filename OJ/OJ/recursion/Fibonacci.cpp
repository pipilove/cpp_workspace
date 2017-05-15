/****************************************************************************/
/*		POJ读书笔记9.2 —— 菲波那契数列2753		皮皮 2014-7-10				*/
/****************************************************************************/
#include <stdio.h>

/*	菲波那契数列递归实现	*/
int fibonacci(int index){
	if( index == 1 || index == 2 )
		return 1;
	return fibonacci(index - 2) + fibonacci(index - 1);
}

/*	菲波那契数列非递归实现1	*/
int fibonacci1(int index){					//1 0 1 1 2 3 5 ... (添加了1 0项)
	int sum = 0;
	int pre_pre_sum, pre_sum = 1;
	while(index--){
		pre_pre_sum = pre_sum;				//第n-2项的值
		pre_sum = sum;						//第n-1项的值
		sum = pre_sum + pre_pre_sum;		//第n项的值
	}
	return sum;
}

/*	菲波那契数列非递归实现2	*/
int fibonacci2(int index){					//-1 1 0 1 1 2 3 5 ... (添加了1 0项)
	int pre_pre_sum = -1, pre_sum = 1;
	while(index--){
		pre_sum = pre_sum + pre_pre_sum;	//第n-1项的值
		pre_pre_sum = pre_sum - pre_pre_sum;//第n-2项的值
	}
	return pre_sum + pre_pre_sum;			//第n项的值
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
