////验证virtual函数虚表
//#include <stdio.h>
//class VirClass{
//private:
//	int i1;
//	int i;
//public:
//	virtual void p1(){printf("p1()...%d\n",i);}
//	virtual void p2(){printf("p2...\n");}
//};
//
//int main(){
//	VirClass vc;
//	/*void** aPtr;
//	void** ptrVFT;
//	void* pVirFunc;
//	aPtr = (void **)&vc;
//	*(int *)(aPtr+2) = 2;
//	ptrVFT = (void**)*aPtr;
//	pVirFunc = *ptrVFT;*/
//
//	int *aPtr,*ptrVFT,*pVirFunc;
//	aPtr = (int *)&vc;
//	*(aPtr+2) = 2;
//	ptrVFT = (int *)*aPtr;
//	pVirFunc = (int *)*ptrVFT;
//
//	_asm{
//		mov ecx,aPtr;
//		call pVirFunc;
//	};
//	
//	pVirFunc = (int *)(*(ptrVFT+1));
//	//pVirFunc = *(ptrVFT+1);
//	_asm{
//		mov ecx,aPtr;
//		call pVirFunc;
//	};
//	getchar();
//	return 0;
//}