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
	Signal operator ~ ();				//�����һλ��Ч
	Signal operator << (int offset);
	int operator && (int i);

	int operator == (int i);
	int operator != (int i);
	int operator == (Signal s);
	friend ostream& operator << (ostream& output,Signal& obj);

	void setBit(int index,Signal s);	//<=> Signal[index] = s; sֻ��0λ��Ч
	void bitExpand(int bit);			//�õ�bitλ����λ��չ
	void bitExpand(Signal exp,int len);	//��exp���и�lenλ��չ
}input, output, wire, reg;

