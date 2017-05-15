#include <iostream>
using namespace std;
#include<stdio.h>
void ff(int n,int m){
	int a[100],i=0,j,k;
	for(i=0;i<n;i++)
		a[i]=1;
	k=0;
	j=0;
	i=0;
	while(k!=n-1){
		if(a[i]==1){
			j=j+1;
			if(j==m){
				a[i]=0;
				k++;
				j=0;
			}
		}
		i++;
		i %= n;
	}
	for(i=0;i<n;i++)
		if(a[i]==1)
			printf("%d\n",i);
}
void __main(){
	ff(10,4);
	system("pause");
}