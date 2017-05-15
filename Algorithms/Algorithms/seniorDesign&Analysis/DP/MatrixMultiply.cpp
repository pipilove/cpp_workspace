///*	Dynamic programming - �������˷�		2013.12.22	ƤƤ		*/
#include <climits>
#include <iostream>
#include <vector>
#define INFINATY INT_MAX
#define ITEMTYPE int
using namespace std;

typedef struct matrixRes{
	int **m;
	int **s;
}matrixRes;

//�����������С�˷�����
matrixRes *matrixChainOrder(vector<int> P);
//�ع���
void printOptimalParens(int **s,int i,int j);

//�ݹ��㷨
int recursiveMatrixChain(int i,int j,vector<int> P,int **s);

//������¼�ĵݹ��㷨
int memoizedMatirxChain(vector<int> p,int **s);
int lookupChain(vector< vector<int> > m,vector<int> p,int i,int j,int **s);

//�����������С�˷�����
matrixRes *matrixChainOrder(vector<int> P){
	int n = P.size()-1;							//�������ΪP.size()-1
	int **m = new int*[n];					//�������Ai,j��С�˷�����,�±��1��ʼ��Ч��
	int **s = new int*[n];
	for(int i = 1;i <= n;i++){
		m[i] = new int[n];
		s[i] = new int[n];
		m[i][i] = 0;							//��ʼ��Ϊ0
	}
	for(int l = 2;l <= n;l++)					//���������ȣ���ʼΪ2
		for(int i = 1;i <= n-l+1;i++){			//����,��ʼΪ1
			int j = i+l-1;						//��β����ʼΪ2
			m[i][j] = INFINATY;
			for(int k = i;k <= j-1;k++){		//�ϵ㣬��ʼΪi��
				int tmpm = m[i][k] + m[k+1][j] + P[i-1]*P[k]*P[j];
				//P[i-1]*P[k]	P[k]*P[j]		!!
				if(m[i][j] > tmpm){
					m[i][j] = tmpm;
					s[i][j] = k;				//��¼�ϵ�λ��
				}
			}
		}
		matrixRes *res = new matrixRes;
		res->m = m;
		res->s = s;
		return res;
}
//�ع��⣡����
void printOptimalParens(int **s,int i,int j){
	if(i == j)
		printf("A%d",i);
	else{
		printf("(");
		printOptimalParens(s,i,s[i][j]);
		printOptimalParens(s,s[i][j]+1,j);
		printf(")");
	}
}

//�ݹ��㷨
int recursiveMatrixChain(int i,int j,vector<int> P,int **s){
	if(i == j)
		return 0;
	int tmin,min = INFINATY;
	for(int k = i;k <= j-1;k++){
		tmin = recursiveMatrixChain(i,k,P,s)+recursiveMatrixChain(k+1,j,P,s)+P[i-1]*P[k]*P[j];
		if(tmin < min){
			min = tmin;
			s[i][j] = k;
		}
	}
	return min;
}

//������¼�ĵݹ��㷨
int memoizedMatirxChain(vector<int> p,int **s){
	int n = p.size()-1;			//matrice num
	vector< vector<int> > m(n+1);	//define n vectors,that is n*n 2 dimensions' array
	for(int i = 1;i <= n;i++){
		m[i].resize(n+1);			//each vector has n elements
		for(int j = i;j <= n;j++)	//j start from i
			m[i][j] = INFINATY;
	}
	return lookupChain(m,p,1,n,s);
}
int lookupChain(vector< vector<int> > m,vector<int> p,int i,int j,int **s){
	if(m[i][j] < INFINATY)
		return m[i][j];
	if(i == j)
		m[i][j] = 0;
	else
		for(int k = i;k <= j-1;k++){
			int q = lookupChain(m,p,i,k,s)+lookupChain(m,p,k+1,j,s)+p[i-1]*p[k]*p[j];
			if(q < m[i][j]){
				m[i][j] = q;
				s[i][j] = k;
			}
		}
	return m[i][j];
}


//test for matrixChainOrder
void testMatrixChainOrder(vector<int> A){
	matrixRes *res = matrixChainOrder(A);
	/*for(int i = 1;i <= A.size()-1;i++){
	for(int j = i;j <= A.size()-1;j++)
	printf("%d ",res->m[i][j]);
	printf("\n");
	}*/
	printf("the optimal res is: %d\n",res->m[1][A.size()-1]);		//�������ֵ
	printf("the optimal solution is:\n");
	printOptimalParens(res->s,1,A.size()-1);						//������Ž�
	printf("\n");
}
//test for recursiveMatrixChain
void testRecursiveMatrixChain(vector<int> A){
	int **s = new int*[A.size()];
	for(int i = 0;i <= A.size()-1;i++)
		s[i] = new int[A.size()];
	int min = recursiveMatrixChain(1,A.size()-1,A,s);				//��A.size()-1������
	printf("the optimal res is: %d\n",min);
	printf("the optimal solution is:\n");
	printOptimalParens(s,1,A.size()-1);								//������Ž�
	printf("\n");
}
//test for memoizedMatirxChain
void testMemoizedMatirxChain(vector<int> A){
	int ** s = new int*[A.size()];
	for(int i = 0;i <= A.size()-1;i++)
		s[i] = new int[A.size()];
	int min = memoizedMatirxChain(A,s);
	printf("the optimal res is: %d",min);
	printf("\n");
	printf("the optimal solution is:\n");
	printOptimalParens(s,1,A.size()-1);								//������Ž�
	printf("\n");
}


int __2516465132main(){
	vector<ITEMTYPE> A;
	//generate A
	printf("\n");

	//test for matrixChainOrder,matrix num is A.size()-1
	//testMatrixChainOrder(A);
	//test for recursiveMatrixChain
	//testRecursiveMatrixChain(A);
	//test for memoizedMatirxChain
	//testMemoizedMatirxChain(A);

	printf("\n");
	system("pause");
	return 0;
}
