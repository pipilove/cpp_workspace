#pragma once
#include "Signal.h"

/*	ID级流水线寄存器 - pipedereg	*/
class PipeReg2{
public:
	output ewreg,em2reg,ewmem,ewz,ealuc,erd,eqa,eqb,eimm,eadepen,ebdepen,epcsource;
	void into(input wreg,input m2reg,input wmem,input wz,input aluc,input rd,
		input qa,input qb,input imm,input clrn,input adepen,input bdepen,input pcsource);
};
