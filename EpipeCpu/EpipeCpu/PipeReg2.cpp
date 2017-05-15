#include "PipeReg2.h"

void PipeReg2::into(input wreg,input m2reg,input wmem,input wz,input aluc,input rd,
	input qa,input qb,input imm,input clrn,input adepen,input bdepen,input pcsource){
		if(clrn==0){
			ewreg=0;    em2reg=0;
			ewmem=0;    ewz=0;
			ealuc=0;	eqa=0;
			eqb=0;      eimm=0;
			erd=0;		epcsource = 0;
			eadepen=0;	ebdepen=0;
		}else{
			ewreg=wreg;    	em2reg=m2reg;
			ewmem=wmem;    	ewz=wz;
			ealuc=aluc;		eqa=qa;
			eqb=qb;      	eimm=imm;
			erd=rd;			epcsource = pcsource;
			eadepen=adepen;	ebdepen=bdepen;
		}
}
