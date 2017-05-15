#include "myDataStructDefine.h"
#define ITEMTYPE int
//定义二叉树结点
typedef struct node{
	struct node* p;		//parent
	struct node* left,* right;
	ITEMTYPE key;
}bstnode;

//遍历二叉树（中序遍历递归算法）
void recInorderWalk(bstnode* bst);
//遍历二叉树（中序遍历非递归算法(bstMinimum和bstSuccessor实现)）
void inorderWalk(bstnode* bst);


//迭代查找
bstnode* iterativeBstSearch(bstnode* bst,ITEMTYPE k);
//递归查找
bstnode* bstSearch(bstnode*& bst,ITEMTYPE k);
bstnode* bstSearch(bstnode*& bst,bstnode* z);

//查找最小关键字
bstnode* bstMinimum(bstnode* bstNodeP);
//查找最小关键字(递归算法)
bstnode* recBstMinimum(bstnode* bstNodeP);
//查找最大关键字
bstnode* bstMaximum(bstnode* bstNodeP);

//查找后继
bstnode* bstSuccessor(bstnode*& bst,ITEMTYPE a);
bstnode* bstSuccessor(bstnode*& bstNode);
//查找前驱
bstnode* bstPredecessor(bstnode*& bst,ITEMTYPE a);
bstnode* bstPredecessor(bstnode*& bstNode);


//插入结点
void bstInsert(bstnode*& bst,bstnode* z);
//插入ITEMTYPE
void bstInsert(bstnode*& bst,ITEMTYPE a);
//插入（递归算法）
void recBstInsert2(bstnode*& bst,ITEMTYPE a);
void recBstInsert2(bstnode*& bst,bstnode*& z);
//插入（递归算法2）
void recBstInsert(bstnode*& bst,bstnode*& zp,ITEMTYPE a);
void recBstInsert(bstnode*& bst,bstnode*& zp,bstnode*& z);


//删除
void bstDelete(bstnode*& bst,ITEMTYPE a);
void bstDelete(bstnode*& bst,bstnode*& z);
//移植for删除操作
void transplant(bstnode*& bstNode,bstnode*& u,bstnode*& v);


//构建平衡二叉树(从数组A)
bstnode* buildBST(ITEMTYPE* A,int A_length);

//for BSTTree test
void bstTest(bstnode* bst,ITEMTYPE *A);
//先序遍历二叉树
void  DotOrder(bstnode*& root, FILE *fp);
//建立二叉树bst.gv文件
void MakeDot(bstnode* root);
