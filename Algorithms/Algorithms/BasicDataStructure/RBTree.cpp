// *red-black tree	2013.12.19	ƤƤ*/
#include "RBTree.h"
const int LEN  = 20;	//����Ҫ���Ե�����Ĵ�С
const int LOWER= 1 ;	//����Ҫ���Ե��������Сֵ
const int UPPER= 100;	//����Ҫ���Ե���������ֵ

//����ת����
void RB_Tree::leftRotate(rbtnode* x){		//�Զ�����RBTree��thisָ��
	rbtnode* y = x->right;
	if(y->left != nil)
		y->left->p = x;	//�ж��������٣�nil��parent�������⣿
	x->right = y->left;

	rbtTransplant(x,y);

	y->left = x;
	x->p = y;
}

//����ת����
void RB_Tree::rightRotate(rbtnode* x){
	rbtnode* y = x->left;
	x->left = y->right;
	if(y->right != nil) y->right->p = x;
	rbtTransplant(x,y);
	y->right = x;
	x->p = y;
}

//��ֲ��������v��ֲ��u��
void RB_Tree::rbtTransplant(rbtnode* u,rbtnode* v){
	v->p = u->p;
	if(u->p == nil)
		root = v;
	else if(u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
}

//���Ҳ���
RB_Tree::rbtnode *RB_Tree::rbtSearch(ITEMTYPE a){		//rbtnodeҲҪRB_Tree::����
	rbtnode* rbta = root;
	while(rbta != nil && rbta->key!=a){
		if(rbta->key >a) rbta = rbta->left;
		else rbta = rbta->right;
	}
	return rbta;
}
//����rbt_node������Сkey���
RB_Tree::rbtnode *RB_Tree::rbtMinimum(rbtnode *rbt_node){
	if(rbt_node == nil)
		return nil;
	while(rbt_node->left != nil)
		rbt_node = rbt_node->left;
	return rbt_node;
}

//--------------------------���������----------------------------------  
	//α���룺  
	/*RB-INSERT(T, z)    
	1  y �� nil[T]						// y ʼ��ָ�� x �ĸ���㡣 
	2  x �� root[T]						// x ָ��ǰ���ĸ���㣬 
	3  while x �� nil[T] 
	4      do y �� x 
	5         if key[z] < key[x]
	6            then x �� left[x] 
	7            else x �� right[x]
	8  p[z] �� y							//������z �ĸ������Ϊy 
	9  if y = nil[T] 
	10     then root[T] �� z 
	11     else if key[z] < key[y] 
	12             then left[y] �� z 
	13             else right[y] �� z   //�� 8-13�У���z ��ص�ָ�롣 
	14  left[z] �� nil[T] 
	15  right[z] �� nil[T]				//��Ϊ��
	16  color[z] �� RED					//���²���Ľ��z��Ϊ��ɫ 
	17  RB-INSERT-FIXUP(T, z)    
	*/  
	//��z��Ϊ��ɫ�����ܻ�Υ��ĳһ������ʣ���Ҫ����rbtInsertFixup���ֺ������ 
//���������ʼ��key��rbtnode
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
			return;						//����ȥ������ȵ�key
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
	rbt_node->color = red;				//ÿ�β��붼�����Ǻ�ɫ���
	rbtInsertFixup(rbt_node);			//ÿ�β��붼Ҫά���������
}
//---------------------�����������޸�--------------------------------  
//3�ֲ��������α������(δ�漰������ȫ���Ĳ������) 
/* 
RB-INSERT-FIXUP(T, z) 
1 while color[p[z]] = RED 
2     do if p[z] = left[p[p[z]]] 
3           then y �� right[p[p[z]]] 
4                if color[y] = RED 
5                   then color[p[z]] �� BLACK                    // Case 1 
6                        color[y] �� BLACK                       // Case 1 
7                        color[p[p[z]]] �� RED                   // Case 1 
8                        z �� p[p[z]]                            // Case 1 
9                   else if z = right[p[z]] 					 
10                           then z �� p[z]                      // Case 2 
11                                LEFT-ROTATE(T, z)              //	Case 2 
12                           color[p[z]] �� BLACK                // Case 3 
13                           color[p[p[z]]] �� RED               // Case 3 
14                           RIGHT-ROTATE(T, p[p[z]])            //	Case 3 
15           else (same as then clause with "right" and "left" exchanged) 
16 color[root[T]] �� BLACK 
*/
//���ֺ������
void RB_Tree::rbtInsertFixup(rbtnode* z){
	rbtnode *y;
	while(z->p->color == red){		//�޸�����4
		if(z->p == z->p->p->left){	//yΪz->p->p���Һ���
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
			else{						//case 3����Ҫesle???
				z->p->color = black;	//ѭ������
				z->p->p->color = red;
				rightRotate(z->p->p);
			}
		}
		else{							//yΪz->p->p������
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
	this->root->color = black;			//�����޸�����2
}
//����ITEM
void RB_Tree::rbtInsert(ITEMTYPE a){
	rbtnode *rbt_node = new rbtnode();
	rbt_node->key = a;
	rbtInsert(rbt_node);
}


//ɾ��node
void RB_Tree::rbtDelete(ITEMTYPE a){
	rbtnode *z = rbtSearch(a);
	if(z == nil){
		printf("\ndelete error!!! the rbt is nil or the rbtnode doesn't exit...\n");
		Sleep(1000);return;}
	rbtDelete(z);
}
void RB_Tree::rbtDelete(rbtnode *z){
	rbtnode *x;
	rbtnode *y = z;							//���ڼ�¼ɾ�����z
	rbt_color y_original_color = y->color;	//���ڼ�¼ɾ�����z����ɫ����
	if(z->left == nil){
		x = z->right;						//���ڼ�¼������ʿ����⵽�ƻ��Ľ��
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
			x->p = y;						//x = nilʱ��Ҫfixup line4 ��x->p��Ϊarbitrary
		else{
			rbtTransplant(y,y->right);		//������x->p = y->p,�Ӷ�����Ϊarbitrary
			y->right = z->right;
			z->right->p = y;
		}
		rbtTransplant(z,y);
		y->left = z->left;
		y->left->p = y;

		y->color = z->color;				//ͨ����ת���ƻ�������ʵĵط���x�������y->right
	}
	if(y_original_color == black)			//3��������൱��ɾ���Ľ����ɫΪblack����Ҫ��x��Ϊ˫�غڻ��ߺ�ڽ���fixup
		rbtDeleteFixup(x);
}
//---------------------ɾ����������޸�-----------------------------------  
//α���룺  
/* 
RB-DELETE-FIXUP(T, x) 
1 while x �� root[T] and color[x] = BLACK 
2     do if x = left[p[x]] 
3           then w �� right[p[x]] 
4                if color[w] = RED 
5                   then color[w] �� BLACK                        ?  Case 1 
6                        color[p[x]] �� RED                       ?  Case 1 
7                        LEFT-ROTATE(T, p[x])                    ?  Case 1 
8                        w �� right[p[x]]                         ?  Case 1 
9                if color[left[w]] = BLACK and color[right[w]] = BLACK 
10                   then color[w] �� RED                          ?  Case 2 
11                        x p[x]                                  ?  Case 2 
12                   else if color[right[w]] = BLACK 
13                           then color[left[w]] �� BLACK          ?  Case 3 
14                                color[w] �� RED                  ?  Case 3 
15                                RIGHT-ROTATE(T, w)              ?  Case 3 
16                                w �� right[p[x]]                 ?  Case 3 
17                         color[w] �� color[p[x]]                 ?  Case 4 
18                         color[p[x]] �� BLACK                    ?  Case 4 
19                         color[right[w]] �� BLACK                ?  Case 4 
20                         LEFT-ROTATE(T, p[x])                   ?  Case 4 
21                         x �� root[T]                            ?  Case 4 
22        else (same as then clause with "right" and "left" exchanged) 
23 color[x] �� BLACK  
*/  
//ɾ��node
//���ֺ������
void RB_Tree::rbtDeleteFixup(rbtnode *x){
	rbtnode *w;									//x���ֵܽ��
	while(x != root && x->color == black){		//xΪ���ʱֻҪת��Ϊ�ڼ����fixup
		if(x == x->p->left){
			w = x->p->right;
			if(w->color == red){				//case1,תx�ֵ���ɫΪblack
				w->color = black;
				x->p->color = red;
				leftRotate(x->p);
				w = x->p->right;
			}
			if(w->left->color == black && w->right->color == black){//case2��˫��ɫ����;wɫ��Ϊblack
				w->color = red;
				x = x->p;
			}
			else if(w->right->color == black){	//case3��ת��Ϊcase4;wɫ��Ϊblack
				w->color = red;
				w->left->color = black;
				rightRotate(w);
				w = x->p->right;
			}
			else{//else?						//case4,wɫ��Ϊblack
				w->color = w->p->color;			//��֤x֧·�϶��һ�غ�
				w->p->color = black;
				w->right->color = black;
				leftRotate(w->p);
				x = root;						//���ý���
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

//���������f(������A)
void RB_Tree::buildRBT(ITEMTYPE *A,int A_length){
	FILE *batfile = fopen("rbt.bat","w+");						//w+��close֮��Ż����
	fprintf(batfile,"cd /d E:\mine\C++\Algorithms\Algorithms\n");//�Զ��޸�batfile·��
	for(int i=0;i<=A_length-1;i++){
		rbtInsert(A[i]);

		fprintf(batfile,"dot -Tpng -orbt%d.png rbt%d.gv\n",i,i);//���ɶ�Ӧ.gv�ļ���pngͼ

		string filename = addInt2Filename(i);
		//rbtMakeDot(filename.c_str());				//����.gv�ļ�����stringתΪc����ַ���char*
	}
	fclose(batfile);
}
//����rbti.gv�ļ���filename,��û���õ�ת������������
string RB_Tree::addInt2Filename(int i){
	string filename = "rbt";
	char a[10];										//��i(���Ϊ10λ��)תΪ10���Ʊ�ʾ���ַ���a
	sprintf(a, "%d", i);
	string index(a);								//��aת��Ϊstring��
	string extension = ".gv";
	filename = filename + index + extension;
	return filename;
}

//���������������ݹ������
void RB_Tree::recInorderWalk(rbtnode* root){
	if(root != nil){
		recInorderWalk(root->left);
		printf("%d ",root->key);
		recInorderWalk(root->right);
	}
}


//�������������������
void RB_Tree::fprintfRbtnode(rbtnode *rbt_node,FILE *fp){
	if(rbt_node->color == black)
		fprintf(fp,"node[shape=ellipse,style=filled,color=black,fontcolor=white];\n");
	else
		fprintf(fp,"node[shape=ellipse,style=filled,color=red,fontcolor=white];\n");
	//fprintf(fp,"%d[label=\"<f0> | <f1> %d | <f2> \"];\n",rbt_node->key,rbt_node->key);//�ڽ���ϴ�ӡlabel
}
//������������
void  RB_Tree::rbtDotOrder(rbtnode *rbt_node,FILE *fp){
	if(rbt_node == nil)	return;
	if(rbt_node == root){					//��ʾroot���
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
//���������filename.gv�ļ�
void RB_Tree::rbtMakeDot(const char *filename){
	FILE *fp=fopen(filename,"w+");
	fprintf(fp,"digraph RBT {\n");
	rbtDotOrder(root,fp);
	fprintf(fp,"}\n\n");
	fclose(fp);
}

//����
void RB_Tree::rbtTest(){
	string filename = addInt2Filename(1);		//���ɲ��Ե�rbt1.gv�ļ�
	rbtMakeDot(filename.c_str());
	int a;

	//printf("\nplease input the key you want to delete : \n");
	//scanf("%d",&a);
	//printf("after delete %d...\n",a);
	//rbtDelete(a);
	//recInorderWalk(root);
	//filename = addInt2Filename(2);				//���ɲ��Ե�rbt2.gv�ļ�
	//rbtMakeDot(filename.c_str());

	//printf("\nplease input the key you want to delete : \n");
	//scanf("%d",&a);
	//printf("after delete %d...\n",a);
	//rbtDelete(a);
	//recInorderWalk(root);
	//filename = addInt2Filename(3);				//���ɲ��Ե�rbt3.gv�ļ�
	//rbtMakeDot(filename.c_str());

	printf("\nplease input the key you want to insert : \n");
	scanf("%d",&a);
	printf("after insert %d...\n",a);
	rbtInsert(a);
	recInorderWalk(root);
	filename = addInt2Filename(2);				//���ɲ��Ե�rbt2.gv�ļ�
	rbtMakeDot(filename.c_str());
}


static int dataGenerate(int* A);
static void printfArray(ITEMTYPE* A,int A_length);

int __2151612main(){
	int A[LEN];
	int A_length = dataGenerate(A);				//������������ĳ���
	printfArray(A,A_length);
	printf("\n");

	RB_Tree *rbt = new RB_Tree();
	rbt->buildRBT(A,A_length);
	rbt->recInorderWalk(rbt->root);
	rbt->rbtMakeDot("rbt.gv");					//�������յ�rbtͼ��
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
	bool input_flag;	//���������жϱ�־
	do{
		showDatagenerateMode();
		input_flag=0;
		int casechoice;
		//scanf("%d",&casechoice);
		while(scanf("%d",&casechoice) == 0){
			fflush(stdin);	//�������ķǷ����ݣ�
			printf("input illegal,please input again ......\n");
		}
		switch(casechoice){
		case 1:{//�������������in.txt
			if((fp=fopen("in.txt","w"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("the data generates randomly is saving into in.txt ...... ");
			srand((unsigned)time(0));
			for(int k=0;k<LEN;k++){
				//srand(getpid());	//��ͬԪ�����������
				A[k]=random(LOWER,UPPER);
				fprintf(fp,"%d ",A[k]);
				//printf("%d ",A[k]);
			}
			A_length = LEN;
			printf("\n");break;}

		case 2:{//��in.txt��ȡ�������
			if((fp=fopen("in.txt","r"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("the data gets from in.txt is assign to array A ...... ");
			int k=0;
			while(!feof(fp)){										//A_length��֪����ʱ���أ�����
				fscanf(fp,"%d ",&A[k++]);
				//printf("%d ",A[k]);
			}
			A_length = k;
			printf("\n");break;}

		case 3:{//�ֶ�����
			if((fp=fopen("in.txt","w"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("please input the data you want to sort(end when the data input is illegal) :\n");
			int k=0;
			while(scanf("%d ",&A[k])){		//������һ���Ƿ����ݽ���������
				//printf("A[%d] = %d  ",k,A[k]);
				fprintf(fp,"%d ",A[k++]);
			}
			fflush(stdin);	//���stdin�еķǷ�����
			A_length = k;
			printf("the data input is saving into in.txt ...... \n");
			Sleep(1000);break;}

		default :
			//fflush(stdin);	//�������ķǷ��ַ���
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
