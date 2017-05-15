//#include <stdio.h>
//#include <malloc.h>
//#include <memory.h>
//
//#define RELOCATION_ITEM_SIZE sizeof(int)//�����ض�λ���
//#define RELOCATION_COUNT 2 //�ض�λ����2��
//#define RELOCATION_ITEMS_SIZE RELOCATION_ITEM_SIZE * RELOCATION_COUNT //�ض�λ���
//#define DATA_SEGMENT_LEN RELOCATION_COUNT * sizeof(int)//���ݶγ��ȣ�����������
//#define MOV_CODE_LEN 10*RELOCATION_COUNT
//#define RET_LEN 1
//#define CODE_SEGMENT_LEN MOV_CODE_LEN + RET_LEN //movָ��2����retָ��1��
//#define RET_CODE 0xc3
//#define PROGRAM_LEN sizeof(PrgHdr) + RELOCATION_ITEMS_SIZE + DATA_SEGMENT_LEN + CODE_SEGMENT_LEN	//���򳤶ȴ�С
//
//struct PrgHdr{
//	int imageBase;
//	int mainEntryOffset;//��������Գ���ͷ����ƫ����
//	int relocationCount;//�ض�λ����Ŀ  
//};
//
//void buildCode(char * codeStart, int varAddress){
//	//mov [00403374h],12345678h�Ļ����� C7 05 74 33 50 00 78 56 34 12
//	//����movָ����1
//	codeStart[0] = 0xc7;
//	codeStart[1] = 0x05;
//	int * pVarAddr;
//	pVarAddr = (int *)&codeStart[2];
//	*pVarAddr = varAddress;//�������ض�λǰ����ַ����
//	int * pVar;
//	pVar = (int *)&codeStart[6];
//	*pVar = 0x12345678;//��������ֵ
//
//	//����movָ����2
//	codeStart[10] = 0xc7;
//	codeStart[11] = 0x05;
//	pVarAddr = (int *)&codeStart[12];
//	*pVarAddr = varAddress+0x4;	
//	pVar = (int *)&codeStart[16];
//	*pVar = 0x12345679;
//
//	*(codeStart + MOV_CODE_LEN) = RET_CODE;//����retָ��
//}
//
////����һ������飬����ͷ�����ض�λ�����ݶΡ������
//void * makeProgram(int expectedBase){
//	//��������ͷ��
//	struct PrgHdr * prg = (struct PrgHdr *)malloc(PROGRAM_LEN);	//!!!
//	prg->imageBase = expectedBase;
//	prg->relocationCount = RELOCATION_COUNT;
//	int relocationTbLen = prg->relocationCount * RELOCATION_ITEM_SIZE;	//�ض�λ���
//	prg->mainEntryOffset = sizeof(struct PrgHdr) + relocationTbLen + DATA_SEGMENT_LEN;
//
//	//���������ض�λ��
//	*(int *)(prg + 1) = prg->mainEntryOffset + 2;	//��д�ض�λ��(prg + 1��һ��sizeof(prg)ƫ����ָ���һ���ض�λ��)
//	*(int *)((char*)prg + 0x10) = prg->mainEntryOffset + 0x0C;	//!!!(char*)prg + 0x10
//
//	//������������
//	char * codeStart = (char *)prg + prg->mainEntryOffset;	//�������ַ��(char *)����ȥ������������sizeof(prg)Ϊ��λƫ����
//	int expectedGlobalVarAddress = expectedBase + sizeof(PrgHdr) + relocationTbLen;	//�������ݶ���ַ
//	buildCode(codeStart, expectedGlobalVarAddress);
//
//	//�����������ݶ�
//	int * pGlobalVar = (int *)((char *)prg +  sizeof(PrgHdr) + relocationTbLen);
//	* pGlobalVar = 0x12345678;//��ȫ�ֱ�������ֵΪ0x12345678�� �൱��c������int gi = 0x12345678;��������غ�ִ��main֮ǰ��ֵ
//	int * pGlobalVar2 = (int *)((char *)prg +  sizeof(PrgHdr) + relocationTbLen+sizeof(int));
//	* pGlobalVar2 =(int) pGlobalVar;//��ȫ�ֱ�������ֵΪ&gi,��pGlobalVar
//	*(int*)* pGlobalVar2 = 0x12345679;
//
//	//���س�����ַ(void *)
//	return (void *)prg;
//}
//
//void * makeProgramWillRelocate(){
//	return makeProgram(0x00400000);
//}
//
////prgLoaded�������صĳ���ģ�����ʼ��ַ��prgInMem�������ص��ڴ����ʼ��ַ
//void loadProgram(void * prgLoaded, void * prgInMem){
//	memcpy(prgInMem, prgLoaded, PROGRAM_LEN);
//	struct PrgHdr * prgHdr = (struct PrgHdr *)prgInMem;
//	int expectedBase = prgHdr->imageBase;
//	if (expectedBase == (int)prgInMem){printf("need not relocate\n");return;}
//	else{
//		printf("need relocate, expected address is 0x%x, but actualAdress is 0x%x\n", expectedBase, prgInMem);
//		printf("relocation count is %d\n", prgHdr->relocationCount);
//		int *pRelocationItem = (int *)(prgHdr + 1);	//ָ��ͷ����һ����ַ������һ���ض�λ��
//		int offsetLoad = (int)prgInMem - expectedBase;
//		for (int i = 0; i < prgHdr->relocationCount; i++){
//			int * pRelocateAddress = (int *)((char *)prgInMem + *pRelocationItem);
//			int oldValue = * pRelocateAddress;
//			* pRelocateAddress = oldValue + offsetLoad;
//			printf("make a relocation, the value from 0x%x to 0x%x\n", oldValue, * pRelocateAddress);
//			pRelocationItem++;	//ָ��ڶ����ض�λ��
//		}
//		return;
//	}
//}
//
//void runProgram(void * prgInMem){
//	struct PrgHdr * prgHdr = (struct PrgHdr *)prgInMem;
//	void * mainFunctionAddress = (void *)((char *)prgInMem + prgHdr->mainEntryOffset);
//	_asm call mainFunctionAddress;	//!!��ret���Խ�������
//}
//
//void printTheGlobalVar(void * prgInMem){
//	int * pGlobalVar = (int *)((char *)prgInMem + sizeof(struct PrgHdr) + RELOCATION_ITEMS_SIZE);
//	for(int i=0;i<RELOCATION_COUNT;i++)
//		printf("the %dth global varable in the loaded program is 0x%x\n", i+1,* (pGlobalVar+i));
//}
//
//
////ppffset��pg1Offset�ֱ�����p��g1�����ͷ����ƫ����
//void getVarOffset(int * ppOffset, int * pg1Offset){
//
//}
//
//void main(){
//	//չʾ�����Լ��ض�λ��Ч��
//	void * prgLoaded = makeProgramWillRelocate();
//	char prgLocation[PROGRAM_LEN];	//�ڴ��з���Ŀռ�
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
