//****************************************************************************/
//*		算法设计与分析 回溯法 5.3 - 批处理作业调度		皮皮 2014-9-20			*/
//****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <climits>

#define MAX_TASK_NUM 10										//任务数目最大值

static int m[MAX_TASK_NUM][2];								//m[i][j]为任务在机器j上运行的时间
static int best_f = INT_MAX;								//最小的作业调度完成时间
static int best_perm[MAX_TASK_NUM];							//最优作业调度permutation

static void swap(int &x, int &y){
	int tmp = x;
	x = y;
	y = tmp;
}

static void flowShop(int deepth, int* &perm , int n){
	if(deepth >= n){										//每一次都排列出一种排列后计算f并与best_f比较
		int f = m[perm[0]][0] + m[perm[0]][1];				//当前排列下作业调度完成时间
		int f1 = m[perm[0]][0];								//作业进入machine2的时刻，即离开machine1的时刻
		int f2 = f1 + m[perm[0]][1];						//作业在machine2中完成刚离开的时刻

		for(int task_i = 1; task_i < n; task_i++){
			//下一个task进入machine2的时刻为 max(当前task离开machine1的时刻+下一个task在machine1中运行的时间, 当前task在machine2中完成刚离开的时刻）
			f1 = (f2 > m[perm[task_i]][0] + f1 ? f2 : m[perm[task_i]][0] + f1);
			f2 = f1 + m[perm[task_i]][1];
			f += f2;
		}
		if( f < best_f ){
			for(int i = 0; i < n; i++)						//记录最优作业调度permutation
				best_perm[i] = perm[i];
			best_f = f;
		}

	}else{
		for(int i = deepth; i < n; i++){
			swap(perm[deepth], perm[i]);					//搜索排列树标准格式
			flowShop(deepth + 1, perm , n);
			swap(perm[i], perm[deepth]);
		}
	}
}

int __5198464main(){
	assert( freopen("seniorDesign&Analysis\\TraceBack\\FlowShop.in", "r", stdin) );
	int n;													//作业数目<=MAX_TASK_NUM
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d%d", &m[i][0], &m[i][1]);

	int *perm = new int[n];									//初始化作业排列为{ 0, 1 ... n }
	for(int i = 0; i < n; i++)
		perm[i] = i;

	flowShop(0, perm, n);									//深度从0开始

	for(int i = 0; i < n; i++)
		printf("%d ", best_perm[i]);
	printf("\n%d\n", best_f);

	return 0;
}
