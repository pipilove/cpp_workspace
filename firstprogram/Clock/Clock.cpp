// Clock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Clock{
private:
	int hour,minute,second;
public:
	void SetAlarm(int hour,int minute,int second);
	run();
}
Clock::SetAlarm (int hour,int minute,int second){
	this.hour=hour;
	this.minute=minute;
	this.second=second;
}
Clock::run(){
}

int main()
{
	int hour,minute,second;
	char space;
	Clock Clock1;
	cout<<"Please input the alarm time :hour minute second"<<endl;
	cin>>hour>>space>>minute>>space>>second;
	Clock1.SetAlarm(hour,minute,second);
	return 0;
}
