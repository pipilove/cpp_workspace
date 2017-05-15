#pragma once
#include "Signal.h"
#include "AddSub.h"
#include "Mux4.h"

/*	arithmetic logic unit - alu */
class Alu{
public:
	output z,r;
	void into(input a,input b,input aluc);
};
