#include "stdio.h"
#include "stdlib.h"
#include "algorithm"

int machine[3][10];//������ż���ɵ�������
int timeSum[3]={0};//�������������ʱ��
int taskTime[12]={0};//ÿ�����������Ҫ��ʱ��

int main(){
	int i,j,k;
	for (i=0;i<10;i++)
		scanf("%d",&taskTime[i]);
	int compi(const void *a, const void *b){  
    const int *p = a;  
    const int *q = b;  
  
    return *p - *q;  
} 
	int compd(const void *a, const void *b){  
		const int *p = a;  
		const int *q = b;  
		return (*p - *q) * (-1);  
	} 
	qsort(taskTime,10,sizeof(taskTime[0]),compd);
	for (j=0;j<10;j*=3){
		qsort(timeSum,10,sizeof(timeSum[0]),compi);
		for (i=0;i<3;i++){
			timeSum[i]+=taskTime[i+j];
			machine[i][k++]=i+j;
		}
	}
	for()
	return 0;
}