///*	Dynamic programming - 钢条切割		2013.12.21	皮皮		*/
#include "CutRod.h"
using namespace std;

//钢条切割（输入长度为n,长度i的价格为数组p）记录解
result *bottomupCutRod(int n,vector<PRICETYPE> &p){
	PRICETYPE *r = new PRICETYPE[n+1];	//记录最优子结构的解，辅助数组
	PRICETYPE *s = new PRICETYPE[n+1];	//子问题i第一段最优切割长度
	r[0] = 0;
	s[0] = 0;
	for(int i = 1;i <= n;i++){			//问题规模
		r[i] = PRICETYPE_MIN;			//子问题i的解
		for(int j = 0;j < i;j++)		//不进行切割的左边开始一段的长度j
			if(r[i] < p[j] + r[i-j-1]){
				r[i] = p[j] + r[i-j-1];
				s[i] = j + 1;			//规模为i的时候，长度j+1是不动的，子结构r[i-j-1]动
			}
	}

	result *res = new result;			//!!
	res->r = r;
	res->s = s;
	return res;							//返回解和解的值
}
//重构解
void cutRodSolution(int n,PRICETYPE *s){
	printf("the best solution is : ");
	while(n > 0){
		printf("%d ",s[n]);
		n = n-s[n];
	}
}

//自顶向下递归实现(带有记录解)
PRICETYPE cutRod(int n,vector<int> P,int *sForCutRod){
	if(n == 0)
		return 0;
	int max = PRICETYPE_MIN;
	PRICETYPE temp;
	for(int i = 1;i <= n;i++){
		temp = P[i-1] + cutRod(n-i,P,sForCutRod);
		if(temp > max){
			max = temp;
			sForCutRod[n] = i;
		}
	}
	return max;
}
