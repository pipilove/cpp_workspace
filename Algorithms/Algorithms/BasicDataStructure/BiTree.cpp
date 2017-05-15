/****************************************************************************/
/*	 数据结构与算法chap3 —— 二叉树			皮皮 2014-7-6					*/
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
	node * root;// = (node*)malloc(sizeof(node)); 二叉树根
	createBiTree(preord, inord, strlen(preord), root);	//node* &是不用初始化的，node*要

	printf("先序遍历：\n");								//遍历不会改变root和二叉树
	preOrder(root); 
	printf("\n中序遍历：\n");
	inOrder(root);
	printf("\n中序非递归遍历：\n");
	NRInorder(root);
	printf("\n中序非递归遍历2：\n");
	NRInorder2(root);
	printf("\n后序遍历：\n");
	postOrder(root);

	printf("\n层次遍历：\n");
	levelOrder(root);
	printf("\n\n");

	system("pause");
	return 0;
}

/*	访问结点	*/
void visit(node* inode){
	printf("%c", inode->item);
}

/*	先序序列从i - j, 中序序列从k - h, 建立一个二叉树放在t中	*/
void preInOrd(ITEMTYPE* preord, ITEMTYPE* inord, int i, int j, int k, int h, node* & t){
	/*	先序序列从i - j, 中序序列从k - h, 建立一个二叉树放在t中	*/
	int m;

	/*	二叉树的根	*/
	t = (node*)malloc(sizeof(node));
	t->item = preord[i];

	m = k;
	while( inord[m] != preord[i] )	//找到中序序列中根位置
		m++;

	/*	递归调用建立左子树	*/
	if( m == k)						//左子树为空
		t->lchild = NULL;
	else
		preInOrd(preord, inord, i + 1, i + m - k, k, m - 1, t->lchild);

	/*	递归调用建立右子树	*/
	if( m == h )
		t->rchild = NULL;
	else
		preInOrd(preord, inord, i + m - k + 1, j, m + 1, h, t->rchild);
}
/*	nodeNum为二叉树结点个数, 建立一个二叉树放在t中	*/
void createBiTree(ITEMTYPE* preord, ITEMTYPE* inord, int nodeNum, node* & root){
	/*	nodeNum为二叉树结点个数, 建立一个二叉树放在t中	*/
	if(nodeNum <= 0)
		root = NULL;
	else
		preInOrd(preord, inord, 0, nodeNum - 1, 0, nodeNum - 1, root);//strlen(preord) - 1 
}

/*	（递归）先序遍历DLR	*/
void preOrder(node* root){
	if(root){
		visit(root);
		preOrder(root->lchild);
		preOrder(root->rchild);
	}
}
/*	（递归）中序遍历LDR	*/
void inOrder(node* root){
	if(root){
		inOrder(root->lchild);
		visit(root);
		inOrder(root->rchild);
	}
}
/*	（递归）后序遍历LRD	*/
void postOrder(node* root){
	if(root){
		postOrder(root->lchild);
		postOrder(root->rchild);
		visit(root);
	}
}

/*	求二叉树深度(从1开始)	*/
int biTreeDeepth(node *root){
	if(root){
		int lDeepth = biTreeDeepth(root->lchild);
		int rDeepth = biTreeDeepth(root->rchild);
		return 1 + ( lDeepth > rDeepth? lDeepth:rDeepth );
	}
	return 0;
}
/*	二叉树层次遍历（队列实现）	*/
void levelOrder(node *root){
	if(root){														//空二叉树直接返回
		int treeDeepth = biTreeDeepth(root);
		int maxNode = (int)pow((double)2, (double)treeDeepth- 1);	//树高为 treeDeepthn 时， 最后一层最多有 2^(treeDeepthn-1)个结点
		node* queue = (node*)malloc(sizeof(node) * maxNode);		//定义层次遍历队列
		int head = -1, tail = 0;
		queue[tail] = *root;										//初始根结点入列

		while(head != tail){										//队列非空
			visit(&queue[++head]);									//队头出队访问
			if( queue[head].lchild )								//有左孩子，左孩子入队
				queue[++tail] = *queue[head].lchild;
			if( queue[head].rchild )
				queue[++tail] = *queue[head].rchild;
		}
	}
}

/*	二叉树非递归中序遍历	*/
void NRInorder(node *root){
	if(root){
		int treeDeepth = biTreeDeepth(root);	//栈最大深度为treeDeepth，分配treeDeepth个空间大小
		node **biTreeStack = (node**)malloc(sizeof(node) * treeDeepth);
		for(int i = 0; i < treeDeepth; i++)
			biTreeStack[i] = (node*)malloc(sizeof(node));
		node *p = root;

		int head = -1;
		while( p || head != -1){
			if( p ){							//遍历左子树
				biTreeStack[++head] = p;
				//printf("  %d  ", head);
				p = p->lchild;
			}else{								//访问根结点，遍历右子树
				p = biTreeStack[head]->rchild;
				visit( biTreeStack[head--] );
			}
		}
	}
}
/*	二叉树非递归中序遍历2	*/
void NRInorder2(node *root){
	if(root){
		int treeDeepth = biTreeDeepth(root);	//栈最大深度为treeDeepth，分配treeDeepth个空间大小
		node **biTreeStack = (node**)malloc(sizeof(node) * treeDeepth);
		for(int i = 0; i < treeDeepth; i++)
			biTreeStack[i] = (node*)malloc(sizeof(node));
		node *p = root;

		int head = -1;
		biTreeStack[++head] = p;				//根指针入栈
		while( head != -1 ){					//栈非空
			p = biTreeStack[head];				//GetTop(S, p);
			while( p ){
				biTreeStack[++head] = p->lchild;//Push(S, p->lchild);
				p = p->lchild;
			}
			head--;								//空指针退栈(p的左右孩子)

			if( head != -1){
				p = biTreeStack[head--];		//Pop(S, p);
				visit( p );
				biTreeStack[++head] = p->rchild;//Push(S, p->rchild);
			}
		}
	}
}

