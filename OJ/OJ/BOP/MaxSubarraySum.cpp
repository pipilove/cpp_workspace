//***************************************************************************************/
//*		���֮��2.14 ���� �������������֮�͵����ֵ��΢������2006��		ƤƤ 2014-9-4	*/
//***************************************************************************************/
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <limits.h>

/*	O(n^2) �����㷨	*/
static int maxSubarraySum1(int *a,int a_len){
	int max_sum = INT_MIN, sum;
	for(int i = 0; i < a_len; i++){								//��i��ʼ�������������,�����������
		sum = 0;
		for(int j = i; j < a_len; j++){
			sum += a[j];
			if(sum > max_sum)
				max_sum = sum;
		}
	}
	return max_sum;
}

/*	O(nlogn) �����㷨	*/
static int maxSubarraySum2(int *a, int low, int high){			//a[low] a[high]֮������Ӷκ�
	if(low >= high)												//ֻʣһ��Ԫ�ص�ʱ�򷵻ر���Ϊ���ֵ
		return a[low];

	int mid = (high + low) / 2;									//��a[mid]��β�����һ������֮��
	int sum = 0, max_sum_left = INT_MIN;
	for(int i = mid; i >= low; i--){
		sum += a[i];
		if(sum > max_sum_left)
			max_sum_left = sum;
	}

	int max_sum_right = INT_MIN;								//��a[mid + 1]��ʼ�����һ������֮��
	sum = 0;
	for(int i = mid + 1; i <= high; i++){
		sum += a[i];
		if(sum > max_sum_right)
			max_sum_right = sum;
	}
	int max_sum = max_sum_left + max_sum_right;

	int max_sub_left = maxSubarraySum2(a, low, mid);			//�����������Ӷκ�
	int max_sub_right = maxSubarraySum2(a, mid + 1, high); 		//�����������Ӷκ�
	int max_sub = max_sub_left > max_sub_right ? max_sub_left:max_sub_right;
	max_sum = max_sum > max_sub? max_sum : max_sub;				//�����ܵ�����Ӷκ�
	return max_sum;
}

/*	O(n) DP�㷨	*/
static int maxSubarraySum3(int *a, int n){
	int *start = (int *)malloc(sizeof(a[0]) * n);					//start[i]Ϊ��i��ʼ�İ���a[i]����������
	int *all = (int *)malloc(sizeof(a[0]) * n);						//all[i]Ϊ��i��ʼ�����һ�������
	start[n - 1] = a[n - 1];
	all[n - 1] = a[n - 1];

	for(int i = n - 2; i >= 0; i--){
		start[i] = start[i + 1] + a[i] > a[i]? start[i + 1] + a[i] : a[i];	//start[i] = max{a[i], start[i+1]+a[i]}
		all[i] = start[i] > all[i + 1] ? start[i] : all[i + 1];		//all[i] = max{start[i], all[i+1]}
	}
	return all[0];
}
/*	O(n) DP�㷨(O(1)�ռ�)	*/
static int maxSubarraySum4(int *a, int n){
	int start = a[n - 1];
	int all = a[n - 1];

	for(int i = n - 2; i >= 0; i--){
		start = start + a[i] > a[i]? start + a[i] : a[i];
		all = start > all ? start : all;
	}
	return all;
}

/* O(n) �����㷨	*/
/* 
���ŵĽ���ֻɨ������һ�飬���ʱ��Ϊ O(n)������ x1, x2, ..., xt �����Ž⡣
��ô����Ȼ�� ���κ� i <= t��x1, x2,..., xi ֮�Ͳ�����Ϊ����
���򣬿�ȥ��һ�Σ����ǿ��Եõ������ֵ����Щ�öε�������ì�ܡ�
�����˵�����Ž�Ķ�ǰ׺������Ϊ���������仰˵�����һ���εĺ�Ϊ�����򲻿��������Ž��һ���֡�
һ��ʼ���ǰ��Ϊ�� x1 ��ʼ�ĶΣ���Ϊ�ա����Ǵ����鿪ʼ��ǰ���������������������뵱ǰ�� s��ͬʱ��¼Ŀǰ���������͡�
�������һֱ����������ĳ���� xi��ʹ�� s ֮��Ϊ��������� s��Ȼ���� xi ����һ��Ԫ��Ϊ��ǰ�εĿ�ʼ��������ǰ������
�ظ��������ֱ�������������ʵ��ʱ��������Ҫά������ s ��ÿ�ζ�����Ժͣ���ֻ��Ҫά��һ����ǰ�εĺͣ�
������Ԫ�ؼ��뵱ǰ��ʱ�����¶εĺͣ������¿�ʼһ����ʱ���� 0 �ö�֮�͡�
*/
static int maxSubarraySum(int *a, int n){
	int sum = 0, max_sum = INT_MIN;
	for(int i = 0; i < n; i++){
		sum += a[i];
		if(sum > max_sum)
			max_sum = sum;
		if(sum < 0)													//ǰ׺<0ʱ����ȥ��sum���ۻ���
			sum = 0;
	}
	return max_sum;
}
/* O(n) �����㷨����¼���ұ߽磩	*/
static int maxSubarraySum5(int *a, int n){
	int sum = 0, max_sum = INT_MIN;
	int max_low = 0, max_high = 0;									//�������������ұ߽�
	int low = 0;													//��ǰ��<0ǰ׺�����������±�
	for(int i = 0; i < n; i++){
		sum += a[i];
		if(sum > max_sum){
			max_sum = sum;
			max_high = i;
			max_low = low;
		}
		if(sum < 0){												//ǰ׺<0ʱ����ȥ��sum���ۻ���
			sum = 0;
			low = i + 1;
		}
	}
	printf("max_low = %d, max_high = %d\n", max_low, max_high);
	return max_sum;
}

int __1561616main(){
	assert( freopen("BOP\\maxSubarraySum.in", "r", stdin) );
	int cases;													//���԰�����Ŀ
	scanf("%d", &cases);
	while(cases--){
		int n;													//ÿ������������Ԫ�ظ���
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
