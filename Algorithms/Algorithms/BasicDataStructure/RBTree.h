///*	red-black tree	2013.12.19	皮皮		*/
#include "myDataStructDefine.h"
#define ITEMTYPE int
using namespace std;			//string

class RB_Tree{
private:
	enum rbt_color{red,black};
	//RB_Tree(const RB_Tree& input){}  
	//const RB_Tree& operator=(const RB_Tree& input){}

	
public:
	class rbtnode{
	public:
		rbtnode* p;				// = NULL;
		rbtnode* left,* right;	// = NULL;
		ITEMTYPE key;
		//ITEMTYPE data;
		rbt_color color;
		rbtnode(){
			p = left = right = NULL;
			//color = red;
		}
	};
	rbtnode* nil;		//哨兵结点（叶结点）
	rbtnode* root;		//根结点

	//构造函数,初始化root和nil
	RB_Tree(){
		nil = new rbtnode();
		//root = nil;	//亦可
		nil->left = nil->right  = root;
		nil->p = root;		//初始化时必须为root，否则root调整时root->p->color会访问冲突
		nil->color = black;	//其它可为arbitrary
		root = nil;	//初始化root为nil
	}
	//析构函数
	~RB_Tree(){
		clear(root);
		delete nil;
	}
private:
	// utility function for destructor to destruct object;  
	void clear(rbtnode* rbt_node){  
		if(rbt_node == nil)
			return;
		else{  
			clear(rbt_node->left);
			clear(rbt_node->right);
			delete rbt_node;  
		}  
	} 

public:
	//左旋转操作
	void leftRotate(rbtnode* rbt_node);
	//右旋转操作
	void rightRotate(rbtnode* x);
	//移植操作
	void rbtTransplant(rbtnode* u,rbtnode* v);


	//查找操作
	rbtnode* rbtSearch(ITEMTYPE a);
	//查找rbt_node子树最小key结点
	rbtnode *rbtMinimum(rbtnode *rbt_node);

	//插入仅仅初始化key的rbtnode
	void rbtInsert(rbtnode *rbt_node);
	//保持红黑性质
	void rbtInsertFixup(rbtnode *rbt_node);
	//插入ITEM
	void rbtInsert(ITEMTYPE a);

	//删除node
	void rbtDelete(ITEMTYPE a);
	void rbtDelete(rbtnode *rbt_node);
	//保持红黑性质
	void rbtDeleteFixup(rbtnode *x);

	//建立红黑树
	void buildRBT(ITEMTYPE *A,int A_length);
	//生成rbti.gv文件名filename
	string addInt2Filename(int i);

	//遍历红黑树（中序递归遍历）
	void recInorderWalk(rbtnode* root);

	
	//输出红黑树单个结点属性
	void fprintfRbtnode(rbtnode *rbt_node,FILE *fp);
	//先序遍历红黑树
	void  rbtDotOrder(rbtnode *root,FILE *fp);
	//建立红黑树filename.gv文件，可在任意位置引用rbtMakeDot("rbt.gv");
	void rbtMakeDot(const char *filename);


	//测试
	void rbtTest();


//	//  
//inline RB_Node* InOrderPredecessor(RB_Node* node)  
//{  
//	if(node==m_nullNode)       //null node has no predecessor  
//	{  
//		return m_nullNode;  
//	}  
//	RB_Node* result = node->left;     //get node's left child  
//	while(result!=m_nullNode)         //try to find node's left subtree's right most node  
//	{  
//		if(result->right!=m_nullNode)       
//		{  
//			result = result->right;  
//		}  
//		else  
//		{  
//			break;  
//		}  
//	}            //after while loop result==null or result's right child is null  
//	if(result==m_nullNode)  
//	{  
//		RB_Node* index = node->parent;  
//		result = node;  
//		while(index!=m_nullNode && result == index->left)  
//		{  
//			result = index;  
//			index = index->parent;  
//		}  
//		result = index;         // first right parent or null  
//	}  
//	return result;  
//}  
//
////  
//inline RB_Node* InOrderSuccessor(RB_Node* node)  
//{  
//	if(node==m_nullNode)       //null node has no successor  
//	{  
//		return m_nullNode;  
//	}  
//	RB_Node* result = node->right;   //get node's right node  
//	while(result!=m_nullNode)        //try to find node's right subtree's left most node  
//	{  
//		if(result->left!=m_nullNode)       
//		{  
//			result = result->left;  
//		}  
//		else  
//		{  
//			break;  
//		}  
//	}                              //after while loop result==null or result's left child is null  
//	if(result == m_nullNode)  
//	{  
//		RB_Node* index = node->parent;  
//		result = node;  
//		while(index!=m_nullNode && result == index->right)  
//		{  
//			result = index;  
//			index = index->parent;  
//		}  
//		result = index;         //first parent's left or null  
//	}  
//	return result;  
//}  
};
