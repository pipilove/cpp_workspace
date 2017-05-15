/* 过程信息	*/
typedef struct proIfo{
	char* proName;			//过程名
	char* ptype;			//过程类型
	int plev;				//过程层次
	int fadr;				//过程第一个变量位置
	int ladr;				//过程最后一个变量位置
}proIfo;

int proCheck();
int callProCheck();
