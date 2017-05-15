#pragma once
#include "Signal.h"

/*	exe级流水线寄存器 pipereg3	*/
class PipeReg3{
public:
	output mwreg,mm2reg,mwmem,mrd,mz,mr,mqb;
	void into(input ewreg,input em2reg,input ewmem,input ewz,input erd,input ez,input er,input eqb,input clrn);
};
