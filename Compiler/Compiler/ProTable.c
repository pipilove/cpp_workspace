/*	���̼��(�ض��塢δ����)	*/
#include <string.h>
#include "ProTable.h"
#include "GetWordStruct.h"
extern proIfo funInfo[256];					//������Ϣ��
extern int pro_counter;						//���̸���
extern word* all_word[];					//������
extern int advance_index;

/*	���̼��(�ض���)	*/
int proCheck(){
	int index = 0;
	int current_pro_index = pro_counter;
	if(current_pro_index == 0)									//��һ�����������
		return 0;
	for(index = 0 ; index <= pro_counter -1 ; index ++){		//������ʱ����1
		if(	!( strcmp(funInfo[current_pro_index].proName,funInfo[index].proName) 
			|| strcmp(funInfo[current_pro_index].ptype,funInfo[index].ptype)
			|| ( funInfo[current_pro_index].plev != funInfo[index].plev ) )	)
			return 1;
	}
	return 0;
}

/*	���̼��(δ����)	*/
int callProCheck(){
	int index = 0;
	for(index = 0 ; index <= pro_counter ; index ++){			//������ʱ����1
		if(	!( strcmp(all_word[advance_index - 2]->name,funInfo[index].proName) )	)
			return 1;
	}
	return 0;
}
