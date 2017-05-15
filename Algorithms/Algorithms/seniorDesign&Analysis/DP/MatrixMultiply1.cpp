/****************************************************************************/
/*			�㷨��������3.1 - ��������		ƤƤ 2014-9-14				*/
/****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>

//�������㷨
static void traceback1(int **breakPoints, int i, int j){
	if(i == j){
		printf("A%d", i);
		return;
	}
	int breakPoint = breakPoints[i][j];
	traceback1(breakPoints, i, breakPoint);
	printf(")(");
	traceback1(breakPoints, breakPoint + 1, j);
}

/*	�������Ž�(����򵥵�i==j��������ݹ���ʽ)	*/
static void traceback(int **breakPoints, int i, int j){
	if(i == j)
		printf("A%d", i + 1);
	else{
		int breakPoint = breakPoints[i][j];
		printf("(");
		traceback(breakPoints, i, breakPoint);
		traceback(breakPoints, breakPoint + 1, j);	
		printf(")");
	}
}

static int matrixMultiply(int *p, int n){						//�޸�p[i]���ں��������Ӱ�죡����
	//int m[6][6];
	int **m = (int **)malloc(sizeof(int *) * n);				//m[i][j]����matrix[i][j]�Ӿ���������Сֵ
	for(int i = 0; i < n; i++){
		m[i] = (int *)malloc(sizeof(int) * n);
		for(int j = 0; j < n; j++)
			m[i][j] = INT_MAX;									//��ʼ��Ϊ���ֵ
	}

	for(int i = 0; i < n; i++)									//��������Ϊ1ʱ��min
		m[i][i] = 0;

	//int breakPoints[6][6];
	int **breakPoints = (int **)malloc(sizeof(int *) * n);
	for(int i = 0; i < n; i++)
		breakPoints[i] = (int *)malloc(sizeof(int) * n);

	for(int sub_mat_len = 2; sub_mat_len <= n; sub_mat_len++){	//����
		for(int i = 0; i <= n - sub_mat_len; i++){				//��ͷ
			int j = i + sub_mat_len - 1;						//��β(��ͷ��β�������������У�
			for(int k = i; k <= j - 1; k++){					//k = i, ��kΪA[k]��A[k+1]�Ķϵ�
				int tmp_min = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j + 1];	//!!!
				if(tmp_min < m[i][j]){
					m[i][j] = tmp_min;
					breakPoints[i][j] = k;						//��¼�ϵ�
				}
			}
		}
	}

	traceback(breakPoints, 0, n - 1);
	printf("\n");
	return m[0][n - 1];
}

int __15142151main(){
	assert( freopen("seniorDesign&Analysis\\DP\\MatrixMultiply.in", "r", stdin) );
	int n;
	scanf("%d", &n);
	int *p = (int *)malloc(sizeof(int) * (n + 1));
	for(int i = 0; i <= n + 1; i++)								//A[k] = P[k] * P[k + 1]
		scanf("%d", &p[i]);

	printf("%d\n", matrixMultiply(p, n));
	return 0;
}
