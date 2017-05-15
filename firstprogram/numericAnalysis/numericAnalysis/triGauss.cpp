/*	三对角矩阵分解	*/
#include "stdio.h"
#include "stdlib.h"

void triGauss(int* a,int* b,int*c,int* f){
	int n=4;//sizeof(b)/sizeof(b[0]);	//矩阵阶数
	int i,d;
	for(i=1;i<=n-1;i++){
		d=a[i]/b[i];
		b[i+1]=b[i+1]-d*c[i];
		f[i+1]=f[i+1]-d*f[i];
	}
	f[n]=f[n]/b[n];
	for(i=n-1;i>=1;i--)
		f[i]=(f[i]-c[i]*f[i+1])/b[i];
}

int main(){
	int a[3]={-1,-2,-3};
	int b[4]={2,3,4,5};
	int c[3]={-1,-2,-2};
	int f[4]={6,1,0,1};
	triGauss(a,b,c,f);
	for(int k=0;k<=3;k++)
		printf("%d ",f[k]);
}
