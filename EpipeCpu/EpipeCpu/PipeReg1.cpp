#include "PipeReg1.h"

void PipeReg1::into(input pinst,input clrn,input wir){
	if(clrn == 0)
		inst = 0;
	else if(wir == 1)
		inst = pinst;
}
