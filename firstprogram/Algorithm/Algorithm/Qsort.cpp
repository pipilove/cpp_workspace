/**	c中的qsort 格式：
*qsort(array_name,data_number,sizeof(data_type),compare_function_name)  
*(void*)bsearch (pointer_to_key_word,array_name,find_number,sizeof(data_type),compare_function_name)
*/
/*
#include <iostream>
#include <stdlib.h>
using namespace std;

int cmp(const void *a,const void *b){//按非降序排序
	int *p1,*p2;
	p1=(int *)a;
	p2=(int *)b;
	if(*p1>*p2)
		return 1;
	else if(*p1==*p2)
		return 0;
	else return -1;
}

int cmpDesc(const void *a,const void *b){//按降序排序
	int *p1,*p2;
	p1=(int *)a;
	p2=(int *)b;
	if(*p1>*p2)
		return 1;
	else return 0;
}

int cmpAsc(const void *a,const void *b){//按升序排序
	int *p1,*p2;
	p1=(int *)a;
	p2=(int *)b;
	if(*p1<*p2)
		return 1;
	else return 0;
}

int main(){
	int i;
	int a[]={48,10,13,5,10,51,33,43,10,4,14,1,41,41};
	int len=sizeof(a)/sizeof(a[0]);

	for(i=0;i<len;i++)
	cout<<a[i]<<", ";
	cout<<endl;

	qsort(a,len,sizeof(int),cmp);//默认为非降序序
	for(i=0;i<len;i++)
	cout<<a[i]<<", ";
	cout<<endl;

	qsort(a,len,sizeof(int),cmpDesc);//自定义为降序
	for(i=0;i<len;i++)
	cout<<a[i]<<", ";
	cout<<endl;

	qsort(a,len,sizeof(int),cmpAsc);//自定义为升序
	for(i=0;i<len;i++)
	cout<<a[i]<<", ";
	cout<<endl;

	system("pause");
	return 0;
}
*/