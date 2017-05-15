#include "myDataStructDefine.h"
#define ITEMTYPE int
//������������
typedef struct node{
	struct node* p;		//parent
	struct node* left,* right;
	ITEMTYPE key;
}bstnode;

//��������������������ݹ��㷨��
void recInorderWalk(bstnode* bst);
//��������������������ǵݹ��㷨(bstMinimum��bstSuccessorʵ��)��
void inorderWalk(bstnode* bst);


//��������
bstnode* iterativeBstSearch(bstnode* bst,ITEMTYPE k);
//�ݹ����
bstnode* bstSearch(bstnode*& bst,ITEMTYPE k);
bstnode* bstSearch(bstnode*& bst,bstnode* z);

//������С�ؼ���
bstnode* bstMinimum(bstnode* bstNodeP);
//������С�ؼ���(�ݹ��㷨)
bstnode* recBstMinimum(bstnode* bstNodeP);
//�������ؼ���
bstnode* bstMaximum(bstnode* bstNodeP);

//���Һ��
bstnode* bstSuccessor(bstnode*& bst,ITEMTYPE a);
bstnode* bstSuccessor(bstnode*& bstNode);
//����ǰ��
bstnode* bstPredecessor(bstnode*& bst,ITEMTYPE a);
bstnode* bstPredecessor(bstnode*& bstNode);


//������
void bstInsert(bstnode*& bst,bstnode* z);
//����ITEMTYPE
void bstInsert(bstnode*& bst,ITEMTYPE a);
//���루�ݹ��㷨��
void recBstInsert2(bstnode*& bst,ITEMTYPE a);
void recBstInsert2(bstnode*& bst,bstnode*& z);
//���루�ݹ��㷨2��
void recBstInsert(bstnode*& bst,bstnode*& zp,ITEMTYPE a);
void recBstInsert(bstnode*& bst,bstnode*& zp,bstnode*& z);


//ɾ��
void bstDelete(bstnode*& bst,ITEMTYPE a);
void bstDelete(bstnode*& bst,bstnode*& z);
//��ֲforɾ������
void transplant(bstnode*& bstNode,bstnode*& u,bstnode*& v);


//����ƽ�������(������A)
bstnode* buildBST(ITEMTYPE* A,int A_length);

//for BSTTree test
void bstTest(bstnode* bst,ITEMTYPE *A);
//�������������
void  DotOrder(bstnode*& root, FILE *fp);
//����������bst.gv�ļ�
void MakeDot(bstnode* root);
