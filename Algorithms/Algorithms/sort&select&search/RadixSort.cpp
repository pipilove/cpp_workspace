//*	��������	2013.11.17	*//
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>	//Sleep()

typedef int* ITEMTYPE_POINTER;
typedef int ITEMTYPE;
ITEMTYPE getdigit(ITEMTYPE num,int pos){	//pos��num�ĵ�pos��λ����1��ʼ
	while(--pos)num/=10;
	return num%10;
}


//����ʵ���ռ����ݵ�����
void radixSort(int* A,int A_length,int radix,int keynum){
	int i,j,k,num,radixnum;
	int** radixArray=(int**)malloc(sizeof(int)*radix);
	if(radixArray==NULL){
		printf("malloc fail ......");system("pause");exit(0);}
	for(i=0;i<=radix-1;++i){
		radixArray[i]=(int*)malloc((A_length+1)*sizeof(A[0]));	//����Ϊi������
		if(radixArray[i]==NULL){
			printf("malloc fail ......");system("pause");exit(0);}
		radixArray[i][0]=0;	//��λר���ڼ�¼����Ϊi���������ĸ���,��ʼ��Ϊ0
	}

	for(int pos=1;pos<=keynum;++pos){
		for(j=0;j<=A_length-1;++j){	//ͨ���Ƚϵ�i���ؼ��֣�λ����A�����ָ������
			num=getdigit(A[j],pos);
			radixArray[num][++radixArray[num][0]]=A[j];
		}
		for(radixnum=0,j=0;radixnum<=radix-1;++radixnum){	//���չؼ��֣�λ��0-radix��radixArray���������ռ���A��
			k=1;
			while(radixArray[radixnum][0]){
				A[j++]=radixArray[radixnum][k++];	//�ӵ�0��~radixnum����Ͱ�ĵ�1(~A_length)��λ�ÿ�ʼ�ռ�����
				--radixArray[radixnum][0];
			}
		}
	}
}


//����ʵ���ռ����ݵ�����
typedef struct node{	//ע�����
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
	radixList* collectA=(radixList*)malloc(sizeof(radixList));	//�ռ����ݵ�����(��ʼֻ��һ��ͷ��㣬��ʵ����������)
	if(!collectA){printf("radixList* collectA malloc fail ... ... \n");Sleep(3000);exit(0);}
	collectA->next = NULL;//collectA->value = 0;
	createRadixList(A,collectA,A_length);

	frontrear* ft = new frontrear[radix];	//����ͷβ����
	if(ft == NULL){printf("frontrear* ft malloc fail ... ...\n");Sleep(3000);exit(0);}

	//�����ռ�����
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

//�����鴴������(ͷ�巨)
void createRadixList(ITEMTYPE* A,radixList* collectA,int A_length){
	for(int i=0;i<=A_length-1;i++){
		radixNode* newnode = new radixNode;
		newnode->value = A[i];
		newnode->next = collectA->next;
		collectA->next = newnode;
	}
}

//һ�Σ��൱��һ��keynum���ַ���������Ԫ�ص���Ӧ���������㣬ͷ�����ʵ������
void radixDistribute(radixList* collectA,int keynum,frontrear* ft,int radix){
	// ft[i].front �� ft[i].rear �ֱ�ָ���i��������ĵ�һ�������һ����㣬��ÿ�γ�ʼ���������ÿգ�����
	for(int i=0;i<=radix-1;i++){
		ft[i].front=NULL;
		ft[i].rear=NULL;
	}
	ITEMTYPE digit;
	radixNode* pos;
	while(collectA->next != NULL){
		// ȡ��ԭʼ�������е����ݽ��
		pos = collectA->next;
		collectA->next = pos->next;	//ͷ��㲻��
		pos->next = NULL;
		//����ȡ���Ľ����뵽��Ӧ��������
		digit = getdigit(pos->value,keynum);
		if(ft[digit].front != NULL){
			ft[digit].rear->next = pos;
			ft[digit].rear = pos;	//�޸�βָ��
		}
		else{
			ft[digit].front = pos;			
			ft[digit].rear  = pos;
		}
	}
}

//�ռ��������еĽ�㵽����collectA��
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

//���ź��������д��ԭʼ������
void listToArray(ITEMTYPE_POINTER A,radixList* collectA){
	int i=0;
	radixNode* pos = collectA->next;
	while(pos){
		A[i++] = pos->value;
		pos = pos->next;
	}
}

//�ͷ�����ռ�
void deleteList(radixList* collectA){
	radixNode* pos = collectA;
	while(pos){
		collectA = pos->next;
		delete(pos);
		pos = collectA;
	}
}

//show collectAչʾԭʼ����
void showCollect(radixList* collectA){
	radixNode* pos = collectA->next;
	while(pos){
		printf("%d ",pos->value);
		pos = pos->next;
	}
	printf("\n");
}

//show ftչʾ������
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
