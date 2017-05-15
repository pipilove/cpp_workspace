#pragma once
#include "Signal.h"

/*	¿ØÖÆµ¥Ôª	*/
class CtrlUnit{
public:
	output wreg,m2reg,wmem,wz,aluc,adepend,bdepend,sext,sst,pcsource,depend,rnb;
	void into(input op,input rs1,input rd,input erd,input ewreg,input esld,input mz,input mrd,input mwreg);//input rnb,
};
