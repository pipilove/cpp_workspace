//****************************************************************************************************/
//*	 CCF���������֤����ģ���� ���� ������Largest Rectangle in a Histogram poj2559	ƤƤ 2014-9-3	*/
//****************************************************************************************************/
#include <iostream>
#include <assert.h>
using namespace std;

/*	ccf��׼�㷨	TLE!!!	*/						//????????????????
static void largestRectangle(){
	int n;												//ֱ��ͼ������Ŀ
	cin>>n;
	int *height = new int[n];
	for(int i = 0; i < n; i++)
		cin>>height[i];

	long long sum, max = 0;
	for(int i = 0; i < n; i++){
		int h = height[i];
		for(int j = i; j < n; j++){						//����ɨ��
			if( height[j] < h )							//�߶�Сʱ��ΪС�ĸ߶�
				h = height[j];
			sum = (j - i +1) * h;						//����߶�h�ľ������
			if(sum > max)								//��ԭ�������滻
				max = sum;
		}
		while( i < n - 1 && height[i+1] < height[i] )	//�Ľ����ȵ�ǰheight[i]С�Ĳ����ټ��㣨i����߶ȱ�iС�Ĳ������и�������ľ��Σ�
			i++;
	}
	cout<<max<<endl;
}

static void largestRectangle1(){
	int n;
	cin>>n;
	//while(n){	
	int *height = (int *)malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++)
		cin>>height[i];

	int j, k, sum, max = 0;
	for(int i = 0; i < n; i++){
		sum = 1;										//��ʼֻ��һ�������߶ȵ�
		j = i - 1;
		k = i + 1;
		while(j >= 0 && height[j] >= height[i]){		//����ɨ��ͬ���߶ȵ��ж��ٸ�
			sum++;
			j--;
		}
		while(k <= n - 1 && height[k] >= height[i]){	//����ɨ��ͬ���߶ȵ��ж��ٸ�
			sum++;
			k++;
		}
		sum *= height[i];								//����߶�Ϊ��ǰ��С��ֱ�����ж��ٸ��������������С��
		if(sum > max)
			max = sum;
	}
	cout<<max<<endl;
	cin>>n;/*
		   }*/
}

int __518415main(){
	//assert( freopen("CCF\\largestRectangle1.in", "r", stdin) );
	largestRectangle1();
	//fclose(stdin);
	return 0;
}
