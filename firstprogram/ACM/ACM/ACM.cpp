// ACM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h> 
#include <iostream> 
using namespace std;

const int MAXN=1000;

int partition(int *array, int left, int right){
	if (array == NULL)
		return -1;

	int pos = right;
	right--;
	while (left <= right){
		while (left < pos && array[left] <= array[pos])
			left++;

		while (right >= 0 && array[right] > array[pos])
			right--;

		if (left >= right)
			break;

		array[right]=array[left];
	}
	array[left]=array[pos];

	return left;
}

int getMidIndex(int *array, int size){
	if (array == NULL || size <= 0)
		return -1;

	int left = 0;
	int right = size - 1;
	int midPos = right >> 1;
	int index = -1;

	while (index != midPos){
		index = partition(array, left, right);

		if (index < midPos){
			left = index + 1;
		}
		else if (index > midPos){
			right = index - 1;
		}
		else{
			break;
		}
	}
	return index;
}

int sum(int *array,int i,int j){
	int sum=0,k,num=j-i;
	for(k=0;k<=num;k++)
		sum=sum+array[i+k];
	return sum;
}

int main(){
	int i=0,h=0,v=0,count=0,d=0;
	int horizonIndex,verticalIndex,horizonSum,verticalSum,horizonSum1,verticalSum1;
	int n;
	int horizonValue[MAXN];
	int verticalValue[MAXN];
	int horizonArray[MAXN];
	int verticalArray[MAXN];
	int dist[MAXN];
	while(scanf("%d",&n),n!=0){
		count++;
		for(i=0;i<n;i++)
			scanf("%d%d",&horizonArray[i],&verticalArray[i]);
		horizonIndex = getMidIndex(horizonArray, n);
		verticalIndex = getMidIndex(verticalArray, n);
		horizonValue[h++] =horizonArray[horizonIndex];
		verticalValue[v++] =verticalArray[verticalIndex];
		horizonSum=sum(horizonArray,0,horizonIndex);
		horizonSum1=sum(horizonArray,horizonIndex,n-1);
		verticalSum=sum(verticalArray,0,verticalIndex);
		verticalSum1=sum(verticalArray,verticalIndex,n-1);
		if(!(n%2))
			dist[d]=verticalSum1-verticalSum+horizonSum1-horizonSum-horizonValue[d]-verticalValue[d];
		else
			dist[d]=verticalSum1-verticalSum+horizonSum1-horizonSum;
		d++;
	}
	for(i=0;i<count;i++)
		printf("case %d: (%d,%d) %d \n",i+1,horizonValue[i],verticalValue[i],dist[i]);
	system("pause");
	return 0;
}
