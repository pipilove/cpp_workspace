#include <string.h>
#include "GetWordStruct.h"
#include "ProTable.h"
#include "VarTable.h"
int varCheck();

var vartable[256];					//变量名表
int vartable_len;					//变量名表中变量个数

extern word* all_word[];			//变量名
extern int advance_index;
extern char * var_pro_name;			//变量所属过程名,也可通过varTable参数传入
int var_offset;						//变量在变量表中的位移
extern int plev;					//变量层次 = 过程层次(+1)

extern proIfo funInfo[];			//过程信息表,引入记录函数中最后的变量声明
extern int pro_counter;

/*	填写变量名表(形参和变量才填表)	*/
int varTable(int vkind){
	int var_error;
	vartable[vartable_len].vname = all_word[advance_index-1]->name;
	vartable[vartable_len].vproc = var_pro_name;
	vartable[vartable_len].vkind = vkind;
	vartable[vartable_len].types = "(ints)";
	vartable[vartable_len].vadr  = var_offset;
	vartable[vartable_len++].vlev  = plev;						//变量名表中变量个数加1

	var_error = varCheck();										//检查变量在变量表中是否存在

	//也可以在这每次填完一个变量就写入.var文件中

	funInfo[pro_counter].ladr = var_offset;						//记录函数中最后的变量声明
	var_offset += 4;
	return var_error;
}

/*	查表(形参、变量)	*/
int varCheck(){
	int index = 0;
	int current_var_index = vartable_len -1;
	if(current_var_index == 0)									//第一个变量不查表
		return 0;
	for(index = 0 ; index <= vartable_len -2 ; index ++){		//查表存在时返回1
		if(	 !( strcmp(vartable[current_var_index].vname,vartable[index].vname) 
			|| strcmp(vartable[current_var_index].vproc,vartable[index].vproc)
			|| strcmp(vartable[current_var_index].types,vartable[index].types)
			|| ( vartable[current_var_index].vkind != vartable[index].vkind )
			|| ( vartable[current_var_index].vlev  != vartable[index].vlev  ) )	)
			return 1;
	}
	return 0;
}

/*	查表(实参)	*/
int realParaCheck(){
	int index = 0;
	for(index = 0 ; index <= vartable_len -1 ; index ++){						//查表不存在时返回0
		if(	!( strcmp(all_word[advance_index-2]->name,vartable[index].vname)	//当前实参名
			|| strcmp(var_pro_name,vartable[index].vproc)						//当前实参所属过程名
			|| strcmp("(ints)",vartable[index].types) )	)
			return 1;
	}
	return 0;
}
