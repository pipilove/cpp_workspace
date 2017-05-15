//#include <stdio.h>
//#include <malloc.h>
//#include <memory.h>
//
//#define RELOCATION_ITEM_SIZE sizeof(int)//单个重定位项长度
//#define RELOCATION_COUNT 2 //重定位项数2个
//#define RELOCATION_ITEMS_SIZE RELOCATION_ITEM_SIZE * RELOCATION_COUNT //重定位项长度
//#define DATA_SEGMENT_LEN RELOCATION_COUNT * sizeof(int)//数据段长度（两个整数）
//#define MOV_CODE_LEN 10*RELOCATION_COUNT
//#define RET_LEN 1
//#define CODE_SEGMENT_LEN MOV_CODE_LEN + RET_LEN //mov指令2条，ret指令1条
//#define RET_CODE 0xc3
//#define PROGRAM_LEN sizeof(PrgHdr) + RELOCATION_ITEMS_SIZE + DATA_SEGMENT_LEN + CODE_SEGMENT_LEN	//程序长度大小
//
//struct PrgHdr{
//	int imageBase;
//	int mainEntryOffset;//主函数相对程序头部的偏移量
//	int relocationCount;//重定位项数目  
//};
//
//void buildCode(char * codeStart, int varAddress){
//	//mov [00403374h],12345678h的机器码 C7 05 74 33 50 00 78 56 34 12
//	//构建mov指令码1
//	codeStart[0] = 0xc7;
//	codeStart[1] = 0x05;
//	int * pVarAddr;
//	pVarAddr = (int *)&codeStart[2];
//	*pVarAddr = varAddress;//构建（重定位前）地址部分
//	int * pVar;
//	pVar = (int *)&codeStart[6];
//	*pVar = 0x12345678;//构建被赋值
//
//	//构建mov指令码2
//	codeStart[10] = 0xc7;
//	codeStart[11] = 0x05;
//	pVarAddr = (int *)&codeStart[12];
//	*pVarAddr = varAddress+0x4;	
//	pVar = (int *)&codeStart[16];
//	*pVar = 0x12345679;
//
//	*(codeStart + MOV_CODE_LEN) = RET_CODE;//构建ret指令
//}
//
////构造一个程序块，包括头部、重定位表、数据段、代码段
//void * makeProgram(int expectedBase){
//	//构建程序头部
//	struct PrgHdr * prg = (struct PrgHdr *)malloc(PROGRAM_LEN);	//!!!
//	prg->imageBase = expectedBase;
//	prg->relocationCount = RELOCATION_COUNT;
//	int relocationTbLen = prg->relocationCount * RELOCATION_ITEM_SIZE;	//重定位项长度
//	prg->mainEntryOffset = sizeof(struct PrgHdr) + relocationTbLen + DATA_SEGMENT_LEN;
//
//	//构建程序重定位项
//	*(int *)(prg + 1) = prg->mainEntryOffset + 2;	//填写重定位项(prg + 1加一个sizeof(prg)偏移量指向第一个重定位项)
//	*(int *)((char*)prg + 0x10) = prg->mainEntryOffset + 0x0C;	//!!!(char*)prg + 0x10
//
//	//构建程序代码段
//	char * codeStart = (char *)prg + prg->mainEntryOffset;	//代码段首址，(char *)不能去掉，否则是以sizeof(prg)为单位偏移量
//	int expectedGlobalVarAddress = expectedBase + sizeof(PrgHdr) + relocationTbLen;	//期望数据段首址
//	buildCode(codeStart, expectedGlobalVarAddress);
//
//	//构建程序数据段
//	int * pGlobalVar = (int *)((char *)prg +  sizeof(PrgHdr) + relocationTbLen);
//	* pGlobalVar = 0x12345678;//给全局变量赋初值为0x12345678， 相当于c语言中int gi = 0x12345678;即程序加载后，执行main之前的值
//	int * pGlobalVar2 = (int *)((char *)prg +  sizeof(PrgHdr) + relocationTbLen+sizeof(int));
//	* pGlobalVar2 =(int) pGlobalVar;//给全局变量赋初值为&gi,即pGlobalVar
//	*(int*)* pGlobalVar2 = 0x12345679;
//
//	//返回程序首址(void *)
//	return (void *)prg;
//}
//
//void * makeProgramWillRelocate(){
//	return makeProgram(0x00400000);
//}
//
////prgLoaded代表被加载的程序模块的起始地址，prgInMem代表被加载到内存的起始地址
//void loadProgram(void * prgLoaded, void * prgInMem){
//	memcpy(prgInMem, prgLoaded, PROGRAM_LEN);
//	struct PrgHdr * prgHdr = (struct PrgHdr *)prgInMem;
//	int expectedBase = prgHdr->imageBase;
//	if (expectedBase == (int)prgInMem){printf("need not relocate\n");return;}
//	else{
//		printf("need relocate, expected address is 0x%x, but actualAdress is 0x%x\n", expectedBase, prgInMem);
//		printf("relocation count is %d\n", prgHdr->relocationCount);
//		int *pRelocationItem = (int *)(prgHdr + 1);	//指向头部下一个地址，即第一个重定位项
//		int offsetLoad = (int)prgInMem - expectedBase;
//		for (int i = 0; i < prgHdr->relocationCount; i++){
//			int * pRelocateAddress = (int *)((char *)prgInMem + *pRelocationItem);
//			int oldValue = * pRelocateAddress;
//			* pRelocateAddress = oldValue + offsetLoad;
//			printf("make a relocation, the value from 0x%x to 0x%x\n", oldValue, * pRelocateAddress);
//			pRelocationItem++;	//指向第二个重定位项
//		}
//		return;
//	}
//}
//
//void runProgram(void * prgInMem){
//	struct PrgHdr * prgHdr = (struct PrgHdr *)prgInMem;
//	void * mainFunctionAddress = (void *)((char *)prgInMem + prgHdr->mainEntryOffset);
//	_asm call mainFunctionAddress;	//!!有ret可以结束返回
//}
//
//void printTheGlobalVar(void * prgInMem){
//	int * pGlobalVar = (int *)((char *)prgInMem + sizeof(struct PrgHdr) + RELOCATION_ITEMS_SIZE);
//	for(int i=0;i<RELOCATION_COUNT;i++)
//		printf("the %dth global varable in the loaded program is 0x%x\n", i+1,* (pGlobalVar+i));
//}
//
//
////ppffset和pg1Offset分别是向p和g1离程序头部的偏移量
//void getVarOffset(int * ppOffset, int * pg1Offset){
//
//}
//
//void main(){
//	//展示加载以及重定位的效果
//	void * prgLoaded = makeProgramWillRelocate();
//	char prgLocation[PROGRAM_LEN];	//内存中分配的空间
//	loadProgram(prgLoaded, prgLocation);
//	printf("\n\nbefore relocation ......\n ");
//	printTheGlobalVar(prgLocation);
//
//	runProgram(prgLocation);
//	printf("\nafter relocation ......\n ");
//	printTheGlobalVar(prgLocation);
//
//	free(prgLoaded);
//}
