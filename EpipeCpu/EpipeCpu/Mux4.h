#pragma once
#include "Signal.h"

/*	��ѡһ��·ѡ����	mux4x32	*/
class Mux4{
public:
	output out;
	void into(input a0,input a1,input a2,input a3,input select);
};
