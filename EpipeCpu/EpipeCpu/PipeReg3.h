#pragma once
#include "Signal.h"

/*	exe����ˮ�߼Ĵ��� pipereg3	*/
class PipeReg3{
public:
	output mwreg,mm2reg,mwmem,mrd,mz,mr,mqb;
	void into(input ewreg,input em2reg,input ewmem,input ewz,input erd,input ez,input er,input eqb,input clrn);
};
