/****************************************************************************/
/*	 	POJ����ʼ�9.5 ���� ��ƻ��1664&�����������		ƤƤ 2014-7-16		*/
/****************************************************************************/
#include <stdio.h>
#include <time.h>

/*	����㷨,��໮��n�ݣ������Ǹպû���n��	*/
static int divide(int m, int n){
	if( m == 0 || n == 1 )						// || m == 1 �ɼӿɲ���
		return 1;
	if(m < n)		
		return divide(m, m);
	/*	m >= nʱ��m���Ϊ<=n�ݣ�������� = �����n�� + �����<n��
	m�ŵ�n�����Ӷ��У���<=>m-n�ŵ�n�����ӣ�m�ŵ�<n�����ӣ���<=>m�ŵ�n-1�����ӵ����	*/
	return divide(m - n, n) + divide(m, n - 1);	
}

/*	��ƻ������	*/
void putApple(){
	int cases;
	scanf("%d", &cases);
	while(cases--){
		int m, n;
		scanf("%d %d", &m, &n);
		printf("%d\n", divide(m, n));
	}
}

/*	�������ֵݹ��㷨1(�ӷ�ƻ����������)		*/
static void integerDivide(){
	int m;
	scanf("%d", &m);
	printf("�㷨1	����%d ���� %d �ֲ�ַ�ʽ\n", m, divide(m, m));
}


/*	��������	*/
static int integerDivide(int num, int max){	//��Ҫ��ֵ�����num, ����ֳ���������max
	if(num == 0 || max == 1)				//num == 0 || max == 1ʱ���ɼ������
		return 1;
	if(num <= max){							//��Ҫ��ֵ���num < ����ֳ�������max,��ֻ�ܴ�num��С�������num
		int count = 0;
		for(int i = num; i >= 1; i--)
			count += integerDivide(num - i, i);
		return count;
	}else{									//��Ҫ��ֵ���num > ����ֳ�������max,�������max��С���num
		int count = 0;
		for(int i = max; i >= 1; i--)
			count += integerDivide(num - i, i);	//ע����num - i!!!
		return count;
	}
}
/*	������ֵݹ��㷨2	(��ȫ<=>��ƻ������)	*/
static void integerDivide2(){
	int m;
	scanf("%d", &m);
	printf("�㷨2	����%d ���� %d �ֲ�ַ�ʽ\n", m, integerDivide(m, m));
}


/*	������ַǵݹ��㷨(ĸ��������)(��������m > n�ķ�ƻ��������)	*/
const int MAXN = 120;
int c1[MAXN+1],c2[MAXN+1];				//c2�����ʾÿһ�ֳ˷���õ�ϵ����c1�����ʾ������Ϊֹ�˷��õ���ϵ���ܺ�
static void integerDivide3(){
	int i,j,k,q;
	for(i=0;i<=MAXN;i++)
		c1[i]=1,c2[i]=0;

	for(i=2;i<=MAXN;i++){				//i��ʾ��i - 1�ֳ˷�x�η��仯������2��ʼ���㣬��һ����������ֳ�i�ĸ�����ĸ�������ʣ�
		for(j=0;j<=MAXN;j++)			//��ǰ*��ߴη���j,Ϊ0 ~ MAXN
			for(k=0;k+j<=MAXN;k+=i)		//�����ұߵĴ���k
				c2[j+k]+=c1[j];			//�η���Ϊj + k��ϵ����1

		for(q=0;q<=MAXN;q++)
			c1[q]=c2[q],c2[q]=0;
	}

	int m;
	scanf("%d", &m);
	printf("�㷨3	����%d ���� %d �ֲ�ַ�ʽ\n", m, c1[m]);
}


int __6598461main(){
	//��ƻ���������
	//putApple();

	//������ֲ���
	while(1){
		int start = clock();
		integerDivide();
		printf("�㷨1��ʱ%d\n\n", clock() - start);//23000(input 100)
		start = clock();
		integerDivide2();
		printf("�㷨2��ʱ%d\n\n", clock() - start);//23000
		start = clock();
		integerDivide3();
		printf("�㷨3��ʱ%d\n\n", clock() - start);//3000
	}
	return 0;
}
