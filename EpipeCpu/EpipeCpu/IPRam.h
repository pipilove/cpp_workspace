#pragma once
#include "Signal.h"

/*	���ݴ洢�� - IP_RAM	*/
class IPRam{
public:
	output dataout;
	void into(input wmem,input addr,input datain);
};
