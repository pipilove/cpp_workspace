#include "Alu.h"

void Alu::into(input a,input b,input aluc){
	wire r_sum,r_ld_st,r_shift;

	//alu���                           sra 1111;//aluc[0] = 1��������
	//and 0000;  add 0100;  load 1000; sll 1100;
	//or  0001;  sub 0101; store 1001; srl 1101;
	wire r_and = a & b;		//ִ��and����
	wire r_or  = a | b;		//ִ��or����
	wire r_and_or = aluc[0].value? r_or:r_and;//ִ���߼�����

	AddSub as0,as1,as2;
	r_sum = as0.into(a,b,aluc[0]);	//ִ����������
	r_ld_st = as1.into(a,b, 0 );	//ִ�д�ȡ����

	Mux4 mux4;
	mux4.into(r_and_or,r_sum,r_ld_st,r_shift,aluc.sub(3,2));//aluc[3:2]ѡ����������
	r = mux4.out;
	if( r == 0 )
		z = 1;
	else
		z = 0;		//���ý��0��־,���Ϊ0ʱz = 1
}
