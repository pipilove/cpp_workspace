/**	Բ����ʯ�Ӻϲ�����	*/
#include <iostream>
using namespace std;

int minFuction();

int main(){
	int n,i,j,k;
	cout<<"������ʯ�Ӷ����� ";
	cin>>n;
	int *stone=new int[n];
	cout<<"���������ʯ�ӵĸ����� ";	
	for(i=0;i<n;i++)
		cin>>stone[i];

	int **m=new int*[n];
	for(i=0;i<n;i++)
		m[i]=new int[n];
	//m[i][j]��ʾ�Ӵӵ�i����j��ʯ�Ӻϲ��������ƶ���
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			if(i==j)m[i][j]=0;//������ϣ��������ƶ����ƶ���Ϊ0
			else
				m[i][j]=-1;//��ʼ��
		};
	for(i=0,j=1;i<n;i++,j++)//������ϣ�ֱ�����
			m[i][j]=stone[i]+stone[j];
	for(k=3;k<n;k++)
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
			m[i][j]

	int minFuction();
	return 0;
}

int minFuction();