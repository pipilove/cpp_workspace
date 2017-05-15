///*	����������	2013.12.1	ƤƤ	*/
#include "BST.h"

//��������������������ݹ��㷨��
void recInorderWalk(bstnode *bst){
	bstnode *tp = bst;
	if(tp != NULL){
		recInorderWalk(tp->left);
		printf("%d ",tp->key);
		recInorderWalk(tp->right);
	}
}
//��������������������ǵݹ��㷨(bstMinimum��bstSuccessorʵ��)��
void inorderWalk(bstnode* bst){
	if(bst == NULL) return;
	bstnode* min = bstMinimum(bst);
	printf("%d ",min->key);
	bstnode* successor = bstSuccessor(min);
	while(successor != NULL){
		printf("%d ",successor->key);
		successor = bstSuccessor(successor);
	}
	printf("\n");
}

//��������
bstnode* iterativeBstSearch(bstnode* bst,ITEMTYPE k){
	bstnode* bstNode= bst;
	while(bstNode != NULL && bstNode->key != k){
		if(bstNode->key > k) bstNode = bstNode->left;
		else bstNode = bstNode->right;
	}
	return bstNode;
}
//�ݹ����
bstnode* bstSearch(bstnode*& bst,ITEMTYPE k){
	bstnode* bstNode = bst;
	if(bstNode == NULL || bstNode->key == k) return bstNode;
	if(bstNode->key > k) return bstSearch(bstNode->left,k);
	return bstSearch(bstNode->right,k);
}
bstnode* bstSearch(bstnode*& bst,bstnode* z){
	bstnode* bstNode = bst;
	if(bstNode == NULL || bstNode == z) return bstNode;
	if(bstNode->key > z->key) return bstSearch(bstNode->left,z);
	return bstSearch(bstNode->right,z);
}

//������С�ؼ���
bstnode* bstMinimum(bstnode* bstNodeP){
	if(bstNodeP == NULL)	return NULL;
	bstnode *tp = bstNodeP;		//���ı�ָ��bst,ջ�е�bstNodeP�����Ͳ���ı䣿
	while(tp->left != NULL)
		tp = tp->left;
	return tp;		//����*tp����bstMinimum.key����key��������bstMinimum->key����key
}
//������С�ؼ���(�ݹ��㷨)
bstnode* recBstMinimum(bstnode* bstNodeP){
	if(bstNodeP == NULL)	return NULL;
	bstnode *tp = bstNodeP;
	if(tp->left == NULL) return tp;
	return recBstMinimum(tp->left);
}
//�������ؼ���
bstnode* bstMaximum(bstnode* bstNodeP){
	if(bstNodeP == NULL)	return NULL;
	bstnode *tp = bstNodeP;
	while(tp->right != NULL)
		tp = tp->right;
	return tp;
}

//���Һ��
bstnode* bstSuccessor(bstnode*& bst,ITEMTYPE a){
	bstnode* nodeP = bstSearch(bst,a);
	if(nodeP == NULL){
		printf("the bst is NULL or the bstnode doesn't exit,can't find its successor...\n");
		Sleep(1000);return NULL;}
	return bstSuccessor(nodeP);
}
bstnode* bstSuccessor(bstnode*& bstNode){
	if(bstNode->right != NULL)
		return bstMinimum(bstNode->right);
	bstnode* bstp = bstNode->p;
	while(bstp != NULL && bstNode != bstp->left){	//˳���ܷ���������ʳ�ͻ
		bstNode = bstp;
		bstp = bstp->p;
	}
	return bstp;
}
//����ǰ��
bstnode* bstPredecessor(bstnode*& bst,ITEMTYPE a){
	bstnode* nodeP = bstSearch(bst,a);
	if(nodeP == NULL){
		printf("the bst is NULL or the bstnode doesn't exit,can't find its predecessor...\n");
		Sleep(1000);return NULL;}
	return bstPredecessor(nodeP);
}
bstnode* bstPredecessor(bstnode*& bstNode){
	if(bstNode->left != NULL)
		return bstMaximum(bstNode->left);
	bstnode* bstp = bstNode->p;
	while(bstp != NULL && bstNode != bstp->right){
		bstNode = bstp;
		bstp = bstp->p;
	}
	return bstp;
}


//������
void bstInsert(bstnode*& bst,bstnode* z){	//��bstnode* z ��bstnode*& zû�и�ֵ�޸�
	if(bst == NULL) bst = z;//��bst���и�ֵ�޸ģ�û��&��ÿ�ζ���ջ����� bst = z����ջ��ֵ��Ч
	else{
		bstnode* tempz = bst;
		bstnode* zp = NULL;
		while(tempz != NULL){
			zp = tempz;
			if(tempz->key > z->key)
				tempz = tempz->left;
			else if(tempz->key < z->key)
				tempz = tempz->right;		//����(����)�������ұ�
			else
				return;
		}
		z->p = zp;
		if(zp->key > z->key) zp->left = z;
		else zp->right = z;
	}
}
//����ITEMTYPE
void bstInsert(bstnode*& bst,ITEMTYPE a){
	bstnode* newNodeP = new bstnode;
	newNodeP->key = a;
	newNodeP->left = newNodeP->right = newNodeP->p = NULL;
	bstInsert(bst,newNodeP);
}
//���루�ݹ��㷨��
void recBstInsert2(bstnode*& bst,ITEMTYPE a){
	bstnode* newNodeP = new bstnode;
	newNodeP->key = a;
	newNodeP->left = newNodeP->right = newNodeP->p = NULL;
	recBstInsert2(bst,newNodeP);
}
void recBstInsert2(bstnode*& bst,bstnode*& z){
	if(bst == NULL) {bst = z;return;}
	z->p = bst;
	if(bst->left == NULL && bst->right == NULL){
		if(bst->key > z->key) bst->left = z;
		else bst->right = z;
	}
	else if(bst->key > z->key) recBstInsert2(bst->left,z);
	else recBstInsert2(bst->right,z);
}
//���루�ݹ��㷨2��
void recBstInsert(bstnode*& bst,bstnode*& zp,ITEMTYPE a){
	bstnode* newNodeP = new bstnode;
	newNodeP->key = a;
	newNodeP->left = newNodeP->right = newNodeP->p = NULL;
	recBstInsert(bst,zp,newNodeP);
}
void recBstInsert(bstnode*& bst,bstnode*& zp,bstnode*& z){		//��һ�ε���ǰ zp = bst;
	if(zp == NULL) {zp = z;return;}
	z->p = zp;
	if(bst == NULL){
		if(zp->key > z->key) zp->left = z;
		else zp->right = z;
	}
	else if(bst->key > z->key) recBstInsert(bst->left,bst,z);
	else recBstInsert(bst->right,bst,z);
}


//ɾ��
void bstDelete(bstnode*& bst,ITEMTYPE a){
	bstnode* nodeP = bstSearch(bst,a);
	if(nodeP == NULL){
		printf("delete error!!! the bst is NULL or the bstnode doesn't exit...\n");
		Sleep(1000);return;}
	bstDelete(bst,nodeP);
}
void bstDelete(bstnode*& bst,bstnode*& z){
	if(bstSearch(bst,z) == NULL){		//ֱ�ӵ��ô˺���ʱ,��Ҫ���Ҵ˽��ָ���Ƿ����ڸ�bst
		printf("delete error!!! the bst is NULL or the bstnode doesn't exit...\n");
		Sleep(1000);return;}
	if(z->left == NULL) transplant(bst,z,z->right);
	else if(z->right == NULL) transplant(bst,z,z->left);
	else{
		bstnode* y = bstMinimum(z->right);
		if(y != z->right){
			transplant(bst,y,y->right);
			y->right = z->right;
			z->right->p = y;
		}
		transplant(bst,z,y);
		z->left->p = y;
		y->left = z->left;
	}
}
//��ֲforɾ������
void transplant(bstnode*& bstNode,bstnode*& u,bstnode*& v){
	if(u->p == NULL) bstNode = v;		//v��ֲ��������
	else if(u == u->p->left)	u->p->left = v;
	else u->p->right = v;
	if(v != NULL)	v->p = u->p;
}


//����ƽ�������(������A)
bstnode* buildBST(ITEMTYPE* A,int A_length){
	bstnode *bst = NULL;
	for(int i = 0;i <= A_length-1;i++)
		bstInsert(bst,A[i]);
	return bst;
}


//for BSTTree test
void bstTest(bstnode* bst,ITEMTYPE *A){
	printf("bstMinimum(bst) = %d\n",bstMinimum(bst)->key);
	//printf("recBstMinimum(bst) = %d\n",recBstMinimum(bst)->key);
	printf("bstMaximum(bst) = %d\n",bstMaximum(bst)->key);
	printf("\n");

	if(bstPredecessor(bst,A[3]) != NULL)
		printf("bstPredecessor(%d) = %d\n",A[3],bstPredecessor(bst,A[3])->key);
	if(bstSuccessor(bst,A[3]) != NULL)
		printf("bstSuccessor(%d) = %d\n",A[3],bstSuccessor(bst,A[3])->key);
	printf("\n");

	recInorderWalk(bst);
	printf("\ninsert 31: \n");
	recBstInsert(bst,bst,31);
	inorderWalk(bst);
	printf("insert 8: \n");
	recBstInsert2(bst,8);
	inorderWalk(bst);
	printf("delete 31: \n");
	bstDelete(bst,31);
	inorderWalk(bst);
	printf("delete %d: \n",bstMinimum(bst)->key);
	bstnode* min = bstMinimum(bst);
	bstDelete(bst,min);
	inorderWalk(bst);
	printf("delete %d: \n",bstMinimum(bst)->key);
	min = bstMinimum(bst);
	bstDelete(bst,min);
	inorderWalk(bst);
}
//�������������
void  DotOrder(bstnode*& root, FILE *fp){ /*�������������*/
	if(root==NULL)	return;
	if(root->left)
		fprintf(fp,"%d -> %d ;\n",root->key,root->left->key);
	if(root->right)
		fprintf(fp,"%d -> %d ;\n",root->key,root->right->key);
	DotOrder(root->left,fp);
	DotOrder(root->right,fp);	
}
//����������bst.gv�ļ�
void MakeDot(bstnode* root){
	FILE *fp=fopen("bst.gv","w+");
	fprintf(fp,"digraph BST {\n");
	DotOrder(root,fp);
	fprintf(fp,"}\n\n");
	fclose(fp);
}
