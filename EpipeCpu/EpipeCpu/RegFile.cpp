#include "RegFile.h"
reg regfile[31];	//31*32-bit regs,0 is invalid

void RegFile::into(input rna,input rnb,input d,input wn,input wreg,input clrn){
	qa = (rna == 0)? 0:regfile[rna.value];
	qb = (rnb == 0)? 0:regfile[rnb.value];
	if(clrn == 0)					//clear signal is negedge 0
		for(int i = 1;i < 32;i = i+1)
			regfile[i] = 0;
	else if(wreg && (wn != 0)) 		//write&write enable signal is valid
		regfile[wn.value] = d;
}
