/*#include <stdio.h>
//#include <iostream>

const int MAX=100001;

int main(){
	int x,y,z,T,i=0;
	scanf("%d",&T);
	int sum[MAX]={0};
	while(i!=T){
		scanf("%d%d%d",&x,&y,&z);
		if(x==0)
			sum[i]=1;
		else if(x==1){
			if(y==0)
				sum[i]=2;
			else if(y==1)
				sum[i]=4;
			else
				sum[i]=x+y*2+z*5+1;
		}
		else if(x==2||x==3){
			if(y==0)
				sum[i]=x+1;
			else
				sum[i]=x+y*2+z*5+1;
		}
		else
			sum[i]=x+y*2+z*5+1;
		i++;
	}

	for(i=0;i<T;i++)
		printf("Case #%d: %d\n",i+1,sum[i]);
	//system("pause");
	return 0;
}
*/