#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include  <windows.h>	//����������ɫ;Sleep()

#define arrayLength(A)(sizeof(A)/sizeof(A[0]))	//��������ĳ���

//#define RAND_MAX 0x7fffffff	//��Ч��ʵ��RAND_MAX=36767	
//����ں���random()��������������
//�����rand()%100,��Ϊ32767����100�ı���,����0-67�ĸ���Ҫ����68-99�ĸ���,����ܾ���Ҷ����ָ������
#define random(low,upper)((rand()*rand())%((upper)-(low)+1)+(low))

//�����������ĺ궨���㷨,���Ÿ���
//������������ͬһ�����������һ��a^=bʱa��b����Ϊ0,��ʱӦ������жϣ�����򲻽���
#define swap(a,b) (a^=b,b^=a,a^=b)	//������жϻ�Ӱ������if else
//template<class T>
//inline void swap(T &a,T &b){
//	if(a != b)(a^=b,b^=a,a^=b);
//}