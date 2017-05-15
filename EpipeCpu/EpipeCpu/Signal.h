#pragma once
#include <iostream>
using namespace std;

typedef class Signal{
public:
	Signal();
	Signal(int val);
	int value;

	Signal sub(int high, int low);

	void operator = (int val);
	Signal operator + (int val);
	Signal operator / (int val);
	Signal operator + (Signal s);
	Signal operator [] (int index);

	Signal operator | (Signal s);
	Signal operator & (Signal s);
	Signal operator & (int i);
	Signal operator ^ (Signal s);
	Signal operator ~ ();				//仅最后一位有效
	Signal operator << (int offset);
	int operator && (int i);

	int operator == (int i);
	int operator != (int i);
	int operator == (Signal s);
	friend ostream& operator << (ostream& output,Signal& obj);

	void setBit(int index,Signal s);	//<=> Signal[index] = s; s只有0位有效
	void bitExpand(int bit);			//用第bit位进行位拓展
	void bitExpand(Signal exp,int len);	//用exp进行高len位拓展
}input, output, wire, reg;

