/**	输油管道问题(类似求中位数问题)	*/
#include <iostream>  
#include <fstream>  
#include <math.h>  
using namespace std;

//以x为基准元素对子数组a[start：end]进行划分，将小于基准的元素放在左边
int part(int* a,int start,int end){
    int i,j,x,temp;  
    i=start;  
    j=end+1;  
    x=a[start];  
    while(1){	//2°数组划分算法,第一种见数据结构书
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
    partPos=part(a,start,end);  //以a[start]为基准元素对子数组a[start：end]进行左小右大划分后a[start]的位置
    position=partPos-start+1;  //实际中的位置，从序号1开始的
    if(k<=position)  
        return  selectK(a,start,partPos,k);  
    else  
        return selectK(a,partPos+1,end,k-position);  
}  
  
void main(){   
    int i,n,sum,middle; 
    fstream file;  //文件操作！！！
    file.open("input.txt",ios::in);  
    file>>n;  
    int* a=new int[n];  
    for(i=0;i<n;i++)  
        file>>a[i]>>a[i];  //只需要纵坐标
    file.close();  
  
    middle=selectK(a,0,n-1,(n+1)/2);  //求中位数
    for(i=0,sum=0;i<n;i++)  
        sum+=abs(a[i]-middle);  
      
    file.open("output.txt",ios::out);  
    file<<sum;  
    file.close();  

    delete []a;  
    a=0;  
}  