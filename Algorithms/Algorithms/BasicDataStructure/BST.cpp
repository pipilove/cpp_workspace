///*	二叉搜索树	2013.12.1	皮皮	*/
#include "BST.h"

//遍历二叉树（中序遍历递归算法）
void recInorderWalk(bstnode *bst){
	bstnode *tp = bst;
	if(tp != NULL){
		recInorderWalk(tp->left);
		printf("%d ",tp->key);
		recInorderWalk(tp->right);
	}
}
//遍历二叉树（中序遍历非递归算法(bstMinimum和bstSuccessor实现)）
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

//迭代查找
bstnode* iterativeBstSearch(bstnode* bst,ITEMTYPE k){
	bstnode* bstNode= bst;
	while(bstNode != NULL && bstNode->key != k){
		if(bstNode->key > k) bstNode = bstNode->left;
		else bstNode = bstNode->right;
	}
	return bstNode;
}
//递归查找
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

//查找最小关键字
bstnode* bstMinimum(bstnode* bstNodeP){
	if(bstNodeP == NULL)	return NULL;
	bstnode *tp = bstNodeP;		//不改变指针bst,栈中的bstNodeP本来就不会改变？
	while(tp->left != NULL)
		tp = tp->left;
	return tp;		//返回*tp则用bstMinimum.key访问key，否则用bstMinimum->key访问key
}
//查找最小关键字(递归算法)
bstnode* recBstMinimum(bstnode* bstNodeP){
	if(bstNodeP == NULL)	return NULL;
	bstnode *tp = bstNodeP;
	if(tp->left == NULL) return tp;
	return recBstMinimum(tp->left);
}
//查找最大关键字
bstnode* bstMaximum(bstnode* bstNodeP){
	if(bstNodeP == NULL)	return NULL;
	bstnode *tp = bstNodeP;
	while(tp->right != NULL)
		tp = tp->right;
	return tp;
}

//查找后继
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
	while(bstp != NULL && bstNode != bstp->left){	//顺序不能反！否则访问冲突
		bstNode = bstp;
		bstp = bstp->p;
	}
	return bstp;
}
//查找前驱
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


//插入结点
void bstInsert(bstnode*& bst,bstnode* z){	//而bstnode* z 和bstnode*& z没有赋值修改
	if(bst == NULL) bst = z;//对bst进行赋值修改，没有&则每次都是栈里面的 bst = z，清栈后赋值无效
	else{
		bstnode* tempz = bst;
		bstnode* zp = NULL;
		while(tempz != NULL){
			zp = tempz;
			if(tempz->key > z->key)
				tempz = tempz->left;
			else if(tempz->key < z->key)
				tempz = tempz->right;		//大于(等于)都插入右边
			else
				return;
		}
		z->p = zp;
		if(zp->key > z->key) zp->left = z;
		else zp->right = z;
	}
}
//插入ITEMTYPE
void bstInsert(bstnode*& bst,ITEMTYPE a){
	bstnode* newNodeP = new bstnode;
	newNodeP->key = a;
	newNodeP->left = newNodeP->right = newNodeP->p = NULL;
	bstInsert(bst,newNodeP);
}
//插入（递归算法）
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
//插入（递归算法2）
void recBstInsert(bstnode*& bst,bstnode*& zp,ITEMTYPE a){
	bstnode* newNodeP = new bstnode;
	newNodeP->key = a;
	newNodeP->left = newNodeP->right = newNodeP->p = NULL;
	recBstInsert(bst,zp,newNodeP);
}
void recBstInsert(bstnode*& bst,bstnode*& zp,bstnode*& z){		//第一次调用前 zp = bst;
	if(zp == NULL) {zp = z;return;}
	z->p = zp;
	if(bst == NULL){
		if(zp->key > z->key) zp->left = z;
		else zp->right = z;
	}
	else if(bst->key > z->key) recBstInsert(bst->left,bst,z);
	else recBstInsert(bst->right,bst,z);
}


//删除
void bstDelete(bstnode*& bst,ITEMTYPE a){
	bstnode* nodeP = bstSearch(bst,a);
	if(nodeP == NULL){
		printf("delete error!!! the bst is NULL or the bstnode doesn't exit...\n");
		Sleep(1000);return;}
	bstDelete(bst,nodeP);
}
void bstDelete(bstnode*& bst,bstnode*& z){
	if(bstSearch(bst,z) == NULL){		//直接调用此函数时,先要查找此结点指针是否属于该bst
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
//移植for删除操作
void transplant(bstnode*& bstNode,bstnode*& u,bstnode*& v){
	if(u->p == NULL) bstNode = v;		//v移植到树根上
	else if(u == u->p->left)	u->p->left = v;
	else u->p->right = v;
	if(v != NULL)	v->p = u->p;
}


//构建平衡二叉树(从数组A)
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
//先序遍历二叉树
void  DotOrder(bstnode*& root, FILE *fp){ /*先序遍历二叉树*/
	if(root==NULL)	return;
	if(root->left)
		fprintf(fp,"%d -> %d ;\n",root->key,root->left->key);
	if(root->right)
		fprintf(fp,"%d -> %d ;\n",root->key,root->right->key);
	DotOrder(root->left,fp);
	DotOrder(root->right,fp);	
}
//建立二叉树bst.gv文件
void MakeDot(bstnode* root){
	FILE *fp=fopen("bst.gv","w+");
	fprintf(fp,"digraph BST {\n");
	DotOrder(root,fp);
	fprintf(fp,"}\n\n");
	fclose(fp);
}
