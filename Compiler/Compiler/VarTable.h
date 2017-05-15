/*	变量结构	*/
typedef struct var{
	char* vname;	//变量名
	char* vproc;	//所属过程名
	int vkind;		//变量分类 0—变量,1—形参
	char* types;	//变量类型
	int vlev;		//变量层次
	int vadr;		//变量在变量表中的位置
}var;

int varTable(int vkind);
int varCheck();
int realParaCheck();
