#pragma once
#include "Signal.h"

/*	pc�Ĵ���	*/
class PipeReg0{
public:
	output pc;
	void into(int depend,input npc,int clrn);
};
