#pragma once
#include "Signal.h"

/*	四选一多路选择器	mux4x32	*/
class Mux4{
public:
	output out;
	void into(input a0,input a1,input a2,input a3,input select);
};
