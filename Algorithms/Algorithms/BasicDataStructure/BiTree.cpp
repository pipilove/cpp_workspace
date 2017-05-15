/****************************************************************************/
/*	 ���ݽṹ���㷨chap3 ���� ������			ƤƤ 2014-7-6					*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#define ITEMTYPE char

typedef struct binode{
	struct binode *lchild, *rchild;
	ITEMTYPE item;
}node;

static void preInOrd(ITEMTYPE* preord, ITEMTYPE* inord, int i, int j, int k, int h, node* & t);
static void createBiTree(ITEMTYPE* preord, ITEMTYPE* inord, int nodeNum, node* & root);
static void preOrder(node* root);
static void inOrder(node* root);
static void NRInorder(node *root);
static void NRInorder2(node *root);
static void postOrder(node* root);
static int biTreeDeepth(node *root);
static void levelOrder(node *root);

int __21515415main(){
	ITEMTYPE preord[20] = "ABCDEFG";
	ITEMTYPE inord[20] = "CBDAEGF";
	/*			A
		B				E
	C		D				F
						G		
	*/
	node * root;// = (node*)malloc(sizeof(node)); ��������
	createBiTree(preord, inord, strlen(preord), root);	//node* &�ǲ��ó�ʼ���ģ�node*Ҫ

	printf("���������\n");								//��������ı�root�Ͷ�����
	preOrder(root); 
	printf("\n���������\n");
	inOrder(root);
	printf("\n����ǵݹ������\n");
	NRInorder(root);
	printf("\n����ǵݹ����2��\n");
	NRInorder2(root);
	printf("\n���������\n");
	postOrder(root);

	printf("\n��α�����\n");
	levelOrder(root);
	printf("\n\n");

	system("pause");
	return 0;
}

/*	���ʽ��	*/
void visit(node* inode){
	printf("%c", inode->item);
}

/*	�������д�i - j, �������д�k - h, ����һ������������t��	*/
void preInOrd(ITEMTYPE* preord, ITEMTYPE* inord, int i, int j, int k, int h, node* & t){
	/*	�������д�i - j, �������д�k - h, ����һ������������t��	*/
	int m;

	/*	�������ĸ�	*/
	t = (node*)malloc(sizeof(node));
	t->item = preord[i];

	m = k;
	while( inord[m] != preord[i] )	//�ҵ����������и�λ��
		m++;

	/*	�ݹ���ý���������	*/
	if( m == k)						//������Ϊ��
		t->lchild = NULL;
	else
		preInOrd(preord, inord, i + 1, i + m - k, k, m - 1, t->lchild);

	/*	�ݹ���ý���������	*/
	if( m == h )
		t->rchild = NULL;
	else
		preInOrd(preord, inord, i + m - k + 1, j, m + 1, h, t->rchild);
}
/*	nodeNumΪ������������, ����һ������������t��	*/
void createBiTree(ITEMTYPE* preord, ITEMTYPE* inord, int nodeNum, node* & root){
	/*	nodeNumΪ������������, ����һ������������t��	*/
	if(nodeNum <= 0)
		root = NULL;
	else
		preInOrd(preord, inord, 0, nodeNum - 1, 0, nodeNum - 1, root);//strlen(preord) - 1 
}

/*	���ݹ飩�������DLR	*/
void preOrder(node* root){
	if(root){
		visit(root);
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
}
/*	���ݹ飩�������LDR	*/
void inOrder(node* root){
	if(root){
		inOrder(root->lchild);
		visit(root);
		inOrder(root->rchild);
	}
}
/*	���ݹ飩�������LRD	*/
void postOrder(node* root){
	if(root){
		postOrder(root->lchild);
		postOrder(root->rchild);
		visit(root);
	}
}

/*	����������(��1��ʼ)	*/
int biTreeDeepth(node *root){
	if(root){
		int lDeepth = biTreeDeepth(root->lchild);
		int rDeepth = biTreeDeepth(root->rchild);
		return 1 + ( lDeepth > rDeepth? lDeepth:rDeepth );
	}
	return 0;
}
/*	��������α���������ʵ�֣�	*/
void levelOrder(node *root){
	if(root){														//�ն�����ֱ�ӷ���
		int treeDeepth = biTreeDeepth(root);
		int maxNode = (int)pow((double)2, (double)treeDeepth- 1);	//����Ϊ treeDeepthn ʱ�� ���һ������� 2^(treeDeepthn-1)�����
		node* queue = (node*)malloc(sizeof(node) * maxNode);		//�����α�������
		int head = -1, tail = 0;
		queue[tail] = *root;										//��ʼ���������

		while(head != tail){										//���зǿ�
			visit(&queue[++head]);									//��ͷ���ӷ���
			if( queue[head].lchild )								//�����ӣ��������
				queue[++tail] = *queue[head].lchild;
			if( queue[head].rchild )
				queue[++tail] = *queue[head].rchild;
		}
	}
}

/*	�������ǵݹ��������	*/
void NRInorder(node *root){
	if(root){
		int treeDeepth = biTreeDeepth(root);	//ջ������ΪtreeDeepth������treeDeepth���ռ��С
		node **biTreeStack = (node**)malloc(sizeof(node) * treeDeepth);
		for(int i = 0; i < treeDeepth; i++)
			biTreeStack[i] = (node*)malloc(sizeof(node));
		node *p = root;

		int head = -1;
		while( p || head != -1){
			if( p ){							//����������
				biTreeStack[++head] = p;
				//printf("  %d  ", head);
				p = p->lchild;
			}else{								//���ʸ���㣬����������
				p = biTreeStack[head]->rchild;
				visit( biTreeStack[head--] );
			}
		}
	}
}
/*	�������ǵݹ��������2	*/
void NRInorder2(node *root){
	if(root){
		int treeDeepth = biTreeDeepth(root);	//ջ������ΪtreeDeepth������treeDeepth���ռ��С
		node **biTreeStack = (node**)malloc(sizeof(node) * treeDeepth);
		for(int i = 0; i < treeDeepth; i++)
			biTreeStack[i] = (node*)malloc(sizeof(node));
		node *p = root;

		int head = -1;
		biTreeStack[++head] = p;				//��ָ����ջ
		while( head != -1 ){					//ջ�ǿ�
			p = biTreeStack[head];				//GetTop(S, p);
			while( p ){
				biTreeStack[++head] = p->lchild;//Push(S, p->lchild);
				p = p->lchild;
			}
			head--;								//��ָ����ջ(p�����Һ���)

			if( head != -1){
				p = biTreeStack[head--];		//Pop(S, p);
				visit( p );
				biTreeStack[++head] = p->rchild;//Push(S, p->rchild);
			}
		}
	}
}

