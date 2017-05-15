/*	过程检查(重定义、未定义)	*/
#include <string.h>
#include "ProTable.h"
#include "GetWordStruct.h"
extern proIfo funInfo[256];					//过程信息表
extern int pro_counter;						//过程个数
extern word* all_word[];					//变量名
extern int advance_index;

/*	过程检查(重定义)	*/
int proCheck(){
	int index = 0;
	int current_pro_index = pro_counter;
	if(current_pro_index == 0)									//第一个变量不查表
		return 0;
	for(index = 0 ; index <= pro_counter -1 ; index ++){		//查表存在时返回1
		if(	!( strcmp(funInfo[current_pro_index].proName,funInfo[index].proName) 
			|| strcmp(funInfo[current_pro_index].ptype,funInfo[index].ptype)
			|| ( funInfo[current_pro_index].plev != funInfo[index].plev ) )	)
			return 1;
	}
	return 0;
}

/*	过程检查(未定义)	*/
int callProCheck(){
	int index = 0;
	for(index = 0 ; index <= pro_counter ; index ++){			//查表存在时返回1
		if(	!( strcmp(all_word[advance_index - 2]->name,funInfo[index].proName) )	)
			return 1;
	}
	return 0;
}
