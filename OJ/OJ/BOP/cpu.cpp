/**************************************************************************************/
/*	���֮��1.1 - ����cpuռ�������ߣ�50%ֱ�ߡ�1~100����ֱ�ߡ��������ߣ�	ƤƤ 2014-6-30	  */
/**************************************************************************************/
#include <Windows.h>
#include <stdio.h>
#include <math.h>
using namespace std;

#define GetCpuTickCount() __rdtsc()

//50%ֱ��
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
		Sleep(10);			//����ָ��ʱ���أ�����
	}
}


const DWORD lineAny_busy_time = 10;
const DWORD lineAny_idle_time = lineAny_busy_time;
//1~100����ֱ��
void lineAny(){
	DWORD pre_time;
	while(1){
		pre_time = GetTickCount();				//�������ֻ��ȷ��55ms��1��tick����55ms
		while( (GetTickCount() - pre_time) <= lineAny_busy_time );
		Sleep(lineAny_idle_time);
	}
}

const int SAMPLE_NUM = 200;
DWORD busy_time[200];
const DWORD TOTAL_TIME_SLICE = 100;//ÿ��100msȡ��һ�������㣬��cpu�����ڶ�Ӧ�����ʱ��,TOTAL_TIME_SLICEms�仯һ��cpuռ����
const DWORD HALF_TOTAL_TIME_SLICE = TOTAL_TIME_SLICE/2;
//sine ����
void sine(){
	DWORD pre_time;
	for(int i = 0 ; ; i = (i+1)%SAMPLE_NUM ){
		pre_time = GetTickCount();
		while( (GetTickCount() - pre_time) <= busy_time[i]);	//cpuæ
		Sleep(TOTAL_TIME_SLICE - busy_time[i]);					//cpu��
	}
}

const double PI_L = 0.031415926535;
//��sine����
void sine_sampling(){
	for(int i = 0 ; i < SAMPLE_NUM ; i++){
		busy_time[i] = (DWORD)( sin( PI_L*i )*HALF_TOTAL_TIME_SLICE + HALF_TOTAL_TIME_SLICE );	//busy_timeֵ��Χ ��-1~1�� *50+50 = (0~100)
		//printf("busy_time[%d] = %d\n",i,busy_time[i]);
	}
}

void __5186main(){
	sine_sampling();

	//printf("CurrentProcessorNumber : %d\n",(int)GetCurrentProcessorNumber());
	SYSTEM_INFO info;
    GetSystemInfo(&info);						//����API��������ȡ�����Ӳ������Ϣ
	printf("dwNumberOfProcessors : %d\n",info.dwNumberOfProcessors);	//cpu����
	//printf("CpuTickCount = %u\n",GetCpuTickCount());

	DWORD dwThreadId;
	HANDLE hThread;
	int coreNum = info.dwNumberOfProcessors;
	for(int i = 0 ; i < coreNum ; i ++){
		hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)sine,0,0,&dwThreadId);
		SetThreadAffinityMask(hThread,1<<i);	//���cpu��i(from 0)
	}
    WaitForSingleObject(hThread, INFINITE);		//����INFINITE��ʾ���޵ȴ�,�̲߳��������
}
