#include "PipeReg3.h"

void PipeReg3::into(input ewreg,input em2reg,input ewmem,input ewz,input erd,input ez,input er,input eqb,input clrn){
	if(clrn==0){
		mwreg=0;	 mm2reg=0;
		mwmem=0;	 mrd=0; 
		mz=0;		 mr=0;
		mqb=0;			
	}else{
		mwreg=ewreg;	 mm2reg=em2reg;
		mwmem=ewmem;	 mrd=erd; 
		mr=er;			 mqb=eqb;
	}
	if(ewz.value) 
		mz=ez;		//only for alu inst				
}
