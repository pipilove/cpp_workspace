#pragma once
#include "Signal.h"

/*	WB����ˮ�߼Ĵ��� - pipereg4	*/
class PipeReg4{
public:
	output wwreg,wm2reg,wrd,wr,wd;
	void into(input mwreg,input mm2reg,input mrd,input mr,input md,input clrn);
};
