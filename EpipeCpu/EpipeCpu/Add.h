#pragma once
#include "Signal.h"

/*	����λ�ӷ���	*/
/*
class Add{
public:
	output npc;
	void into(input offset,input pc);
};*/
class Add{
public:
	output sum;
	output into(input a,input b,input ci);
};
