#include "IPRam.h"
reg ram[32];							//32*32-bit ram
int times;

void IPRam::into(input wmem,input addr,input datain){
	dataout=ram[addr.sub(6,2).value];		//字节地址4对齐，5位地址

	if(wmem.value)
		ram[addr.sub(6,2).value]=datain;
	/*
	for(int i=0;i<32;i=i+1)
		ram[i]=0;*/
	if(times == 0){				//ram初始化
	ram[0x00] = 0x0;
	ram[0x14] = 0x000000a3;
	ram[0x15] = 0x00000027;
	ram[0x16] = 0x00000079;
	ram[0x17] = 0x00000115;
	
	ram[0x01] = 0x00000004;
	times = 1;
	}
}
