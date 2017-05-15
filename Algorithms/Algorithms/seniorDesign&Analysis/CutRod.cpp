///*	Dynamic programming - �����и�		2013.12.21	ƤƤ		*/
#include "CutRod.h"
using namespace std;

//�����и���볤��Ϊn,����i�ļ۸�Ϊ����p����¼��
result *bottomupCutRod(int n,vector<PRICETYPE> &p){
	PRICETYPE *r = new PRICETYPE[n+1];	//��¼�����ӽṹ�Ľ⣬��������
	PRICETYPE *s = new PRICETYPE[n+1];	//������i��һ�������и��
	r[0] = 0;
	s[0] = 0;
	for(int i = 1;i <= n;i++){			//�����ģ
		r[i] = PRICETYPE_MIN;			//������i�Ľ�
		for(int j = 0;j < i;j++)		//�������и����߿�ʼһ�εĳ���j
			if(r[i] < p[j] + r[i-j-1]){
				r[i] = p[j] + r[i-j-1];
				s[i] = j + 1;			//��ģΪi��ʱ�򣬳���j+1�ǲ����ģ��ӽṹr[i-j-1]��
			}
	}

	result *res = new result;			//!!
	res->r = r;
	res->s = s;
	return res;							//���ؽ�ͽ��ֵ
}
//�ع���
void cutRodSolution(int n,PRICETYPE *s){
	printf("the best solution is : ");
	while(n > 0){
		printf("%d ",s[n]);
		n = n-s[n];
	}
}

//�Զ����µݹ�ʵ��(���м�¼��)
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
