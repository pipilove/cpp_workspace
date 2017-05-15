#include "Alu.h"

void Alu::into(input a,input b,input aluc){
	wire r_sum,r_ld_st,r_shift;

	//alu设计                           sra 1111;//aluc[0] = 1代表右移
	//and 0000;  add 0100;  load 1000; sll 1100;
	//or  0001;  sub 0101; store 1001; srl 1101;
	wire r_and = a & b;		//执行and运算
	wire r_or  = a | b;		//执行or运算
	wire r_and_or = aluc[0].value? r_or:r_and;//执行逻辑运算

	AddSub as0,as1,as2;
	r_sum = as0.into(a,b,aluc[0]);	//执行算术运算
	r_ld_st = as1.into(a,b, 0 );	//执行存取运算

	Mux4 mux4;
	mux4.into(r_and_or,r_sum,r_ld_st,r_shift,aluc.sub(3,2));//aluc[3:2]选择运算类型
	r = mux4.out;
	if( r == 0 )
		z = 1;
	else
		z = 0;		//设置结果0标志,结果为0时z = 1
}
