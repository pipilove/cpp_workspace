///*	dynamic promming - lcs	2014.1.6	ƤƤ		*/
#include "LCS.h"
#include <iostream>
using namespace std;
//�����������
vector< vector<int> > lcs(vector<ITEMTYPE> X,vector<ITEMTYPE> Y,vector< vector<int> > &B){
	//Z�Ĵ�СΪ(X.size+1) * (Y.size+1),Z[i][j]����XiYj��lcs����
	vector< vector<int> > Z(X.size()+1);
	for(int i = 0;i <= X.size();i++){
		Z[i].resize(Y.size()+1);
		Z[i][0] = 0;
	}
	for(int j = 0;j <= Y.size();j++)
		Z[0][j] = 0;

	for(int i = 1;i <= X.size();i++){			//�߼��ϴ�1��ʼ����XY�ĵ�һ���ַ�
		for(int j = 1;j <= Y.size();j++){
			if(X[i-1] == Y[j-1]){
				Z[i][j] = Z[i-1][j-1] + 1;
				B[i][j] = 2;					//Ӧ��Ϊ���ֵ��ͬ��ֵ
			}
			else if(Z[i][j-1] >= Z[i-1][j]){
				Z[i][j] = Z[i][j-1];
				B[i][j] = -1;
			}
			else{
				Z[i][j] = Z[i-1][j];
				B[i][j] = 1;
			}
		}
	}
	return Z;
}

//printf the optimal solution of lcs
void printfLCS(vector< vector<int> > B,vector<ITEMTYPE> X,int i,int j){
	if(i == 0 || j == 0)
		return;
	if(B[i][j] == 2){
		printfLCS(B,X,i-1,j-1);
		cout<<X[i-1];		//X[i]�����i��������1��ʼ��
	}
	else if(B[i][j] == 1)
		printfLCS(B,X,i-1,j);
	else
		printfLCS(B,X,i,j-1);
}

//printf the optimal solution of lcs according to Z without B
void printfLCSZ(vector< vector<int> > Z,vector<ITEMTYPE> X,int i,int j){
	if(i == 0 || j== 0)
		return;
	if(Z[i][j] == Z[i-1][j-1]+1){
		printfLCSZ(Z,X,i-1,j-1);
		cout<<X[i-1];
	}
	else if(Z[i][j] == Z[i-1][j])
		printfLCSZ(Z,X,i-1,j);
	else
		printfLCSZ(Z,X,i,j-1);
}
