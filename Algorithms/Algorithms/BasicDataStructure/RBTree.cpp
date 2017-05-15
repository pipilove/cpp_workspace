// *red-black tree	2013.12.19	皮皮*/
#include "RBTree.h"
const int LEN  = 20;	//定义要测试的数组的大小
const int LOWER= 1 ;	//定义要测试的数组的最小值
const int UPPER= 100;	//定义要测试的数组的最大值

//左旋转操作
void RB_Tree::leftRotate(rbtnode* x){		//自动传入RBTree的this指针
	rbtnode* y = x->right;
	if(y->left != nil)
		y->left->p = x;	//判断语句可以少，nil的parent可以任意？
	x->right = y->left;

	rbtTransplant(x,y);

	y->left = x;
	x->p = y;
}

//右旋转操作
void RB_Tree::rightRotate(rbtnode* x){
	rbtnode* y = x->left;
	x->left = y->right;
	if(y->right != nil) y->right->p = x;
	rbtTransplant(x,y);
	y->right = x;
	x->p = y;
}

//移植操作（将v移植到u）
void RB_Tree::rbtTransplant(rbtnode* u,rbtnode* v){
	v->p = u->p;
	if(u->p == nil)
		root = v;
	else if(u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
}

//查找操作
RB_Tree::rbtnode *RB_Tree::rbtSearch(ITEMTYPE a){		//rbtnode也要RB_Tree::声明
	rbtnode* rbta = root;
	while(rbta != nil && rbta->key!=a){
		if(rbta->key >a) rbta = rbta->left;
		else rbta = rbta->right;
	}
	return rbta;
}
//查找rbt_node子树最小key结点
RB_Tree::rbtnode *RB_Tree::rbtMinimum(rbtnode *rbt_node){
	if(rbt_node == nil)
		return nil;
	while(rbt_node->left != nil)
		rbt_node = rbt_node->left;
	return rbt_node;
}

//--------------------------插入结点操作----------------------------------  
	//伪代码：  
	/*RB-INSERT(T, z)    
	1  y ← nil[T]						// y 始终指向 x 的父结点。 
	2  x ← root[T]						// x 指向当前树的根结点， 
	3  while x ≠ nil[T] 
	4      do y ← x 
	5         if key[z] < key[x]
	6            then x ← left[x] 
	7            else x ← right[x]
	8  p[z] ← y							//插入结点z 的父结点置为y 
	9  if y = nil[T] 
	10     then root[T] ← z 
	11     else if key[z] < key[y] 
	12             then left[y] ← z 
	13             else right[y] ← z   //此 8-13行，置z 相关的指针。 
	14  left[z] ← nil[T] 
	15  right[z] ← nil[T]				//设为空
	16  color[z] ← RED					//将新插入的结点z作为红色 
	17  RB-INSERT-FIXUP(T, z)    
	*/  
	//将z着为红色，可能会违反某一红黑性质，需要调用rbtInsertFixup保持红黑性质 
//插入仅仅初始化key的rbtnode
void RB_Tree::rbtInsert(rbtnode *rbt_node){
	rbtnode* tempz = root;
	rbtnode* zp = nil;
	while(tempz != nil){
		zp = tempz;
		if(tempz->key > rbt_node->key)
			tempz = tempz->left;
		else if(tempz->key < rbt_node->key)
			tempz = tempz->right;
		else
			return;						//这里去掉了相等的key
	}
	rbt_node->p = zp;
	if(zp == nil)
		root = rbt_node;
	else if(zp->key > rbt_node->key)
		zp->left = rbt_node;
	else
		zp->right = rbt_node;
	rbt_node->left = nil;
	rbt_node->right = nil;
	rbt_node->color = red;				//每次插入都必须是红色结点
	rbtInsertFixup(rbt_node);			//每次插入都要维护红黑性质
}
//---------------------插入结点性质修复--------------------------------  
//3种插入情况，伪代码中(未涉及到所有全部的插入情况) 
/* 
RB-INSERT-FIXUP(T, z) 
1 while color[p[z]] = RED 
2     do if p[z] = left[p[p[z]]] 
3           then y ← right[p[p[z]]] 
4                if color[y] = RED 
5                   then color[p[z]] ← BLACK                    // Case 1 
6                        color[y] ← BLACK                       // Case 1 
7                        color[p[p[z]]] ← RED                   // Case 1 
8                        z ← p[p[z]]                            // Case 1 
9                   else if z = right[p[z]] 					 
10                           then z ← p[z]                      // Case 2 
11                                LEFT-ROTATE(T, z)              //	Case 2 
12                           color[p[z]] ← BLACK                // Case 3 
13                           color[p[p[z]]] ← RED               // Case 3 
14                           RIGHT-ROTATE(T, p[p[z]])            //	Case 3 
15           else (same as then clause with "right" and "left" exchanged) 
16 color[root[T]] ← BLACK 
*/
//保持红黑性质
void RB_Tree::rbtInsertFixup(rbtnode* z){
	rbtnode *y;
	while(z->p->color == red){		//修复性质4
		if(z->p == z->p->p->left){	//y为z->p->p的右孩子
			y = z->p->p->right;
			if(y->color == red){		//case 1
				z->p->color = black;
				z->p->p->color = red;
				y->color = black;
				z = z->p->p;
			}
			else if(z == z->p->right){	//case 2
				z = z->p;
				leftRotate(z);
			}
			else{						//case 3，不要esle???
				z->p->color = black;	//循环结束
				z->p->p->color = red;
				rightRotate(z->p->p);
			}
		}
		else{							//y为z->p->p的左孩子
			y = z->p->p->left;
			if(y->color == red){		//case 1
				z->p->color = black;
				z->p->p->color = red;
				y->color = black;
				z = z->p->p;
			}
			else if(z == z->p->left){	//case 2
				z = z->p;
				rightRotate(z);
			}
			else{						//case 3
				z->p->color = black;
				z->p->p->color = red;
				leftRotate(z->p->p);
			}
		}
	}
	this->root->color = black;			//可能修复性质2
}
//插入ITEM
void RB_Tree::rbtInsert(ITEMTYPE a){
	rbtnode *rbt_node = new rbtnode();
	rbt_node->key = a;
	rbtInsert(rbt_node);
}


//删除node
void RB_Tree::rbtDelete(ITEMTYPE a){
	rbtnode *z = rbtSearch(a);
	if(z == nil){
		printf("\ndelete error!!! the rbt is nil or the rbtnode doesn't exit...\n");
		Sleep(1000);return;}
	rbtDelete(z);
}
void RB_Tree::rbtDelete(rbtnode *z){
	rbtnode *x;
	rbtnode *y = z;							//用于记录删除结点z
	rbt_color y_original_color = y->color;	//用于记录删除结点z的颜色性质
	if(z->left == nil){
		x = z->right;						//用于记录红黑性质可能遭到破坏的结点
		rbtTransplant(z,z->right);
	}
	else if(z->right == nil){
		x = z->left;
		rbtTransplant(z,z->left);
	}
	else{
		y = rbtMinimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if(y->p == z)
			x->p = y;						//x = nil时需要fixup line4 中x->p不为arbitrary
		else{
			rbtTransplant(y,y->right);		//设置了x->p = y->p,从而不会为arbitrary
			y->right = z->right;
			z->right->p = y;
		}
		rbtTransplant(z,y);
		y->left = z->left;
		y->left->p = y;

		y->color = z->color;				//通过此转移破坏红黑性质的地方到x，即最初y->right
	}
	if(y_original_color == black)			//3种情况都相当于删除的结点颜色为black，需要将x视为双重黑或者红黑进行fixup
		rbtDeleteFixup(x);
}
//---------------------删除结点性质修复-----------------------------------  
//伪代码：  
/* 
RB-DELETE-FIXUP(T, x) 
1 while x ≠ root[T] and color[x] = BLACK 
2     do if x = left[p[x]] 
3           then w ← right[p[x]] 
4                if color[w] = RED 
5                   then color[w] ← BLACK                        ?  Case 1 
6                        color[p[x]] ← RED                       ?  Case 1 
7                        LEFT-ROTATE(T, p[x])                    ?  Case 1 
8                        w ← right[p[x]]                         ?  Case 1 
9                if color[left[w]] = BLACK and color[right[w]] = BLACK 
10                   then color[w] ← RED                          ?  Case 2 
11                        x p[x]                                  ?  Case 2 
12                   else if color[right[w]] = BLACK 
13                           then color[left[w]] ← BLACK          ?  Case 3 
14                                color[w] ← RED                  ?  Case 3 
15                                RIGHT-ROTATE(T, w)              ?  Case 3 
16                                w ← right[p[x]]                 ?  Case 3 
17                         color[w] ← color[p[x]]                 ?  Case 4 
18                         color[p[x]] ← BLACK                    ?  Case 4 
19                         color[right[w]] ← BLACK                ?  Case 4 
20                         LEFT-ROTATE(T, p[x])                   ?  Case 4 
21                         x ← root[T]                            ?  Case 4 
22        else (same as then clause with "right" and "left" exchanged) 
23 color[x] ← BLACK  
*/  
//删除node
//保持红黑性质
void RB_Tree::rbtDeleteFixup(rbtnode *x){
	rbtnode *w;									//x的兄弟结点
	while(x != root && x->color == black){		//x为红黑时只要转化为黑即完成fixup
		if(x == x->p->left){
			w = x->p->right;
			if(w->color == red){				//case1,转x兄弟颜色为black
				w->color = black;
				x->p->color = red;
				leftRotate(x->p);
				w = x->p->right;
			}
			if(w->left->color == black && w->right->color == black){//case2，双重色上移;w色必为black
				w->color = red;
				x = x->p;
			}
			else if(w->right->color == black){	//case3，转换为case4;w色必为black
				w->color = red;
				w->left->color = black;
				rightRotate(w);
				w = x->p->right;
			}
			else{//else?						//case4,w色必为black
				w->color = w->p->color;			//保证x支路上多出一重黑
				w->p->color = black;
				w->right->color = black;
				leftRotate(w->p);
				x = root;						//设置结束
			}
		}
		else{
			w = x->p->left;
			if(w->color == red){
				w->color = black;
				x->p->color = red;
				rightRotate(x->p);
				w = x->p->left;
			}
			if(w->left->color == black && w->right->color == black){
				w->color = red;
				x = x->p;
			}
			else if(w->left->color == black){
				w->color = red;
				w->right->color = black;
				leftRotate(w);
				w = x->p->right;
			}
			else{
				w->color = w->p->color;
				w->p->color = black;
				w->left->color = black;
				rightRotate(w->p);
				x = root;
			}
		}
	}
	x->color = black;
}

//建立红黑树f(从数组A)
void RB_Tree::buildRBT(ITEMTYPE *A,int A_length){
	FILE *batfile = fopen("rbt.bat","w+");						//w+，close之后才会清空
	fprintf(batfile,"cd /d E:\mine\C++\Algorithms\Algorithms\n");//自动修改batfile路径
	for(int i=0;i<=A_length-1;i++){
		rbtInsert(A[i]);

		fprintf(batfile,"dot -Tpng -orbt%d.png rbt%d.gv\n",i,i);//生成对应.gv文件的png图

		string filename = addInt2Filename(i);
		//rbtMakeDot(filename.c_str());				//创建.gv文件，将string转为c风格字符串char*
	}
	fclose(batfile);
}
//生成rbti.gv文件名filename,有没更好的转化方法？？？
string RB_Tree::addInt2Filename(int i){
	string filename = "rbt";
	char a[10];										//将i(最大为10位数)转为10进制表示的字符串a
	sprintf(a, "%d", i);
	string index(a);								//将a转化为string类
	string extension = ".gv";
	filename = filename + index + extension;
	return filename;
}

//遍历红黑树（中序递归遍历）
void RB_Tree::recInorderWalk(rbtnode* root){
	if(root != nil){
		recInorderWalk(root->left);
		printf("%d ",root->key);
		recInorderWalk(root->right);
	}
}


//输出红黑树单个结点属性
void RB_Tree::fprintfRbtnode(rbtnode *rbt_node,FILE *fp){
	if(rbt_node->color == black)
		fprintf(fp,"node[shape=ellipse,style=filled,color=black,fontcolor=white];\n");
	else
		fprintf(fp,"node[shape=ellipse,style=filled,color=red,fontcolor=white];\n");
	//fprintf(fp,"%d[label=\"<f0> | <f1> %d | <f2> \"];\n",rbt_node->key,rbt_node->key);//在结点上打印label
}
//先序遍历红黑树
void  RB_Tree::rbtDotOrder(rbtnode *rbt_node,FILE *fp){
	if(rbt_node == nil)	return;
	if(rbt_node == root){					//显示root结点
		fprintfRbtnode(rbt_node,fp);
		fprintf(fp,"%d;\n",rbt_node->key);//"%d:<f0>:sw;\n"
	}
	if(rbt_node->left != nil){
		fprintfRbtnode(rbt_node->left,fp);
		fprintf(fp,"%d->%d;\n",rbt_node->key,rbt_node->left->key);//"%d:<f0>:sw->%d:<f1>;\n"
	}
	if(rbt_node->right != nil){
		fprintfRbtnode(rbt_node->right,fp);
		fprintf(fp,"%d->%d;\n",rbt_node->key,rbt_node->right->key);//"%d:<f2>:se->%d:<f1>;\n"
	}
	rbtDotOrder(rbt_node->left,fp);
	rbtDotOrder(rbt_node->right,fp);
}
//建立红黑树filename.gv文件
void RB_Tree::rbtMakeDot(const char *filename){
	FILE *fp=fopen(filename,"w+");
	fprintf(fp,"digraph RBT {\n");
	rbtDotOrder(root,fp);
	fprintf(fp,"}\n\n");
	fclose(fp);
}

//测试
void RB_Tree::rbtTest(){
	string filename = addInt2Filename(1);		//生成测试的rbt1.gv文件
	rbtMakeDot(filename.c_str());
	int a;

	//printf("\nplease input the key you want to delete : \n");
	//scanf("%d",&a);
	//printf("after delete %d...\n",a);
	//rbtDelete(a);
	//recInorderWalk(root);
	//filename = addInt2Filename(2);				//生成测试的rbt2.gv文件
	//rbtMakeDot(filename.c_str());

	//printf("\nplease input the key you want to delete : \n");
	//scanf("%d",&a);
	//printf("after delete %d...\n",a);
	//rbtDelete(a);
	//recInorderWalk(root);
	//filename = addInt2Filename(3);				//生成测试的rbt3.gv文件
	//rbtMakeDot(filename.c_str());

	printf("\nplease input the key you want to insert : \n");
	scanf("%d",&a);
	printf("after insert %d...\n",a);
	rbtInsert(a);
	recInorderWalk(root);
	filename = addInt2Filename(2);				//生成测试的rbt2.gv文件
	rbtMakeDot(filename.c_str());
}


static int dataGenerate(int* A);
static void printfArray(ITEMTYPE* A,int A_length);

int __2151612main(){
	int A[LEN];
	int A_length = dataGenerate(A);				//返回生成数组的长度
	printfArray(A,A_length);
	printf("\n");

	RB_Tree *rbt = new RB_Tree();
	rbt->buildRBT(A,A_length);
	rbt->recInorderWalk(rbt->root);
	rbt->rbtMakeDot("rbt.gv");					//生成最终的rbt图形
	rbt->rbtTest();

	printf("\n");
	system("pause");
	return 0;
}


static void showDatagenerateMode(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("please input the Generation methods that the array need to sort:\n\n");
	printf("1 Randomly generate and save into file in.txt\n");
	printf("2 use the privious data in file in.txt that generate randomly\n");
	printf("3 manually generate and save into file in.txt\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
}
int dataGenerate(int* A){
	int A_length;
	FILE* fp;
	bool input_flag;	//输入正误判断标志
	do{
		showDatagenerateMode();
		input_flag=0;
		int casechoice;
		//scanf("%d",&casechoice);
		while(scanf("%d",&casechoice) == 0){
			fflush(stdin);	//清除输入的非法数据！
			printf("input illegal,please input again ......\n");
		}
		switch(casechoice){
		case 1:{//生成随机数存入in.txt
			if((fp=fopen("in.txt","w"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("the data generates randomly is saving into in.txt ...... ");
			srand((unsigned)time(0));
			for(int k=0;k<LEN;k++){
				//srand(getpid());	//相同元素数组的排序
				A[k]=random(LOWER,UPPER);
				fprintf(fp,"%d ",A[k]);
				//printf("%d ",A[k]);
			}
			A_length = LEN;
			printf("\n");break;}

		case 2:{//从in.txt中取出随机数
			if((fp=fopen("in.txt","r"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("the data gets from in.txt is assign to array A ...... ");
			int k=0;
			while(!feof(fp)){										//A_length不知道的时候呢？？？
				fscanf(fp,"%d ",&A[k++]);
				//printf("%d ",A[k]);
			}
			A_length = k;
			printf("\n");break;}

		case 3:{//手动输入
			if((fp=fopen("in.txt","w"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("please input the data you want to sort(end when the data input is illegal) :\n");
			int k=0;
			while(scanf("%d ",&A[k])){		//以输入一个非法数据结束！！！
				//printf("A[%d] = %d  ",k,A[k]);
				fprintf(fp,"%d ",A[k++]);
			}
			fflush(stdin);	//清除stdin中的非法数据
			A_length = k;
			printf("the data input is saving into in.txt ...... \n");
			Sleep(1000);break;}

		default :
			//fflush(stdin);	//清除输入的非法字符！
			printf("input wrong num,please input again ......\n");
			Sleep(1000);
			input_flag=1;
			system("cls");break;
		}
	}while(input_flag);

	fclose(fp);
	return A_length;
}

void printfArray(ITEMTYPE* A,int A_length){
	printf("array A is :\n");
	for(int i = 0;i<= A_length-1;i++)
		printf("%d ",A[i]);
	printf("\n");
}
