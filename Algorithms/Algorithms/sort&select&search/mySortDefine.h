#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include  <windows.h>	//设置字体颜色;Sleep()

#define arrayLength(A)(sizeof(A)/sizeof(A[0]))	//返回数组的长度

//#define RAND_MAX 0x7fffffff	//无效，实际RAND_MAX=36767	
//相对于函数random()对性能提升不大
//如果是rand()%100,因为32767不是100的倍数,所以0-67的概率要大于68-99的概率,这可能就是叶赛所指的问题
#define random(low,upper)((rand()*rand())%((upper)-(low)+1)+(low))

//交换两个数的宏定义算法,逗号隔开
//两个数不能是同一个数，否则第一次a^=b时a和b都变为0,这时应该添加判断，相等则不交换
#define swap(a,b) (a^=b,b^=a,a^=b)	//但添加判断会影响外层的if else
//template<class T>
//inline void swap(T &a,T &b){
//	if(a != b)(a^=b,b^=a,a^=b);
//}