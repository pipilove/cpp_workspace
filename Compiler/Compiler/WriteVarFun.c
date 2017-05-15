/*	将变量名表和过程名表写入文件中		*/
#include <stdio.h>
#include "VarTable.h"
#include "ProTable.h"

extern FILE* varfp;
extern var vartable[256];						//变量名表
extern int vartable_len;						//变量个数

extern FILE* profp;
extern proIfo funInfo[256];						//过程信息表
extern int pro_counter;							//过程个数


void writeVarFun(){
	int i;
	/*	填写变量名表	*/
	for(i = 0 ; i <= vartable_len-1 ; i++){
		fprintf(varfp,"vname: %16s\n",vartable[i].vname );
		fprintf(varfp,"vproc: %16s\n",vartable[i].vproc); 
		fprintf(varfp,"vkind: %16d\n",vartable[i].vkind);
		fprintf(varfp,"types: %16s\n",vartable[i].types);
		fprintf(varfp,"vlev:  %16d\n",vartable[i].vlev);  
		fprintf(varfp,"vadr:  %16d\n\n",vartable[i].vadr);
	}
	/*	填写过程名表	*/
	for(i = 0; i<= pro_counter ; i++){
		fprintf(profp,"proName:%16s\n",funInfo[i].proName);
		fprintf(profp,"ptype:%18s\n",funInfo[i].ptype);
		fprintf(profp,"plev:%19d\n",funInfo[i].plev);
		fprintf(profp,"fadr:%19d\n",funInfo[i].fadr);
		fprintf(profp,"ladr:%19d\n\n",funInfo[i].ladr);
	}
}
