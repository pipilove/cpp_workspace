#pragma once
#include "Signal.h"

/*	WB级流水线寄存器 - pipereg4	*/
class PipeReg4{
public:
	output wwreg,wm2reg,wrd,wr,wd;
	void into(input mwreg,input mm2reg,input mrd,input mr,input md,input clrn);
};
