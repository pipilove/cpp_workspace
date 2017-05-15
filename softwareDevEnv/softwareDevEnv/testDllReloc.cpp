/*	建立一个动态链接库	
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
typedef int(*SubPtr)(int,int);

void main(){
	HMODULE h_withoutReloc=LoadLibraryA("dllRelocation.dll");
	if(h_withoutReloc==NULL){printf("cannot load dllRelocation.dll ...\n");system("pause");return;}
	else{printf("load dllRelocation.dll successfully...\n");}
	SubPtr fp_withoutReloc=(SubPtr)GetProcAddress(h_withoutReloc,"sub");
	if(fp_withoutReloc==NULL){printf("cannot get function sub() in dllRelocation.dll...\n");system("pause");return;}
	else{printf("get function sub() in dllRelocation.dll successfully...\n");}
	
	HMODULE h_withReloc=LoadLibraryA("dllRelocation2.dll");
	if(h_withReloc==NULL){printf("cannot load dllRelocation2.dll ...\n");system("pause");return;}
	else{printf("load dllRelocation2.dll successfully...\n");}
	SubPtr fp_withReloc=(SubPtr)GetProcAddress(h_withReloc,"sub");
	if(fp_withReloc==NULL){printf("cannot get function sub() in dllRelocation2.dll ...\n");system("pause");return;}
	else{printf("get function sub() in dllRelocation2.dll successfully...\n");}

	int sub_withoutReloc=fp_withoutReloc(3,2);
	int sub_withReloc=fp_withReloc(3,2);
	printf("3-2 = %d\n",sub_withoutReloc);
	printf("3-2 = %d\n",sub_withReloc);

	system("pause");
}
*/