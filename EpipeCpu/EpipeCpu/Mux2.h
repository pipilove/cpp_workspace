#pragma once
#include "Signal.h"

/*	��·ѡ����	*/
/*
class Mux2{
public:
	output offset;
	void into(input pcsource,input addr);
};*/
class Mux2{
public:
	output out;
	void into(input select,input in0,input in1);
};
