#pragma once
#include "Signal.h"

/*	pc¼Ä´æÆ÷	*/
class PipeReg0{
public:
	output pc;
	void into(int depend,input npc,int clrn);
};
