#pragma once
//循环左移
#define ROL(value) ((value<<1) | (value >>7))
//循环个数右移
#define ROR(value, k) ((value>>k) | (value <<(8-k)))
//指定空间大小
#define MAXNUMBER 250
#define MAXPOWER 16
#define BYTE 8
//基础类，数据暂存
#include "StringNumber.h"
 class GreatNumber
{
private:
	//小数
	unsigned char number[MAXNUMBER];
	//幂指数
	unsigned char power[MAXPOWER];

	void binaryadd(GreatNumber *a, GreatNumber *b,GreatNumber *result, bool isPower);
	void binaryadd(GreatNumber *a, GreatNumber *b, bool isPower);
	void binarynot(GreatNumber *a, bool isPower);
	void binaryneg(GreatNumber *a, bool isPower);
	void align(GreatNumber *a, GreatNumber *b, GreatNumber *dif);
	void right(GreatNumber *a, GreatNumber *b, GreatNumber *dif);
	bool equZero(GreatNumber* a, bool isPower);
	//均为正数时的二进制表示的乘法
	void binarymul(GreatNumber *a, GreatNumber *b, GreatNumber *result);
	void load(std::string s, long number, GreatNumber *b);
	void normalize(GreatNumber *a);
	//左移
	void left1bit(GreatNumber *a);
	//逻辑左移一位
	void left1bit(GreatNumber *a, bool logigal);
	//右移
	void right1bit(GreatNumber *a);	
	//赋值
	void assign(GreatNumber *a,GreatNumber *b,bool isPower);
	//尾数调整，保证商尾数为小数
	void mantissaAlign(GreatNumber *a,GreatNumber *b);
	//阶码相减
	void subPower(GreatNumber *a,GreatNumber *b,GreatNumber *result);
	//比较符号位
	bool signCmp(GreatNumber *r,GreatNumber *y);
	//尾数相除,result为假商
	void div(GreatNumber *a,GreatNumber *b,GreatNumber *result);
	//假商校正
	void floatDiv(GreatNumber *a,GreatNumber *b,GreatNumber *result);
	//浮点数相除
	void quotientRevise(GreatNumber *result);
public:
	void Initialize();
	void add(GreatNumber *a, GreatNumber *b, GreatNumber *result);
	void mul(GreatNumber *a, GreatNumber *b, GreatNumber *result);//a*b

	GreatNumber operator=(std::string);
	GreatNumber operator=(GreatNumber b);
	GreatNumber operator+(GreatNumber b);
	GreatNumber operator-(GreatNumber b);
	GreatNumber operator*(GreatNumber b);
	GreatNumber operator/(GreatNumber b);
};