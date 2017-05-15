#include "Add.h"
//
//void Add::into(input offset,input pc){
//	npc = pc + 4;
//}

output Add::into(input a,input b,input ci){
	sum = a + b +ci;
	return sum;
}
