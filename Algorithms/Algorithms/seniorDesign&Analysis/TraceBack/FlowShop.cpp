//****************************************************************************/
//*		�㷨�������� ���ݷ� 5.3 - ��������ҵ����		ƤƤ 2014-9-20			*/
//****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <climits>

#define MAX_TASK_NUM 10										//������Ŀ���ֵ

static int m[MAX_TASK_NUM][2];								//m[i][j]Ϊ�����ڻ���j�����е�ʱ��
static int best_f = INT_MAX;								//��С����ҵ�������ʱ��
static int best_perm[MAX_TASK_NUM];							//������ҵ����permutation

static void swap(int &x, int &y){
	int tmp = x;
	x = y;
	y = tmp;
}

static void flowShop(int deepth, int* &perm , int n){
	if(deepth >= n){										//ÿһ�ζ����г�һ�����к����f����best_f�Ƚ�
		int f = m[perm[0]][0] + m[perm[0]][1];				//��ǰ��������ҵ�������ʱ��
		int f1 = m[perm[0]][0];								//��ҵ����machine2��ʱ�̣����뿪machine1��ʱ��
		int f2 = f1 + m[perm[0]][1];						//��ҵ��machine2����ɸ��뿪��ʱ��

		for(int task_i = 1; task_i < n; task_i++){
			//��һ��task����machine2��ʱ��Ϊ max(��ǰtask�뿪machine1��ʱ��+��һ��task��machine1�����е�ʱ��, ��ǰtask��machine2����ɸ��뿪��ʱ�̣�
			f1 = (f2 > m[perm[task_i]][0] + f1 ? f2 : m[perm[task_i]][0] + f1);
			f2 = f1 + m[perm[task_i]][1];
			f += f2;
		}
		if( f < best_f ){
			for(int i = 0; i < n; i++)						//��¼������ҵ����permutation
				best_perm[i] = perm[i];
			best_f = f;
		}

	}else{
		for(int i = deepth; i < n; i++){
			swap(perm[deepth], perm[i]);					//������������׼��ʽ
			flowShop(deepth + 1, perm , n);
			swap(perm[i], perm[deepth]);
		}
	}
}

int __5198464main(){
	assert( freopen("seniorDesign&Analysis\\TraceBack\\FlowShop.in", "r", stdin) );
	int n;													//��ҵ��Ŀ<=MAX_TASK_NUM
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d%d", &m[i][0], &m[i][1]);

	int *perm = new int[n];									//��ʼ����ҵ����Ϊ{ 0, 1 ... n }
	for(int i = 0; i < n; i++)
		perm[i] = i;

	flowShop(0, perm, n);									//��ȴ�0��ʼ

	for(int i = 0; i < n; i++)
		printf("%d ", best_perm[i]);
	printf("\n%d\n", best_f);

	return 0;
}
