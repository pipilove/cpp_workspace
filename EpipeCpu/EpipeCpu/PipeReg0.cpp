#include "PipeReg0.h"

/*	����pc	*/
void PipeReg0::into(int depend,input npc,int clrn){
	if(clrn == 0)
		pc = 0;
	else if(depend == 1)
		pc = npc;
}
