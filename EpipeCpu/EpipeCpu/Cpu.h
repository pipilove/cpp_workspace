#pragma once
#include "Signal.h"
#include "IPRomInit.h"
#include "Add.h"
#include "AddSub.h"
#include "Alu.h"
#include "CtrlUnit.h"
#include "IPRam.h"
#include "IPRom.h"
#include "Mux2.h"
#include "Mux4.h"
#include "PipeReg0.h"
#include "PipeReg1.h"
#include "PipeReg2.h"
#include "PipeReg3.h"
#include "PipeReg4.h"
#include "RegFile.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <map>

PipeReg0 pr0;
IPRom iprom;
PipeReg1 pr1;
CtrlUnit cu;
RegFile rf;
Mux2 rnd_mux;
PipeReg2 pr2;
PipeReg3 pr3;
IPRam ipram;
PipeReg4 pr4;
Mux2 result;
wire inst;
int cycles = 20;
fstream cpuFile;
fstream instFile;

int Cpu(input clrn);
int instInputSelect();
//void outFile(Signal npc,Mux4 alu_a_mux,Mux4 alu_b_mux,Alu alu_unit);


int main(){
	input clrn = 1;

	instFile.open("../instFile.txt",ios::in | ios::out);
	if(!instFile){
		cout<<"instFile open fail!!!"<<endl;
		system("pause");
		exit(1);
	}
	instInputSelect();

	cpuFile.open("../cpufile.json",ios::out);
	if(!cpuFile){
		cout<<"cpuFile open fail!!!"<<endl;
		system("pause");
		exit(1);
	}
	cpuFile<<"["<<endl;

	while(cycles--){
		Cpu(clrn);
	}

	cpuFile<<"]"<<endl;
	cpuFile.close();
	system("pause");
	return 0;
}

extern reg regfile[31];
extern reg ram[32];

string id_codes[30] = {	
	"non inst",
	"non inst",
	"non inst",
	"non inst",
	"ori r3,r3,3",
	"andi r2,r3,2",
	"or r1,r3,r2",
	"load r4,r4,4",
	"sub  r4,r4,r2",
	"sub  r4,r4,r2",
	"addi r2,r4,1",
	"branch 2",
	"ori r5,r5,5",
	"sub  r1,r1,r2",
	"beq  2",
	"beq  2",
	"ori r5,r5,5",
	"store r2,r1,4",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst"
};
int id_index = 4;


string if_codes[30] = {	
	"ori r3,r3,3",
	"andi r2,r3,2",
	"or r1,r3,r2",
	"load r4,r4,4",
	"sub  r4,r4,r2",
	"addi r2,r4,1",
	"addi r2,r4,1",
	"branch 2",
	"ori r5,r5,5",
	"sub  r1,r1,r2",
	"beq  2",
	"ori r5,r5,5",
	"ori r5,r5,5",
	"store r2,r1,4",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst",
	"undef inst"
};
int if_index = 0;


/*	流水线cpu module - cpu */
int Cpu(input clrn){								//cpu(clk,clrn,pinst,md , pc,mwmem,mr,mqb)
	//所有转移指令位拓展，由上一级inst计算出
	inst = pr1.inst;								//取出ID级的inst
	wire b_imm = inst.sub(25,0);					//{{6{inst[25]}},inst[25:0]};
	b_imm.bitExpand(25);
	wire b_offset = b_imm << 2;

	//IPRom iprom;
	wire pc = pr0.pc;								//当前pc
	iprom.into(pc);
	wire pinst = iprom.inst;						//当前的取指指令


	//CtrlUnit cu
	wire op = inst.sub(31,26);						//input for ctrlunit
	wire rs1 = inst.sub(20,16);
	wire rd = inst.sub(25,21);
	//wire rnb = rnd_mux.out;
	wire erd = pr2.erd;
	wire ewreg = pr2.ewreg;
	wire em2reg = pr2.em2reg;
	wire mz = pr3.mz;
	wire mrd = pr3.mrd;
	wire mwreg = pr3.mwreg;
	//void into(input op,input rs1,input rnb,input rd,input erd,input ewreg,input esld,input mz,input mrd,input mwreg);
	cu.into(op,rs1,rd,erd,ewreg,em2reg,mz,mrd,mwreg);//rnb,
	//ctrlunit cu (op,rs1,rnb,rd,erd,ewreg,em2reg,mz,mrd,mwreg,
	//				sst,adepen,bdepen,aluc,wz,wmem,m2reg,wreg,n_loaddepen,pcsource,sext);

	//rf的rnd端选择rs2或rd(store指令)
	//wire sst = cu.sst;
	//rnd_mux.into(sst,inst.sub(4,0),inst.sub(25,21));
	/*mux2x5 reg_rnb_select(inst[4:0],inst[25:21],sst,rnb);*/

	//下条指令偏移量
	wire pcsource = cu.pcsource;
	Mux2 pc_mux;pc_mux.into(pcsource,4,b_offset);		//mux2x32 nextimm (32'h4,b_offset,pcsource,offsetpc);
	//计算下条指令地址
	AddSub pc_as;pc_as.into(pc_mux.out,pc,0);			//相对指令的下一条指令 求beq/bne转移地址adr	
	wire npc = pc_as.sum;								//最新计算出来的pc赋值给下一个要取的npc

	//写回内容选择	Mux2 result; 应在regfile取数和alu之前计算完成alu_mem的值
	wire wm2reg = pr4.wm2reg;
	wire wr = pr4.wr;
	wire wd = pr4.wd;
	result.into(wm2reg,wr,wd);							//alu_mem即regfile的d
	wire alu_mem = result.out;							//alu_mem修改为当前result输出

	/*	写寄存器堆 regfile	在id开始前就应该写回*/
	wire wrd = pr4.wrd;
	wire wwreg = pr4.wwreg;
	//rf.into(rs1,rnb,alu_mem,wrd,wwreg,clrn);
	rf.into(rs1,0,alu_mem,wrd,wwreg,clrn);

	wire rnb = rnd_mux.out;
	//rf.into(rs1,rnb,alu_mem,wrd,wwreg,clrn);
	rf.into(rs1,rnb,0,0,0,clrn);
	/*regfile rf(inst[20:16],rnb,alu_mem,wrd,wwreg,clk,clrn,qa,qb);*/

	wire sext = cu.sext;
	wire e = sext&inst[15];								//imm位拓展
	wire imm = inst.sub(15,0);
	imm.bitExpand(e,16);								//{{16{e}},inst.sub(15,0);

	/*pipereg2*/
	wire wreg = cu.wreg;
	wire m2reg = cu.m2reg;
	wire wmem = cu.wmem;
	wire wz = cu.wz;
	wire aluc = cu.aluc;
	wire qa = rf.qa;
	wire qb = rf.qb;
	wire adepen = cu.adepend;
	wire bdepen = cu.bdepend;
	//pr2.into(wreg,m2reg,wmem,wz,aluc,inst.sub(25,21),qa,qb,imm,clrn,adepen,bdepen);
	/*void into(input wreg,input m2reg,input wmem,input wz,input aluc,input rd,
	input qa,input qb,input imm,input clrn,input adepen,input bdepen);*/
	/*pipereg2 pipereg22(wreg,m2reg,wmem,wz,aluc,inst[25:21],qa,qb,imm,clk,clrn,adepen,bdepen,
	ewreg,em2reg,ewmem,ewz,ealuc,erd,eqa,eqb,eimm,eadepen,ebdepen);*/

	//alu连接逻辑
	Mux4 alu_a_mux,alu_b_mux;
	wire eqa = pr2.eqa;
	wire eqb = pr2.eqb;
	wire eimm = pr2.eimm;
	wire mr = pr3.mr;
	wire eadepen = pr2.eadepen;
	wire ebdepen = pr2.ebdepen;
	alu_a_mux.into(eqa,eimm,mr,alu_mem,eadepen);
	alu_b_mux.into(eqb,eimm,mr,alu_mem,ebdepen);

	Alu alu_unit;
	wire alua = alu_a_mux.out;
	wire alub = alu_b_mux.out;
	wire ealuc = pr2.ealuc;
	alu_unit.into(alua,alub,ealuc);



	wire ewmem = pr2.ewmem;
	wire ewz = pr2.ewz;
	wire ez = alu_unit.z;
	wire er = alu_unit.r;
	//pr3.into(ewreg,em2reg,ewmem,ewz,erd,ez,er,eqb,clrn);
	/*void into(input ewreg,input em2reg,input ewmem,input ewz,input erd,input ez,input er,input eqb,input clrn);
	pipereg3 pipereg33(ewreg,em2reg,ewmem,ewz,erd,ez,er,eqb,clk,clrn,
	mwreg,mm2reg,mwmem,mrd,mz,mr,mqb);*/

	//IPRam ipram;
	wire mwmem = pr3.mwmem;
	wire wqb = pr3.mqb;
	ipram.into(mwmem,mr,wqb);

	//PipeReg4 pr4;
	wire mm2reg = pr3.mm2reg;
	wire md = ipram.dataout;
	//pr4.into(mwreg,mm2reg,mrd,mr,md,clrn);
	/*void into(input mwreg,input mm2reg,input mrd,input mr,input md,input clrn);
	pipereg4 pipereg44(mwreg,mm2reg,mrd,mr,md,clk,clrn,wwreg,wm2reg,wrd,wr,wd);*/


	/*	所有内容都在一个周期结束后打入		*/	
	wire n_loaddepen = cu.depend;

	pr0.into(n_loaddepen.value,npc,clrn.value);									//npc打入pr0.pc
	pr1.into(pinst,clrn,n_loaddepen);											//pinst打入pr1.inst中
	pr2.into(wreg,m2reg,wmem,wz,aluc,rd,qa,qb,imm,clrn,adepen,bdepen,pcsource);	//rd = inst.sub(25,21)
	pr3.into(ewreg,em2reg,ewmem,ewz,erd,ez,er,eqb,clrn);
	pr4.into(mwreg,mm2reg,mrd,mr,md,clrn);

	//outFile(npc,alu_a_mux,alu_b_mux,alu_unit);

	/*	信号通过文件输出	*/
	//void outFile(Signal npc,Mux4 alu_a_mux,Mux4 alu_b_mux,Alu alu_unit){	
	/*	if级	*/
	cpuFile<<"{"<<endl;
	cpuFile<<"\""<<"npc"		<<"\""<<":"<<"\""<<npc/4<<"\""<<","<<endl;
	cpuFile<<"\""<<"pc"			<<"\""<<":"<<"\""<<pc/4<<"\""<<","<<endl;
	cpuFile<<"\""<<"pinst"		<<"\""<<":"<<"\""<<hex<<setw(8)<<setfill('0')<<iprom.inst<<"\""<<","<<endl;
	cpuFile<<"\""<<"pcsource"	<<"\""<<":"<<"\""<<dec<<cu.pcsource<<"\""<<","<<endl;
	cpuFile<<"\""<<"depend"		<<"\""<<":"<<"\""<<cu.depend<<"\""<<","<<endl;

	/* id级	*/
	cpuFile<<"\""<<"r1"			<<"\""<<":"<<"\""<<regfile[1]<<"\""<<","<<endl;
	cpuFile<<"\""<<"r2"			<<"\""<<":"<<"\""<<regfile[2]<<"\""<<","<<endl;
	cpuFile<<"\""<<"r3"			<<"\""<<":"<<"\""<<regfile[3]<<"\""<<","<<endl;
	cpuFile<<"\""<<"r4"			<<"\""<<":"<<"\""<<regfile[4]<<"\""<<","<<endl;
	cpuFile<<"\""<<"r5"			<<"\""<<":"<<"\""<<regfile[5]<<"\""<<","<<endl;

	cpuFile<<"\""<<"inst"		<<"\""<<":"<<"\""<<hex<<setw(8)<<setfill('0')<<inst<<"\""<<","<<endl;
	cpuFile<<"\""<<"rs1"		<<"\""<<":"<<"\""<<dec<<inst.sub(20,16)<<"\""<<","<<endl;
	cpuFile<<"\""<<"rs2"		<<"\""<<":"<<"\""<<inst.sub(4,0)<<"\""<<","<<endl;
	cpuFile<<"\""<<"op"			<<"\""<<":"<<"\""<<inst.sub(31,26)<<"\""<<","<<endl;
	cpuFile<<"\""<<"rd"			<<"\""<<":"<<"\""<<inst.sub(25,21)<<"\""<<","<<endl;
	cpuFile<<"\""<<"imm"		<<"\""<<":"<<"\""<<inst.sub(15,0)<<"\""<<","<<endl;
	cpuFile<<"\""<<"addr"		<<"\""<<":"<<"\""<<inst.sub(25,0)<<"\""<<","<<endl;
	cpuFile<<"\""<<"sst"		<<"\""<<":"<<"\""<<cu.sst<<"\""<<","<<endl;
	cpuFile<<"\""<<"sext"		<<"\""<<":"<<"\""<<cu.sext<<"\""<<","<<endl;
	cpuFile<<"\""<<"rnb"		<<"\""<<":"<<"\""<<cu.rnb<<"\""<<","<<endl;
	cpuFile<<"\""<<"wreg"		<<"\""<<":"<<"\""<<cu.wreg<<"\""<<","<<endl;
	cpuFile<<"\""<<"m2reg"		<<"\""<<":"<<"\""<<cu.m2reg<<"\""<<","<<endl;
	cpuFile<<"\""<<"wmem"		<<"\""<<":"<<"\""<<cu.wmem<<"\""<<","<<endl;
	cpuFile<<"\""<<"wz"			<<"\""<<":"<<"\""<<cu.wz<<"\""<<","<<endl;
	cpuFile<<"\""<<"aluc"		<<"\""<<":"<<"\""<<cu.aluc<<"\""<<","<<endl;
	cpuFile<<"\""<<"adepend"	<<"\""<<":"<<"\""<<cu.adepend<<"\""<<","<<endl;
	cpuFile<<"\""<<"bdepend"	<<"\""<<":"<<"\""<<cu.bdepend<<"\""<<","<<endl;
	cpuFile<<"\""<<"qa"			<<"\""<<":"<<"\""<<rf.qa<<"\""<<","<<endl;
	cpuFile<<"\""<<"qb"			<<"\""<<":"<<"\""<<rf.qb<<"\""<<","<<endl;
	cpuFile<<"\""<<"imm"			<<"\""<<":"<<"\""<<imm<<"\""<<","<<endl;

	/*	exe级	*/
	cpuFile<<"\""<<"ewreg"		<<"\""<<":"<<"\""<<ewreg<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"em2reg"		<<"\""<<":"<<"\""<<em2reg<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"ewmem"		<<"\""<<":"<<"\""<<ewmem<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"ewz"		<<"\""<<":"<<"\""<<ewz<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"ealuc"		<<"\""<<":"<<"\""<<ealuc<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"eadepend"	<<"\""<<":"<<"\""<<eadepen<<"\""<<","<<endl;	//pr2.
	cpuFile<<"\""<<"ebdepend"	<<"\""<<":"<<"\""<<ebdepen<<"\""<<","<<endl;	//pr2.
	cpuFile<<"\""<<"erd"		<<"\""<<":"<<"\""<<erd<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"eqa"		<<"\""<<":"<<"\""<<eqa<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"eqb"		<<"\""<<":"<<"\""<<eqb<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"eimm"		<<"\""<<":"<<"\""<<eimm<<"\""<<","<<endl;		//pr2.
	cpuFile<<"\""<<"a"			<<"\""<<":"<<"\""<<alu_a_mux.out<<"\""<<","<<endl;
	cpuFile<<"\""<<"b"			<<"\""<<":"<<"\""<<alu_b_mux.out<<"\""<<","<<endl;
	cpuFile<<"\""<<"z"			<<"\""<<":"<<"\""<<alu_unit.z<<"\""<<","<<endl;
	cpuFile<<"\""<<"r"			<<"\""<<":"<<"\""<<alu_unit.r<<"\""<<","<<endl;

	/*	mem级	*/
	cpuFile<<"\""<<"mwreg"		<<"\""<<":"<<"\""<<mwreg<<"\""<<","<<endl;		//pr3.
	cpuFile<<"\""<<"mm2reg"		<<"\""<<":"<<"\""<<mm2reg<<"\""<<","<<endl;		//pr3.
	cpuFile<<"\""<<"mwmem"		<<"\""<<":"<<"\""<<mwmem<<"\""<<","<<endl;		//pr3.
	cpuFile<<"\""<<"mrd"		<<"\""<<":"<<"\""<<mrd<<"\""<<","<<endl;		//pr3.
	cpuFile<<"\""<<"mz"			<<"\""<<":"<<"\""<<mz<<"\""<<","<<endl;			//pr3.
	cpuFile<<"\""<<"mr"			<<"\""<<":"<<"\""<<mr<<"\""<<","<<endl;			//pr3.
	cpuFile<<"\""<<"mqb"		<<"\""<<":"<<"\""<<pr3.mqb<<"\""<<","<<endl;	//pr3.
	cpuFile<<"\""<<"md"			<<"\""<<":"<<"\""<<ipram.dataout<<"\""<<","<<endl;
	cpuFile<<"\""<<"ram1"		<<"\""<<":"<<"\""<<ram[1]<<"\""<<","<<endl;

	/* wb级	*/
	cpuFile<<"\""<<"wwreg"		<<"\""<<":"<<"\""<<wwreg<<"\""<<","<<endl;		//pr4.
	cpuFile<<"\""<<"wm2reg"		<<"\""<<":"<<"\""<<wm2reg<<"\""<<","<<endl;		//pr4.
	cpuFile<<"\""<<"wrd"		<<"\""<<":"<<"\""<<wrd<<"\""<<","<<endl;		//pr4.
	cpuFile<<"\""<<"wr"			<<"\""<<":"<<"\""<<wr<<"\""<<","<<endl;			//pr4.
	cpuFile<<"\""<<"wd"			<<"\""<<":"<<"\""<<wd<<"\""<<","<<endl;			//pr4.

	/*	每一级注释	*/
	cpuFile<<"\""<<"code"<<0<<"\""<<":"<<"\""<<if_codes[if_index]<<"\""<<","<<endl;
	for(int i = 1; i <= 4 ; i++)
		cpuFile<<"\""<<"code"<<i<<"\""<<":"<<"\""<<id_codes[id_index-i]<<"\""<<","<<endl;
	id_index++;
	if_index++;

	cpuFile<<"\""<<"alu_mem"	<<"\""<<":"<<"\""<<result.out<<"\""<<endl;		//每个周期的最后不需要，

	if(cycles)
		cpuFile<<"},"<<endl;
	else																		//最后一个周期不需要，
		cpuFile<<"}"<<endl;

	return 0;
};

/*	指令输入选择提示	*/
int instInputSelect(){
	map<string,int> instMap;		//instMap初始化
	instMap.insert( map<string,int>::value_type("ori",		0x0c000000) );
	instMap.insert( map<string,int>::value_type("andi",		0x04000000) );
	instMap.insert( map<string,int>::value_type("or",		0x08000000) );
	instMap.insert( map<string,int>::value_type("load",		0x20000000) );
	instMap.insert( map<string,int>::value_type("sub",		0x18000000) );
	instMap.insert( map<string,int>::value_type("addi",		0x14000000) );
	instMap.insert( map<string,int>::value_type("branch",	0x30000000) );
	instMap.insert( map<string,int>::value_type("ori",		0x0c000000) );
	instMap.insert( map<string,int>::value_type("ori",		0x0c000000) );
	instMap.insert( map<string,int>::value_type("sub",		0x18000000) );
	instMap.insert( map<string,int>::value_type("beq",		0x2c000000) );
	instMap.insert( map<string,int>::value_type("ori",		0x0c000000) );
	instMap.insert( map<string,int>::value_type("ori",		0x0c000000) );
	instMap.insert( map<string,int>::value_type("store",	0x24000000) );

	int inst_input;
	int input_select;
	bool inputError;
	string inst_str;
	do{		
		cout<<"please input the instraction generation mode :"<<endl;
		cout<<"0 : using the default inst"<<endl;
		cout<<"1 : input yourself from controler"<<endl;
		cout<<"2 : load inst form instFile.txt"<<endl<<endl;
		cin>>input_select;
		switch(input_select){
		case 0:{
			ipRomInit();							//初始化iprom中的默认指令
			inputError = 0;
			break;
			   }
		case 1:{
			cout<<"input user-defined instraction( # to end input):"<<endl;
			cin>>inst_str;
			while( inst_str != "#"){
				inst_input = instMap[inst_str];
				cin>>inst_str;
			}
			cout<<"****************  input end  *******************"<<endl;
			inputError = 0;
			break;
			   }
		case 2:{
			inputError = 0;
			break;
			   }
		default:{
			cout<<"mode input error, input again!"<<endl;
			inputError = 1;
			break;
				}
		}
	}while(inputError);
	return 0;
}
