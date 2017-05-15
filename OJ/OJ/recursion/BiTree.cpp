/****************************************************************************/
/*		POJ����ʼ�9.3 ���� ������2756		ƤƤ 2014-7-10					*/
/****************************************************************************/
#include <stdio.h>
#include <math.h>

void biTree(){
	int x, y;
	scanf("%d %d", &x, &y);
	int max, min;
	if( x > y){
		max = x;
		min = y;
	}else{
		max = y;
		min = x;
	}

	int delta_k = log((double)min) / log((double)2) + 1;
	int min_pow = pow((double)2, delta_k);					//min��2�η�����
	while( max >= min_pow )
		max /= 2;											//min max��ͬһ2��n ~ n-1�η���Χ��
	while( max != min ){
		max /= 2;
		min /= 2;
	}

	printf("%d\n", max);
}

/* ����������㷨	*/
void biTree1(){
	int x, y;
	scanf("%d %d", &x, &y);
	while( x != y){
		if( x > y)
			x /= 2;
		else
			y /= 2;
	}
	printf("%d\n", x);
}

/*	�������ݹ��㷨	*/
static int common(int x, int y){
	if( x > y)
		return common(x/2, y);
	else if(x < y)
		return common(x, y/2);
	else
		return x;
}
void recBiTree(){
	int x, y;
	scanf("%d %d", &x, &y);
	printf("%d\n", common(x,y) );
}

int __5468main(){
	//biTree();
	//biTree1();
	recBiTree();
	return 0;
}
