#include "IPRom.h"
wire rom[0x1A];					//47*32-bit rom,lay in ram access collepse???

/*	��iprom��ȡָ	*/
void IPRom::into(input pc){	
	inst=rom[pc.sub(7,2).value];			//pcΪ�ֽڱ�ַ��+4ƫ�ƣ�rom�ֱ�ַ+1ƫ��
}
