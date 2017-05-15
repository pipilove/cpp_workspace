#include "IPRom.h"
wire rom[0x1A];					//47*32-bit rom,lay in ram access collepse???

/*	从iprom中取指	*/
void IPRom::into(input pc){	
	inst=rom[pc.sub(7,2).value];			//pc为字节编址，+4偏移；rom字编址+1偏移
}
