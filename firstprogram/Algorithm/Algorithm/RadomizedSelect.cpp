/**	�������������ҳ���iС��Ԫ���㷨	*/
/*
#include <iostream>
#include <ctime>
#include <cstdlib>	
using namespace std;

//1�㻮�ֺ������ڶ��ּ�Petrol.cpp��
int partition(int *a,int p,int r){
	int x=a[p];//ѡȡ��Ԫ�أ����������
	while(p<r){
		while(p<r&&a[r]>=x) r--;
		if(p<r) {a[p]=a[r];p++;}
		while(p<r&&a[p]<=x) p++;
		if(p<r) {a[r]=a[p];r--;}
	}
	a[p]=x;
	return p;
}

//������ֺ���
int radomizedPartition(int *a,int p,int r){
	srand((unsigned)time(0));
	int len=r-p+1;
	int i=rand()%len+p;//����p-r֮��������i	//cout<<"i	"<<i<<endl;//for test
	int temp=a[i];//�������ѡ���Ԫ�غ���Ԫ��
	a[i]=a[p];
	a[p]=temp;
	return partition(a,p,r);
}

//���ѡ���iС��Ԫ��
int radomizedSelect(int *a,int p,int r,int i){
	if(p==r)return a[p];
	int position=radomizedPartition(a,p,r);
	int k=position-p+1;
	if(k==i)return a[position];//ע�ⷵ�ص���a[position]����a[k]
	else if(k<i)
		return radomizedSelect(a,position+1,r,i-k);
	else
		return radomizedSelect(a,p,position-1,i);
}

int main(){
	int a[]={2,2,4,-2,3};
	int len=sizeof(a)/sizeof(int);
	int midian=radomizedSelect(a,0,len-1,(len+1)/2);//��a[]����λ��
	cout<<"midian: "<<midian<<endl;
	system("pause");
	return 0;
}
*/