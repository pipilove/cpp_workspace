/****************************************************************************/
/*			POJ读书笔记6.1 - 约瑟夫问题 2746		皮皮 2014-9-14				*/
/****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*	数组算法(有删除元素)	O(mn)	*/
static int jonseArray(int n, int m) {
	int *jones = new int[n];
	for(int i=0; i<n; i++)
		jones[i]=i+1;
	int t=0;
	for(int left=n; left>=1; left--) {			//剩余人数
		t=(t+m-1)%left;							//将要除去的编号
		//printf("%d ", jones[t]);
		for(int j=t+1; j<=left-1; j++)
			jones[j-1]=jones[j];
	}
	return jones[0];
}

/*	数组算法(无删除元素)	O(mn)	*/
static int jonseArray2(int n, int m){
	int *a = (int *)malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++)
		a[i] = 1;

	int current = 0;
	for(int lose_cnt = 0; lose_cnt < n - 1; lose_cnt++){
		int call_num = 1;										//重新报数
		while(call_num < m){
			current = (current + 1) % n;
			while(a[current] == 0)								//跳过已划出的
				current = (current + 1) % n;
			call_num++;
		}
		a[current] = 0;											//划出一个
		current = (current + 1) % n;							//current指向下一个
		while(a[current] == 0)
			current = (current + 1) % n;
	}

	for(int i = 0; i < n; i++){
		if(a[i] == 1)
			return i + 1;
	}
}
/*	数组算法(无删除元素)	O(mn)	*/
static int jonseArray3(int n,int m){
	int a[300];
	for(int i=0;i<n;i++)
		a[i]=1;

	int i = 0, j = 0, k = 0;
	while(k!=n-1){
		if(a[i]==1){
			j=j+1;
			if(j==m){
				a[i]=0;
				k++;
				j=0;
			}
		}
		i = (i + 1) % n;
	}
	for(int i=0;i<n;i++){
		if(a[i]==1)
			return i + 1;
	}
}


/*	链表算法（双循环链表）	O(mn)	*/
typedef struct jonseNode{
	int code;									//编号(从0开始)
	struct jonseNode *next;
	struct jonseNode *pre;
}jonseNode;
static int jonseList(int n, int m){
	jonseNode *jonseMaxNum;						//最大code值的点作为头结点
	assert(jonseMaxNum = (jonseNode *)malloc(sizeof(jonseNode)));
	jonseMaxNum->code = n - 1;
	jonseMaxNum->next = jonseMaxNum;
	jonseMaxNum->pre = jonseMaxNum;

	for(int i = n - 2; i >= 0; i--){			//头插法插入其它结点
		jonseNode * jonseI;
		assert(jonseI = (jonseNode *)malloc(sizeof(jonseNode)));
		jonseI->code = i;
		jonseI->next = jonseMaxNum->next;
		jonseMaxNum->next = jonseI;
	}

	jonseNode *current_pre = jonseMaxNum;
	jonseNode *current;
	for(int i = 1; i <= n - 1; i++){			//每次除去一个，共除去n-1个
		int call_num = 1;
		current = current_pre->next;
		while(call_num++ < m){
			current_pre = current;
			current = current->next;
		}
		current_pre->next = current->next;
		//printf("%d\n", current->code);
		free(current);
	}

	return current_pre->code + 1;
}


/*	最优算法（低复杂度算法）	*/
static int jonseOptimal(int n, int m){
	int final = 0;
	for(int total = 2; total <= n; total++)	//total个人时的winner为final
		final = (final + m) % total;
	return final + 1;
}


int __26548535165main(){
	int n, m;

	assert(freopen("simulation\\Jonse.in", "r", stdin));
	while(1){
		scanf("%d%d", &n, &m);
		if(n == 0 && m == 0)
			break;
		printf("%d\n", jonseArray(n, m));
	}
	printf("\n");
	
	assert(freopen("simulation\\Jonse.in", "r", stdin));
	while(1){
		scanf("%d%d", &n, &m);
		if(n == 0 && m == 0)
			break;
		printf("%d\n", jonseArray2(n, m));
	}
	printf("\n");
	
	assert(freopen("simulation\\Jonse.in", "r", stdin));
	while(1){
		scanf("%d%d", &n, &m);
		if(n == 0 && m == 0)
			break;
		printf("%d\n", jonseArray3(n, m));
	}
	printf("\n");

	assert(freopen("simulation\\Jonse.in", "r", stdin));
	while(1){
		scanf("%d%d", &n, &m);
		if(n == 0 && m == 0)
			break;
		printf("%d\n", jonseList(n, m));
	}
	printf("\n");
	
	assert(freopen("simulation\\Jonse.in", "r", stdin));
	while(1){
		scanf("%d%d", &n, &m);
		if(n == 0 && m == 0)
			break;
		printf("%d\n", jonseOptimal(n, m));
	}
	printf("\n");

	fclose(stdin);
	return 0;
}
