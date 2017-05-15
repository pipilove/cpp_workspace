/**************************************************************************************/
/*	编程之美1.1 - 控制cpu占用率曲线（50%直线、1~100任意直线、正弦曲线）	皮皮 2014-6-30	  */
/**************************************************************************************/
#include <Windows.h>
#include <stdio.h>
#include <math.h>
using namespace std;

#define GetCpuTickCount() __rdtsc()

//50%直线
void line50(){
	for( ; ;){
		for(int i = 0 ; i < 8666666 ; i++);
		/*
		mov         eax,dword ptr [i] 
		add         eax,1  
		mov         dword ptr [i],eax 
		cmp         dword ptr [i],0Ah 
		jge         cpu+48h (0AC1418h)
		jmp         cpu+37h (0AC1407h)
		*/
		Sleep(10);			//几条指令时间呢？？？
	}
}


const DWORD lineAny_busy_time = 10;
const DWORD lineAny_idle_time = lineAny_busy_time;
//1~100任意直线
void lineAny(){
	DWORD pre_time;
	while(1){
		pre_time = GetTickCount();				//这个函数只精确到55ms，1个tick就是55ms
		while( (GetTickCount() - pre_time) <= lineAny_busy_time );
		Sleep(lineAny_idle_time);
	}
}

const int SAMPLE_NUM = 200;
DWORD busy_time[200];
const DWORD TOTAL_TIME_SLICE = 100;//每隔100ms取下一个采样点，让cpu工作在对应振幅的时间,TOTAL_TIME_SLICEms变化一次cpu占用率
const DWORD HALF_TOTAL_TIME_SLICE = TOTAL_TIME_SLICE/2;
//sine 曲线
void sine(){
	DWORD pre_time;
	for(int i = 0 ; ; i = (i+1)%SAMPLE_NUM ){
		pre_time = GetTickCount();
		while( (GetTickCount() - pre_time) <= busy_time[i]);	//cpu忙
		Sleep(TOTAL_TIME_SLICE - busy_time[i]);					//cpu闲
	}
}

const double PI_L = 0.031415926535;
//对sine采样
void sine_sampling(){
	for(int i = 0 ; i < SAMPLE_NUM ; i++){
		busy_time[i] = (DWORD)( sin( PI_L*i )*HALF_TOTAL_TIME_SLICE + HALF_TOTAL_TIME_SLICE );	//busy_time值范围 （-1~1） *50+50 = (0~100)
		//printf("busy_time[%d] = %d\n",i,busy_time[i]);
	}
}

void __5186main(){
	sine_sampling();

	//printf("CurrentProcessorNumber : %d\n",(int)GetCurrentProcessorNumber());
	SYSTEM_INFO info;
    GetSystemInfo(&info);						//调用API函数来获取计算机硬件的信息
	printf("dwNumberOfProcessors : %d\n",info.dwNumberOfProcessors);	//cpu核数
	//printf("CpuTickCount = %u\n",GetCpuTickCount());

	DWORD dwThreadId;
	HANDLE hThread;
	int coreNum = info.dwNumberOfProcessors;
	for(int i = 0 ; i < coreNum ; i ++){
		hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)sine,0,0,&dwThreadId);
		SetThreadAffinityMask(hThread,1<<i);	//针对cpu核i(from 0)
	}
    WaitForSingleObject(hThread, INFINITE);		//传入INFINITE表示无限等待,线程不会结束？
}
