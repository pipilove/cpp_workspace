//****************************************************************************************************/
//*	 CCF软件能力认证考试模拟题 —— 最大矩形Largest Rectangle in a Histogram poj2559	皮皮 2014-9-3	*/
//****************************************************************************************************/
#include <iostream>
#include <assert.h>
using namespace std;

/*	ccf标准算法	TLE!!!	*/						//????????????????
static void largestRectangle(){
	int n;												//直方图柱形数目
	cin>>n;
	int *height = new int[n];
	for(int i = 0; i < n; i++)
		cin>>height[i];

	long long sum, max = 0;
	for(int i = 0; i < n; i++){
		int h = height[i];
		for(int j = i; j < n; j++){						//向右扫描
			if( height[j] < h )							//高度小时改为小的高度
				h = height[j];
			sum = (j - i +1) * h;						//计算高度h的矩形面积
			if(sum > max)								//比原来大则替换
				max = sum;
		}
		while( i < n - 1 && height[i+1] < height[i] )	//改进：比当前height[i]小的不用再计算（i后面高度比i小的不可能有更大面积的矩形）
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
		sum = 1;										//初始只有一个这样高度的
		j = i - 1;
		k = i + 1;
		while(j >= 0 && height[j] >= height[i]){		//向左扫描同样高度的有多少个
			sum++;
			j--;
		}
		while(k <= n - 1 && height[k] >= height[i]){	//向右扫描同样高度的有多少个
			sum++;
			k++;
		}
		sum *= height[i];								//计算高度为当前大小的直方柱有多少个（即矩形面积大小）
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
