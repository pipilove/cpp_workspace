/****************************************************************************/
/*		���֮��1.13 - NIM��ʯ������	poj 1067	ƤƤ 2014-9-13				*/
/****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;


/*	����������ȫ���淨 WA?????????? */
static int nim11(int x, int y){	//0 < x, y <= 1,000,000,000
	if( (x==0 && y==0))			//special case
		return 0;
	if(x == y)
		return 1;

	if(x > y){					//swap(x, y) let x < y
		int tmp = y;
		y = x;
		x = tmp;
	}
	int max_n = y - x;
	int bn_max_size = max_n + 1;
	int *bn = (int*)malloc(sizeof(int) * bn_max_size );
	memset(bn, 0, sizeof(int) * bn_max_size);
	int bn_size = 0;				//��ǰbn��Ч����
	bn[bn_size++] = 2;

	int an = 1;
	int inc = 1;					//inc = bn - an
	int low = bn[0];				//��Ч��bn��an�е���Сֵ
	int low_index = 0;

	while(inc < max_n){
		if(++an == low){
			++an;
			low = bn[++low_index];	//an�ѳ���lowҪ�޸�low
		}
		inc++;
		bn[bn_size++] = an + inc;
	}

	if(x != an || y != (an + inc))
		return 1;
	return 0;
}

/*	����������ȫ���������㷨 TLE	*/
bool nim12(int x, int y){
	assert(x>=0);  
	assert(y>=0);  
	if( (x==0 && y==0))
		return 0;

	if( x > y){
		int tmp = y;
		y = x;
		x = tmp;
	}
	int max_n = y - x;
	/*	�� n < an < 2n(��ͼ�ɿ���); n = bn - an	*/
	if ( x < max_n || x > ( max_n << 1) )
		return true;							//win the game!!!

	vector<int> bn(max_n+3);					//bn�����max_n��Ԫ��, +3��ֹlow����Խ��
	bn[1] = 2;
	int n = 2;									//bn - an
	int an = bn[1];
	int *low = &bn[2];							//��¼bn(��Ч��)��an����������Сֵ
	int *high = &bn[n];							//��һ��Ҫ�����bnλ��

	for( ; n <= max_n; ++n){					//an����max_n( y - x )�����ֻҪ���max_n��bn
		if ( ++an == *low){
			++low;
			++an;
		}
		*high++ = an + n;  
	}    

	if (*--high == y)
		return false;  
	return true;  
} 


/*	�ƽ�ָ�����ʽ��	*/
static int nim21(int x, int y){
	if( x > y ){
		int tmp = y;
		y = x;
		x = tmp;
	}
	if(x ==0 && y == 0)
		return 0;
	if(x == y)
		return 1;
	double a = (sqrt(5.0) + 1) / 2;				//goldenNum 1.618...
	int an = 0, n = 0;
	while(x > an){
		n++;
		an = a * n;
	}
	//printf("an = %d\n", an);
	if(x != int(an) || y != int(an) + n)
		return 1;
	return 0;
}

/*	�ƽ�ָ��������㷨	*/
static int nim(int x, int y){
	double a = (sqrt(5.0) + 1) / 2;				//goldenNum 1.618...
	int n = abs(x - y);							//bn - an
	x = x < y? x : y;							//ȡС��
	return ( x != int(a * n) );
}


int __55161main(){
	assert( freopen("BOP\\nim3.in", "r", stdin) );
	int x, y;
	//while(scanf("%d%d", &x, &y) != EOF)		//�ļ���û��output�ȶ���ʱ������
	while(scanf("%d%d", &x, &y) == 2)
		printf("%d\n", nim11(x, y));
	printf("\n");

	assert( freopen("BOP\\nim3.in", "r", stdin) );
	while(scanf("%d%d", &x, &y) == 2)
		printf("%d\n", nim12(x, y));
	printf("\n");

	assert( freopen("BOP\\nim3.in", "r", stdin) );
	while(scanf("%d%d", &x, &y) == 2)
		printf("%d\n", nim21(x, y));
	printf("\n");

	assert( freopen("BOP\\nim3.in", "r", stdin) );
	while(scanf("%d%d", &x, &y) == 2)
		printf("%d\n", nim(x, y));
	printf("\n");

	fclose(stdin);
	return 0;
}
