#include "AddSub.h"

output AddSub::into(input a,input b,input sub){
	Add* add1 = new Add();
	wire old_sub = sub;
	sub.bitExpand(0);
	sum = add1->into(a,b^sub,old_sub);	//���üӷ���cla32ʵ�ּӼ�����
	//sum = add1->into(a.value,(b^sub).value,sub.value).value;	//���üӷ���cla32ʵ�ּӼ�����
	return sum;
}
