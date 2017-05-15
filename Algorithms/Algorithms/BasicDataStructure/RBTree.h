///*	red-black tree	2013.12.19	ƤƤ		*/
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
	rbtnode* nil;		//�ڱ���㣨Ҷ��㣩
	rbtnode* root;		//�����

	//���캯��,��ʼ��root��nil
	RB_Tree(){
		nil = new rbtnode();
		//root = nil;	//���
		nil->left = nil->right  = root;
		nil->p = root;		//��ʼ��ʱ����Ϊroot������root����ʱroot->p->color����ʳ�ͻ
		nil->color = black;	//������Ϊarbitrary
		root = nil;	//��ʼ��rootΪnil
	}
	//��������
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
	//����ת����
	void leftRotate(rbtnode* rbt_node);
	//����ת����
	void rightRotate(rbtnode* x);
	//��ֲ����
	void rbtTransplant(rbtnode* u,rbtnode* v);


	//���Ҳ���
	rbtnode* rbtSearch(ITEMTYPE a);
	//����rbt_node������Сkey���
	rbtnode *rbtMinimum(rbtnode *rbt_node);

	//���������ʼ��key��rbtnode
	void rbtInsert(rbtnode *rbt_node);
	//���ֺ������
	void rbtInsertFixup(rbtnode *rbt_node);
	//����ITEM
	void rbtInsert(ITEMTYPE a);

	//ɾ��node
	void rbtDelete(ITEMTYPE a);
	void rbtDelete(rbtnode *rbt_node);
	//���ֺ������
	void rbtDeleteFixup(rbtnode *x);

	//���������
	void buildRBT(ITEMTYPE *A,int A_length);
	//����rbti.gv�ļ���filename
	string addInt2Filename(int i);

	//���������������ݹ������
	void recInorderWalk(rbtnode* root);

	
	//�������������������
	void fprintfRbtnode(rbtnode *rbt_node,FILE *fp);
	//������������
	void  rbtDotOrder(rbtnode *root,FILE *fp);
	//���������filename.gv�ļ�����������λ������rbtMakeDot("rbt.gv");
	void rbtMakeDot(const char *filename);


	//����
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
