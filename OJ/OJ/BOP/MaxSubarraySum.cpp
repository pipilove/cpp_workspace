//***************************************************************************************/
//*		编程之美2.14 —— 求数组的子数组之和的最大值（微软亚研2006）		皮皮 2014-9-4	*/
//***************************************************************************************/
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <limits.h>

/*	O(n^2) 遍历算法	*/
static int maxSubarraySum1(int *a,int a_len){
	int max_sum = INT_MIN, sum;
	for(int i = 0; i < a_len; i++){								//从i开始的子数组的最大和,遍历所有情况
		sum = 0;
		for(int j = i; j < a_len; j++){
			sum += a[j];
			if(sum > max_sum)
				max_sum = sum;
		}
	}
	return max_sum;
}

/*	O(nlogn) 分治算法	*/
static int maxSubarraySum2(int *a, int low, int high){			//a[low] a[high]之间最大子段和
	if(low >= high)												//只剩一个元素的时候返回本身为最大值
		return a[low];

	int mid = (high + low) / 2;									//以a[mid]结尾的最大一段数组之和
	int sum = 0, max_sum_left = INT_MIN;
	for(int i = mid; i >= low; i--){
		sum += a[i];
		if(sum > max_sum_left)
			max_sum_left = sum;
	}

	int max_sum_right = INT_MIN;								//以a[mid + 1]开始的最大一段数组之和
	sum = 0;
	for(int i = mid + 1; i <= high; i++){
		sum += a[i];
		if(sum > max_sum_right)
			max_sum_right = sum;
	}
	int max_sum = max_sum_left + max_sum_right;

	int max_sub_left = maxSubarraySum2(a, low, mid);			//数组左段最大子段和
	int max_sub_right = maxSubarraySum2(a, mid + 1, high); 		//数组左段最大子段和
	int max_sub = max_sub_left > max_sub_right ? max_sub_left:max_sub_right;
	max_sum = max_sum > max_sub? max_sum : max_sub;				//数组总的最大子段和
	return max_sum;
}

/*	O(n) DP算法	*/
static int maxSubarraySum3(int *a, int n){
	int *start = (int *)malloc(sizeof(a[0]) * n);					//start[i]为从i开始的包含a[i]最大子数组和
	int *all = (int *)malloc(sizeof(a[0]) * n);						//all[i]为从i开始的最大一段数组和
	start[n - 1] = a[n - 1];
	all[n - 1] = a[n - 1];

	for(int i = n - 2; i >= 0; i--){
		start[i] = start[i + 1] + a[i] > a[i]? start[i + 1] + a[i] : a[i];	//start[i] = max{a[i], start[i+1]+a[i]}
		all[i] = start[i] > all[i + 1] ? start[i] : all[i + 1];		//all[i] = max{start[i], all[i+1]}
	}
	return all[0];
}
/*	O(n) DP算法(O(1)空间)	*/
static int maxSubarraySum4(int *a, int n){
	int start = a[n - 1];
	int all = a[n - 1];

	for(int i = n - 2; i >= 0; i--){
		start = start + a[i] > a[i]? start + a[i] : a[i];
		all = start > all ? start : all;
	}
	return all;
}

/* O(n) 最优算法	*/
/* 
最优的解是只扫描数组一遍，因此时间为 O(n)。假设 x1, x2, ..., xt 是最优解。
那么，显然， 对任何 i <= t，x1, x2,..., xi 之和不可能为负。
否则，砍去这一段，我们可以得到更大的值，这些该段的最优性矛盾。
这就是说，最优解的段前缀不可能为负。而换句话说，如果一个段的和为负，则不可能是最优解的一部分。
一开始，令当前段为从 x1 开始的段，置为空。我们从数组开始向前搜索，并把遇到的数加入当前段 s，同时记录目前遇到的最大和。
这个过程一直持续到加入某个数 xi，使得 s 之和为负，则清空 s，然后以 xi 的下一个元素为当前段的开始，继续向前搜索。
重复这个过程直到数组结束。在实现时，并不需要维护集合 s 并每次都对其对和，而只需要维护一个当前段的和，
当有新元素加入当前段时，更新段的和；当重新开始一个段时，清 0 该段之和。
*/
static int maxSubarraySum(int *a, int n){
	int sum = 0, max_sum = INT_MIN;
	for(int i = 0; i < n; i++){
		sum += a[i];
		if(sum > max_sum)
			max_sum = sum;
		if(sum < 0)													//前缀<0时可以去掉sum的累积和
			sum = 0;
	}
	return max_sum;
}
/* O(n) 最优算法（记录左右边界）	*/
static int maxSubarraySum5(int *a, int n){
	int sum = 0, max_sum = INT_MIN;
	int max_low = 0, max_high = 0;									//最优子数组左右边界
	int low = 0;													//当前非<0前缀的子数组首下标
	for(int i = 0; i < n; i++){
		sum += a[i];
		if(sum > max_sum){
			max_sum = sum;
			max_high = i;
			max_low = low;
		}
		if(sum < 0){												//前缀<0时可以去掉sum的累积和
			sum = 0;
			low = i + 1;
		}
	}
	printf("max_low = %d, max_high = %d\n", max_low, max_high);
	return max_sum;
}

int __1561616main(){
	assert( freopen("BOP\\maxSubarraySum.in", "r", stdin) );
	int cases;													//测试案例数目
	scanf("%d", &cases);
	while(cases--){
		int n;													//每个案例中数组元素个数
		scanf("%d", &n);
		int *a = (int *)malloc(sizeof(int) * n);
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);

		printf("%d\n", maxSubarraySum1(a, n));
		printf("%d\n", maxSubarraySum2(a, 0, n - 1));
		printf("%d\n", maxSubarraySum3(a, n));
		printf("%d\n", maxSubarraySum4(a, n));
		printf("%d\n", maxSubarraySum(a, n));
		printf("%d\n\n", maxSubarraySum5(a, n));
	}
	fclose(stdin);
	return 0;
}
