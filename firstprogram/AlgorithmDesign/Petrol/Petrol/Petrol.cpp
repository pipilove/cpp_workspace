/**	���͹ܵ�����(��������λ������)	*/
#include <iostream>  
#include <fstream>  
#include <math.h>  
using namespace std;

//��xΪ��׼Ԫ�ض�������a[start��end]���л��֣���С�ڻ�׼��Ԫ�ط������
int part(int* a,int start,int end){
    int i,j,x,temp;  
    i=start;  
    j=end+1;  
    x=a[start];  
    while(1){	//2�����黮���㷨,��һ�ּ����ݽṹ��
        while(i<end&&a[++i]<x);  
        while(j>start&&a[--j]>=x);  
        if(i>=j)  
            break;  
        temp=a[i];  
        a[i]=a[j];  
        a[j]=temp;  
    }  
    a[start]=a[j];  
    a[j]=x;  
    return j;
}  
  
int selectK(int* a,int start,int end,int k){  
    int partPos,position;  
    if(start==end)  
        return a[start];  
    partPos=part(a,start,end);  //��a[start]Ϊ��׼Ԫ�ض�������a[start��end]������С�Ҵ󻮷ֺ�a[start]��λ��
    position=partPos-start+1;  //ʵ���е�λ�ã������1��ʼ��
    if(k<=position)  
        return  selectK(a,start,partPos,k);  
    else  
        return selectK(a,partPos+1,end,k-position);  
}  
  
void main(){   
    int i,n,sum,middle; 
    fstream file;  //�ļ�����������
    file.open("input.txt",ios::in);  
    file>>n;  
    int* a=new int[n];  
    for(i=0;i<n;i++)  
        file>>a[i]>>a[i];  //ֻ��Ҫ������
    file.close();  
  
    middle=selectK(a,0,n-1,(n+1)/2);  //����λ��
    for(i=0,sum=0;i<n;i++)  
        sum+=abs(a[i]-middle);  
      
    file.open("output.txt",ios::out);  
    file<<sum;  
    file.close();  

    delete []a;  
    a=0;  
}  