#pragma once
#include "Signal.h"

/*	Êý¾Ý´æ´¢Æ÷ - IP_RAM	*/
class IPRam{
public:
	output dataout;
	void into(input wmem,input addr,input datain);
};
