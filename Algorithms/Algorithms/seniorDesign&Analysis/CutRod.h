///*	Dynamic programming - �����и�		2013.12.21	ƤƤ		*/
#include <vector>
using namespace std;

#define PRICETYPE_MIN INT_MIN
#define PRICETYPE int

typedef struct result{
	PRICETYPE *r;
	PRICETYPE *s;
}result;

//�����и���볤��Ϊn,����i�ļ۸�Ϊ����p����¼��
result *bottomupCutRod(int n,vector<PRICETYPE> &p);
//�ع���
void cutRodSolution(int n,PRICETYPE *s);

//�Զ����µݹ�ʵ��
PRICETYPE cutRod(int n,vector<int> P,int *sForCutRod);
