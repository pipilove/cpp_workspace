#include "Mux2.h"
//
//void Mux2::into(input pcsource,input addr){
//	if(pcsource == 1)
//		offset = addr;
//	else
//		offset = 4;
//}

void Mux2::into(input select,input in0,input in1){
	if(select == 1)
		out = in1;
	else
		out = in0;
}
