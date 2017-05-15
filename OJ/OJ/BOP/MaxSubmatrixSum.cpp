//***************************************************************************************/
//*		���֮��2.15 ���� ���ά��������Ԫ��֮������Ӿ���\poj 1050		ƤƤ 2014-9-4	*/
//***************************************************************************************/
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>

/*	ֱ��ö�ٷ�O( N^2*M^2*O��sum()) )	Time Limit Exceeded	*/
static int submatrixSum(int **a, int row, int row_end, int col, int col_end){
	int sum = 0;
	for(int i = row; i <= row_end; i++)
		for(int j = col; j <= col_end; j++)
			sum += a[i][j];
	return sum;
}
static int maxSubmatrixSum1(int **a, int n){
	int max_sum = INT_MIN;
	int sum;
	int max_row, max_row_end, max_col, max_col_end;
	for(int row = 0; row < n; row++){
		for(int col = 0; col < n; col++){								//�Ӿ������Ͻ�λ��
			for(int row_end = row; row_end < n; row_end++)
				for(int col_end = col; col_end < n; col_end++){			//4������ȷ��һ���Ӿ���
					sum = submatrixSum(a, row, row_end, col, col_end);	//����ÿ���Ӿ���ĺ�
					if(sum > max_sum){
						max_sum = sum;
						/*max_row = row;
						max_row_end = row_end;
						max_col = col;
						max_col_end = col_end;*/
						//printf("%d\n", max_sum);
					}
				}
		}
	}
	/*printf("\n            col\tcol_end\n            %d\t%d\n", max_col, max_col_end);		//����Ӿ���λ�ã�4�����ԣ�
	printf("row     %d\nrow_end %d\n", max_row, max_row_end);*/
	return max_sum;
}

/*	DP�㷨 O(N^2*M)	AC 47MS*/
static int maxSubmatrixSum2(int **a, int n){
	int ***row_sum;
	assert( row_sum = (int ***)malloc(sizeof(int **) * n) );
	for(int i = 0; i < n; i++)
		assert( row_sum[i] = (int **)malloc(sizeof(int *) * n) );
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			assert( row_sum[i][j] = (int *)malloc(sizeof(int) * n) );
			memset(row_sum[i][j], 0, sizeof(int) * n);				//��ʼ��row_sum[i][j][c]Ϊ0!!!
		}

		//����row_sum[i][j][c]Ϊ��i��j�е�c�еĺ�
		for(int i = n - 1; i >= 0; i--){
			for(int j = 0; j < n; j++){
				for(int c = j; c < n; c++)
					if(c == 0)
						row_sum[i][j][c] = a[i][c];
					else
						row_sum[i][j][c] = row_sum[i][j][c - 1] + a[i][c];
			}
		}

		//��row_sum[i][j][c]ת���ɵ�i��j�е�c�еĺ͵����Ž�
		for(int i = n - 2; i >= 0; i--){								//row_sum[n-1][j][c]����
			for(int j = 0; j < n; j++)
				for(int c = j; c < n; c++){
					if(row_sum[i+1][j][c] > 0)
						row_sum[i][j][c] += row_sum[i+1][j][c];
				}
		}

		//����[i, j]Ϊ���Ͻǵľ������Ž�
		int **optij = (int **)malloc(sizeof(int *) * n);
		for(int i = 0; i < n; i++)
			optij[i] = (int *)malloc(sizeof(int) * n);
		for(int i = 0; i < n; i++)
			memset(optij[i], INT_MIN, sizeof(int) * n);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++)
				for(int c = j; c < n; c++){
					if(row_sum[i][j][c] > optij[j][j])
						optij[j][j] = row_sum[i][j][c];
				}
		}

		//���������Ž�
		int max_sum = INT_MIN;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(optij[i][j] > max_sum)
					max_sum = optij[i][j];
			}
		}

		return max_sum;
}

/*	�����㷨	AC 63MS */
static int maxSubmatrixSum(int **a, int n){
	//��ʼ��col_sum, col_sum[i][j][k]Ϊ��i��j��֮���k��Ԫ�صĺ�
	int *** col_sum;
	assert( col_sum = (int ***)malloc(sizeof(int **) * n) );
	for(int i = 0; i < n; i++)
		assert( col_sum[i] = (int **)malloc(sizeof(int *) * n) );
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			assert( col_sum[i][j] = (int *)malloc(sizeof(int) * n) );
			memset(col_sum[i][j], 0, sizeof(int) * n);
		}
	}

	//�����0��j(>=1)��֮���k�еĺ�
	for(int k = 0; k < n; k++){	
		col_sum[0][0][k] = a[0][k];								//��ʼ��col_sum[0][0][k]Ϊ��������
		for(int j = 1; j < n; j++)
			col_sum[0][j][k] = col_sum[0][j - 1][k] + a[j][k];	//!!!
	}
	//�����i��j��֮���k�еĺ�
	for(int k = 0; k < n; k++){
		for(int i = 1; i < n; i++)
			for(int j = i; j < n; j++)
				col_sum[i][j][k] = col_sum[i - 1][j][k] - a[i - 1][k];
	}

	//��������Ӿ����
	int max_mat_sum = INT_MIN;
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			int row_sum = 0;									//��i��j��֮�������array�ͣ�ѹ������
			for(int k = 0; k < n; k++){
				row_sum += col_sum[i][j][k];
				if(row_sum < 0)
					row_sum = 0;
				if(row_sum > max_mat_sum)
					max_mat_sum = row_sum;
			}
		}
	}

	return max_mat_sum;
}

int __156165main(){
	assert( freopen("BOP\\maxSubmatrixSum.in", "r", stdin) );
	//int cases;													//���԰�����Ŀ
	//scanf("%d", &cases);
	//while(cases--){
		int n;														//ÿ��������matrixά��
		scanf("%d", &n);
		int **a = (int **)malloc(sizeof(int*) * n);
		for(int i = 0; i < n; i++)
			a[i] = (int *)malloc(sizeof(int) * n);

		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				scanf("%d", &a[i][j]);

		//printf("%d\n", maxSubmatrixSum1(a, n) );
		//printf("%d\n", maxSubmatrixSum2(a, n) );
		printf("%d\n", maxSubmatrixSum(a, n) );
	/*}*/
	fclose(stdin);
	return 0;
}
