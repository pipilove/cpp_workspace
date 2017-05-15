#include "PipeReg4.h"

void PipeReg4::into(input mwreg,input mm2reg,input mrd,input mr,input md,input clrn){
	if(clrn==0){
		wwreg=0;
		wm2reg=0;
		wrd=0;		
		wr=0;	
		wd=0;
	}else{
		wwreg=mwreg;	
		wm2reg=mm2reg;
		wrd=mrd;		
		wr=mr;
		wd=md;
	}
}
