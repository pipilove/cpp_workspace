#include "CtrlUnit.h"
#include "Mux2.h"
#include "Cpu.h"
//extern Mux2 rnd_mux;
extern wire inst;

void CtrlUnit::into(input op,input rs1,input rd,input erd,input ewreg,input esld,input mz,input mrd,input mwreg){//input rnb,
	reg i_and = 0, i_andi= 0, i_or  = 0, i_ori = 0,
		i_add = 0, i_addi= 0, i_sub = 0, i_subi= 0,
		i_load= 0, i_store=0, i_beq = 0, i_bne = 0,
		i_branch=0,i_sll = 0, i_srl = 0, i_sra = 0;
	if( inst != 0){			//inst = 0无效
		switch(op.value){	//操作码译码.sub(31,26)
		case 0x00000000:{
			i_and=  1 ;break;}
		case 0x00000001:{
			i_andi= 1 ;break;}
		case 0x00000002:{
			i_or  = 1 ;break;}
		case 0x00000003:{
			i_ori = 1 ;break;}
		case 0x00000004:{
			i_add = 1 ;break;}
		case 0x00000005:{
			i_addi= 1 ;break;}
		case 0x00000006:{
			i_sub = 1 ;break;}
		case 0x00000007:{
			i_subi= 1 ;break;}
		case 0x00000008:{
			i_load= 1 ;break;}
		case 0x00000009:{
			i_store=1 ;break;}
		case 0x0000000a:{
			i_bne = 1 ;break;}
		case 0x0000000b:{
			i_beq = 1 ;break;}
		case 0x0000000c:{
			i_branch=1;break;}
		case 0x0000000d:{
			i_sll = 1 ;break;}
		case 0x0000000e:{
			i_srl = 1 ;break;}
		case 0x0000000f:{
			i_sra = 1 ;break;}
		default:
			printf("inst used not defined\n");
		}
	}

	//是否为store指令
	sst = i_store;
	rnd_mux.into(sst,inst.sub(4,0),inst.sub(25,21));
	rnb = rnd_mux.out;

	wire rs1IsReg = i_and | i_andi | i_or | i_ori | i_add | i_addi | i_sub | i_subi | i_load | i_store ;//exclude b inst
	adepend.setBit( 1,(rs1IsReg & ewreg == 1 & rs1 == erd) | (rs1IsReg & ewreg == 0 & mwreg == 1 & rs1 == mrd)
		| (rs1IsReg & ewreg == 1 & ~(rs1 == erd) & mwreg == 1 & rs1 == mrd) );
	adepend.setBit( 0,(rs1IsReg & ewreg == 0 & mwreg == 1 & rs1 == mrd) 
		| (rs1IsReg & ewreg == 1 & ~(rs1 == erd) & mwreg == 1 & rs1 == mrd) );

	wire rs2IsReg = i_and | i_or | i_add | i_sub ;	
	bdepend.setBit( 1,(rs2IsReg & ewreg == 1 & rnb == erd) | (rs2IsReg & ~ewreg &  mwreg & rnb == mrd)
		| (rs2IsReg & ewreg & ~(rnb == erd) &  mwreg & rnb == mrd) );
	bdepend.setBit( 0,~rs2IsReg | (rs2IsReg & ~ewreg &  mwreg & rnb == mrd)
		| (rs2IsReg & ewreg & ~(rnb == erd) &  mwreg & rnb == mrd) );


	//wire depend = ~(rs1IsReg & rs1 == erd & esld == 1 ) | (rs2IsReg & rnb == erd & esld == 1 )
	//	| (i_store & rd == erd & esld == 1 );
	depend  = 1;												//0代表有控制或load相关
	if( ((rs1IsReg & rs1 == erd & esld == 1 ) | (rs2IsReg & rnb == erd & esld == 1 )
		   | (i_store & rd == erd & esld == 1 ).value) == 1 | ( ((i_bne | i_beq) & pr2.ewreg & ~pr2.em2reg) == 1) )
		depend = 0;


	//设置alu操作控制码
	aluc.setBit( 0,i_or | i_ori | i_sub | i_subi | i_store | i_srl |i_sra );
	aluc.setBit( 1,i_sra );
	aluc.setBit( 2,i_add | i_addi | i_sub | i_subi | i_sll |i_srl |i_sra );
	aluc.setBit( 3,i_load | i_store | i_sll | i_srl | i_sra | i_bne | i_beq );
	//alu a 使用移位
	// shift = i_sll | i_srl | i_sra;
	//alu b 使用立即数
	// aluimm = i_andi | i_ori | i_addi | i_subi | i_load | i_store;
	//设置符号位拓展,可以不要andi/ori?
	sext = i_andi | i_ori | i_addi | i_subi | i_load | i_store;	//| i_beq | i_bne | i_branch;
	//写z标志n_loaddepen相关和转移相关时都不写wz
	wz = depend & ~pr2.epcsource & (i_andi | i_ori | i_addi | i_subi | i_and | i_or | i_add | i_sub | i_sll | i_srl | i_sra);

	//写寄存器
	wreg = depend & ~pr2.epcsource & (i_add | i_sub | i_and | i_or | i_sll | i_srl | i_sra | i_addi | i_andi | i_subi | i_ori | i_load);
	//写存储器
	wmem = depend & ~pr2.epcsource & i_store;
	//存储器数据写入寄存器
	m2reg = depend & i_load;

	//下一条指令选择（同时也是转移相关封锁条件）
	pcsource = mz&i_beq | (~mz&i_bne) | i_branch;

}
