#include "AddSub.h"

output AddSub::into(input a,input b,input sub){
	Add* add1 = new Add();
	wire old_sub = sub;
	sub.bitExpand(0);
	sum = add1->into(a,b^sub,old_sub);	//调用加法器cla32实现加减法器
	//sum = add1->into(a.value,(b^sub).value,sub.value).value;	//调用加法器cla32实现加减法器
	return sum;
}
