#pragma once
#include "Add.h"
#include "Signal.h"

/*	加减法单元	addsub	*/
class AddSub{
public:
	output sum;
	output into(input a,input b,input sub);	//sub减法指示
};
