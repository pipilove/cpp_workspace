/****************************************************************************/
/*	 	POJ读书笔记9.5 —— 放苹果1664&整数拆分问题		皮皮 2014-7-16		*/
/****************************************************************************/
#include <stdio.h>
#include <time.h>

/*	拆分算法,最多划分n份，而不是刚好划分n份	*/
static int divide(int m, int n){
	if( m == 0 || n == 1 )						// || m == 1 可加可不加
		return 1;
	if(m < n)		
		return divide(m, m);
	/*	m >= n时，m拆分为<=n份，则拆分情况 = 拆分了n份 + 拆分了<n份
	m放到n个盒子都有，则<=>m-n放到n个盒子；m放到<n个盒子，则<=>m放到n-1个盒子的情况	*/
	return divide(m - n, n) + divide(m, n - 1);	
}

/*	放苹果问题	*/
void putApple(){
	int cases;
	scanf("%d", &cases);
	while(cases--){
		int m, n;
		scanf("%d %d", &m, &n);
		printf("%d\n", divide(m, n));
	}
}

/*	整数划分递归算法1(从放苹果问题引出)		*/
static void integerDivide(){
	int m;
	scanf("%d", &m);
	printf("算法1	整数%d 共有 %d 种拆分方式\n", m, divide(m, m));
}


/*	整数划分	*/
static int integerDivide(int num, int max){	//需要拆分的数是num, 最大拆分出来的数是max
	if(num == 0 || max == 1)				//num == 0 || max == 1时不可继续拆分
		return 1;
	if(num <= max){							//需要拆分的数num < 最大拆分出来的数max,则只能从num大小继续拆分num
		int count = 0;
		for(int i = num; i >= 1; i--)
			count += integerDivide(num - i, i);
		return count;
	}else{									//需要拆分的数num > 最大拆分出来的数max,则继续从max大小拆分num
		int count = 0;
		for(int i = max; i >= 1; i--)
			count += integerDivide(num - i, i);	//注意是num - i!!!
		return count;
	}
}
/*	整数拆分递归算法2	(完全<=>放苹果问题)	*/
static void integerDivide2(){
	int m;
	scanf("%d", &m);
	printf("算法2	整数%d 共有 %d 种拆分方式\n", m, integerDivide(m, m));
}


/*	整数拆分非递归算法(母函数方法)(不能用于m > n的放苹果问题中)	*/
const int MAXN = 120;
int c1[MAXN+1],c2[MAXN+1];				//c2数组表示每一轮乘法后得到系数，c1数组表示到现在为止乘法得到的系数总和
static void integerDivide3(){
	int i,j,k,q;
	for(i=0;i<=MAXN;i++)
		c1[i]=1,c2[i]=0;

	for(i=2;i<=MAXN;i++){				//i表示第i - 1轮乘法x次方变化数（从2开始计算，第一个），即拆分成i的个数（母函数性质）
		for(j=0;j<=MAXN;j++)			//当前*左边次方数j,为0 ~ MAXN
			for(k=0;k+j<=MAXN;k+=i)		//乘上右边的次数k
				c2[j+k]+=c1[j];			//次方数为j + k的系数加1

		for(q=0;q<=MAXN;q++)
			c1[q]=c2[q],c2[q]=0;
	}

	int m;
	scanf("%d", &m);
	printf("算法3	整数%d 共有 %d 种拆分方式\n", m, c1[m]);
}


int __6598461main(){
	//放苹果问题测试
	//putApple();

	//整数拆分测试
	while(1){
		int start = clock();
		integerDivide();
		printf("算法1用时%d\n\n", clock() - start);//23000(input 100)
		start = clock();
		integerDivide2();
		printf("算法2用时%d\n\n", clock() - start);//23000
		start = clock();
		integerDivide3();
		printf("算法3用时%d\n\n", clock() - start);//3000
	}
	return 0;
}
