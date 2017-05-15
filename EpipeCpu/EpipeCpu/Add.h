#pragma once
#include "Signal.h"

/*	带进位加法器	*/
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
