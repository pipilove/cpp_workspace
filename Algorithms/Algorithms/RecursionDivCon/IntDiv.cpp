/****************************************************************************/
/*	算法设计与分析chap2递归与分治策略 —— 整数划分问题		皮皮 2014-8-18		*/
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

/*	整数n划分为m份（n个苹果放入m个盘子中）	*/
int intDivide(int n, int m){
	if(n == 0 || m == 1)
		return 1;
	if(n >= m)
		return intDivide(n - m, m) + intDivide(n, m - 1);//所有盘子都不为空 + 至少一个盘子空
	return intDivide(n, n);
}

int intDivide1(int n, int m){//同书上一样
	if(n == 0 | m == 0)
		return 0;
	if(n == 1 || m == 1)
		return 1;
	if(n > m)
		return intDivide(n - m, m) + intDivide(n, m - 1);
	if(n < m)
		return intDivide(n, n);
	return intDivide(n, m - 1) + 1;
}

/*	整数划分算法设计书上算法	*/
int intDivide2(int n, int m){
	if(n < 1 || m < 1)
		return 0;
	if( n == 1 || m == 1)
		return 1;
	if(n < m)
		return intDivide2(n, n);
	if(n == m)
		return intDivide2(n, m - 1) + 1;
	return intDivide2(n, m - 1) + intDivide2(n - m, m);
}

/* 母函数算法	*/
/*	p(6) = (1+x+x^2+x^3+x^4+x^5+x^6)(1+x^2+x^4+x^6)(1+x^3+x^6)(1+x^4)(1+x^5)(1+x^6)
		 = ...	+ coex^6 + ...
	coe即所要求的划分数
*/

int __156464654main(){
	int round = 20;
	while(--round){		
		srand(time(0));
		int n = rand()%20 + 1;
		printf("n = %d:", n);
		//scanf("%d", &n);
		printf("%d  ", intDivide(n, n));
		printf("%d  ", intDivide1(n, n));
		printf("%d\n", intDivide2(n, n));
		Sleep(1000);
	}
	system("pause");
	return 0;
}
