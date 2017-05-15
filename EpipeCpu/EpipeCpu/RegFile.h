#pragma once
#include "Signal.h"

/* ¼Ä´æÆ÷¶Ñregfile file - regfile	*/
class RegFile{
public:
	output qa,qb;
	void into(input rna,input rnb,input d,input wn,input wreg,input clrn);
};
