#include <string.h>
#include "GetWordStruct.h"
#include "ProTable.h"
#include "VarTable.h"
int varCheck();

var vartable[256];					//��������
int vartable_len;					//���������б�������

extern word* all_word[];			//������
extern int advance_index;
extern char * var_pro_name;			//��������������,Ҳ��ͨ��varTable��������
int var_offset;						//�����ڱ������е�λ��
extern int plev;					//������� = ���̲��(+1)

extern proIfo funInfo[];			//������Ϣ��,�����¼���������ı�������
extern int pro_counter;

/*	��д��������(�βκͱ��������)	*/
int varTable(int vkind){
	int var_error;
	vartable[vartable_len].vname = all_word[advance_index-1]->name;
	vartable[vartable_len].vproc = var_pro_name;
	vartable[vartable_len].vkind = vkind;
	vartable[vartable_len].types = "(ints)";
	vartable[vartable_len].vadr  = var_offset;
	vartable[vartable_len++].vlev  = plev;						//���������б���������1

	var_error = varCheck();										//�������ڱ��������Ƿ����

	//Ҳ��������ÿ������һ��������д��.var�ļ���

	funInfo[pro_counter].ladr = var_offset;						//��¼���������ı�������
	var_offset += 4;
	return var_error;
}

/*	���(�βΡ�����)	*/
int varCheck(){
	int index = 0;
	int current_var_index = vartable_len -1;
	if(current_var_index == 0)									//��һ�����������
		return 0;
	for(index = 0 ; index <= vartable_len -2 ; index ++){		//������ʱ����1
		if(	 !( strcmp(vartable[current_var_index].vname,vartable[index].vname) 
			|| strcmp(vartable[current_var_index].vproc,vartable[index].vproc)
			|| strcmp(vartable[current_var_index].types,vartable[index].types)
			|| ( vartable[current_var_index].vkind != vartable[index].vkind )
			|| ( vartable[current_var_index].vlev  != vartable[index].vlev  ) )	)
			return 1;
	}
	return 0;
}

/*	���(ʵ��)	*/
int realParaCheck(){
	int index = 0;
	for(index = 0 ; index <= vartable_len -1 ; index ++){						//�������ʱ����0
		if(	!( strcmp(all_word[advance_index-2]->name,vartable[index].vname)	//��ǰʵ����
			|| strcmp(var_pro_name,vartable[index].vproc)						//��ǰʵ������������
			|| strcmp("(ints)",vartable[index].types) )	)
			return 1;
	}
	return 0;
}
