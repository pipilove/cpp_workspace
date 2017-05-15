//*	基数排序	2013.11.17	*//
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>	//Sleep()

typedef int* ITEMTYPE_POINTER;
typedef int ITEMTYPE;
ITEMTYPE getdigit(ITEMTYPE num,int pos){	//pos数num的第pos个位，从1开始
	while(--pos)num/=10;
	return num%10;
}


//数组实现收集数据的容器
void radixSort(int* A,int A_length,int radix,int keynum){
	int i,j,k,num,radixnum;
	int** radixArray=(int**)malloc(sizeof(int)*radix);
	if(radixArray==NULL){
		printf("malloc fail ......");system("pause");exit(0);}
	for(i=0;i<=radix-1;++i){
		radixArray[i]=(int*)malloc((A_length+1)*sizeof(A[0]));	//基数为i的容器
		if(radixArray[i]==NULL){
			printf("malloc fail ......");system("pause");exit(0);}
		radixArray[i][0]=0;	//此位专用于记录基数为i容器中数的个数,初始化为0
	}

	for(int pos=1;pos<=keynum;++pos){
		for(j=0;j<=A_length-1;++j){	//通过比较第i个关键字（位）将A分配给指定容器
			num=getdigit(A[j],pos);
			radixArray[num][++radixArray[num][0]]=A[j];
		}
		for(radixnum=0,j=0;radixnum<=radix-1;++radixnum){	//按照关键字（位）0-radix将radixArray从容器中收集到A中
			k=1;
			while(radixArray[radixnum][0]){
				A[j++]=radixArray[radixnum][k++];	//从第0（~radixnum）个桶的第1(~A_length)个位置开始收集数据
				--radixArray[radixnum][0];
			}
		}
	}
}


//链表实现收集数据的容器
typedef struct node{	//注意对齐
	ITEMTYPE value;
	struct node* next;
}radixList,radixNode;
typedef struct frontrear{
	node* front;
	node* rear;
}frontrear;

void createRadixList(ITEMTYPE* A,radixList* collectA,int A_length);	
void radixDistribute(radixList* collectA,int keynum,frontrear* ft,int radix);
void radixCollect(radixList* collectA,frontrear* ft,int radix);
void listToArray(ITEMTYPE_POINTER A,radixList* collectA);
void deleteList(radixList* collectA);
void showCollect(radixList* collectA);
void showFt(frontrear* ft,int radix);

void radixSort11111111111111111(ITEMTYPE_POINTER A,int A_length,int radix,int keynum){
	radixList* collectA=(radixList*)malloc(sizeof(radixList));	//收集数据的链表(开始只有一个头结点，无实际数据意义)
	if(!collectA){printf("radixList* collectA malloc fail ... ... \n");Sleep(3000);exit(0);}
	collectA->next = NULL;//collectA->value = 0;
	createRadixList(A,collectA,A_length);

	frontrear* ft = new frontrear[radix];	//创建头尾数组
	if(ft == NULL){printf("frontrear* ft malloc fail ... ...\n");Sleep(3000);exit(0);}

	//分配收集链表
	for(int i=1;i<=keynum;i++){	
		radixDistribute(collectA,i,ft,radix);
		//showFt(ft,radix);
		radixCollect(collectA,ft,radix);
		//showCollect(collectA);
	}

	listToArray(A,collectA);
	deleteList(collectA);
	//system("pause");
}		

//从数组创建链表(头插法)
void createRadixList(ITEMTYPE* A,radixList* collectA,int A_length){
	for(int i=0;i<=A_length-1;i++){
		radixNode* newnode = new radixNode;
		newnode->value = A[i];
		newnode->next = collectA->next;
		collectA->next = newnode;
	}
}

//一次（相当于一个keynum）分发插入数组元素到对应链表的最后结点，头结点无实际意义
void radixDistribute(radixList* collectA,int keynum,frontrear* ft,int radix){
	// ft[i].front 和 ft[i].rear 分别指向第i个子链表的第一个和最后一个结点，且每次初始化都必须置空！！！
	for(int i=0;i<=radix-1;i++){
		ft[i].front=NULL;
		ft[i].rear=NULL;
	}
	ITEMTYPE digit;
	radixNode* pos;
	while(collectA->next != NULL){
		// 取出原始链队列中的数据结点
		pos = collectA->next;
		collectA->next = pos->next;	//头结点不动
		pos->next = NULL;
		//分配取出的结点加入到对应子链表中
		digit = getdigit(pos->value,keynum);
		if(ft[digit].front != NULL){
			ft[digit].rear->next = pos;
			ft[digit].rear = pos;	//修改尾指针
		}
		else{
			ft[digit].front = pos;			
			ft[digit].rear  = pos;
		}
	}
}

//收集子链表中的结点到链表collectA中
void radixCollect(radixList* collectA,frontrear* ft,int radix){
	radixList* pos = collectA;
	for(int i=0;i<=radix-1;i++){
		if(ft[i].front){
			pos->next = ft[i].front;
			pos = ft[i].rear;	//!!
		}
	}
	pos->next = NULL;	//!!
}

//将排好序的链表写入原始数组中
void listToArray(ITEMTYPE_POINTER A,radixList* collectA){
	int i=0;
	radixNode* pos = collectA->next;
	while(pos){
		A[i++] = pos->value;
		pos = pos->next;
	}
}

//释放链表空间
void deleteList(radixList* collectA){
	radixNode* pos = collectA;
	while(pos){
		collectA = pos->next;
		delete(pos);
		pos = collectA;
	}
}

//show collectA展示原始链表
void showCollect(radixList* collectA){
	radixNode* pos = collectA->next;
	while(pos){
		printf("%d ",pos->value);
		pos = pos->next;
	}
	printf("\n");
}

//show ft展示子链表
void showFt(frontrear* ft,int radix){
	radixNode* pos;
	for(int i=0;i<=radix-1;i++){
		printf("\nft[%d]: ",i);
		pos = ft[i].front;
		while(pos){
			printf("%d ",pos->value);
			pos = pos->next;
		}
	}
	printf("\nend... ...\n");
}
