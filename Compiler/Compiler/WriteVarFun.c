/*	����������͹�������д���ļ���		*/
#include <stdio.h>
#include "VarTable.h"
#include "ProTable.h"

extern FILE* varfp;
extern var vartable[256];						//��������
extern int vartable_len;						//��������

extern FILE* profp;
extern proIfo funInfo[256];						//������Ϣ��
extern int pro_counter;							//���̸���


void writeVarFun(){
	int i;
	/*	��д��������	*/
	for(i = 0 ; i <= vartable_len-1 ; i++){
		fprintf(varfp,"vname: %16s\n",vartable[i].vname );
		fprintf(varfp,"vproc: %16s\n",vartable[i].vproc); 
		fprintf(varfp,"vkind: %16d\n",vartable[i].vkind);
		fprintf(varfp,"types: %16s\n",vartable[i].types);
		fprintf(varfp,"vlev:  %16d\n",vartable[i].vlev);  
		fprintf(varfp,"vadr:  %16d\n\n",vartable[i].vadr);
	}
	/*	��д��������	*/
	for(i = 0; i<= pro_counter ; i++){
		fprintf(profp,"proName:%16s\n",funInfo[i].proName);
		fprintf(profp,"ptype:%18s\n",funInfo[i].ptype);
		fprintf(profp,"plev:%19d\n",funInfo[i].plev);
		fprintf(profp,"fadr:%19d\n",funInfo[i].fadr);
		fprintf(profp,"ladr:%19d\n\n",funInfo[i].ladr);
	}
}
