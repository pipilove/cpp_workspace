///*	Dynamic programming - 钢条切割		2013.12.21	皮皮		*/
#include <vector>
using namespace std;

#define PRICETYPE_MIN INT_MIN
#define PRICETYPE int

typedef struct result{
	PRICETYPE *r;
	PRICETYPE *s;
}result;

//钢条切割（输入长度为n,长度i的价格为数组p）记录解
result *bottomupCutRod(int n,vector<PRICETYPE> &p);
//重构解
void cutRodSolution(int n,PRICETYPE *s);

//自顶向下递归实现
PRICETYPE cutRod(int n,vector<int> P,int *sForCutRod);
