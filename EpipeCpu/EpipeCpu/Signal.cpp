#include "Signal.h"
#include <bitset>

Signal::Signal(){
	value = 0;		//每个Signal初始值为0
}


Signal::Signal(int val){
	value = val;
}

Signal Signal::sub(int high, int low){
	int a = 0xffffffff;
	int b = 0xffffffff;
	//a <<= (high+1);	//???????????
	a <<= high;
	a <<= 1;
	b <<= low;
	int i = value & (a^b);
	i >>= low;
	return Signal( i );
}

void Signal::operator = (int val){
	value = val;
}

Signal Signal::operator + (int val){
	value += val;
	return Signal(value);
}

Signal Signal::operator / (int val){
	int tmp_value = value;
	tmp_value /= val;
	return Signal(tmp_value);
}

Signal Signal::operator + (Signal s){
	value += s.value;
	return Signal(value);
}


Signal Signal::operator [] (int index){
	int tmp_value = value;
	tmp_value >>= index;
	return Signal(tmp_value & 0x00000001);
}

Signal Signal::operator | (Signal s){
	return Signal(s.value | value);
}

Signal Signal::operator & (Signal s){
	return Signal(s.value & value);
}

Signal Signal::operator & (int i){
	return Signal(i & value);
}

Signal Signal::operator ^ (Signal s){
	return Signal(s.value ^ value);
}

Signal Signal::operator ~ (){
	Signal tmp_value = 1;
	if(value == 1)
		tmp_value = 0;
	return Signal(tmp_value);
}

Signal Signal::operator << (int offset){
	value <<= offset;
	return Signal(value);
}


int Signal::operator && (int i){
	return (i && value);
}


int Signal::operator == (int i){
	if(value == i)
		return 1;
	else
		return 0;
}

int Signal::operator != (int i){
	if(value != i)
		return 1;
	else
		return 0;
}

int Signal::operator == (Signal s){
	if(s.value == value)
		return 1;
	else
		return 0;
}

ostream& operator<<(ostream& os,Signal& s){
    os<<s.value;
    return os;
}

void Signal::setBit(int index,Signal s){
	/*int a = 0xffffffff;
	int b = 0xffffffff;
	a <<= index;
	b <<= index-1;
	if(s == 0)
		value &= ~(a ^ b);
	else
		value |= ~(a ^ b);*/
	int a = 0x00000001;
	a <<= index;
	if(s == 0)
		value &= ~a;
	else
		value |= a;
}

void Signal::bitExpand(int bit){
	int tmp_value = value;
	tmp_value >>= bit;
	int a = 0xffffffff;
	a <<= (bit+1);
	if(tmp_value == 1)
		value |= a;
}

void Signal::bitExpand(Signal exp,int len){
	int a = 0xffffffff;
	a <<= (32 - len);
	if(exp == 1)
		value |= a;
}
