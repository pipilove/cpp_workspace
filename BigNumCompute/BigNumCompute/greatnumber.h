#pragma once
//ѭ������
#define ROL(value) ((value<<1) | (value >>7))
//ѭ����������
#define ROR(value, k) ((value>>k) | (value <<(8-k)))
//ָ���ռ��С
#define MAXNUMBER 250
#define MAXPOWER 16
#define BYTE 8
//�����࣬�����ݴ�
#include "StringNumber.h"
 class GreatNumber
{
private:
	//С��
	unsigned char number[MAXNUMBER];
	//��ָ��
	unsigned char power[MAXPOWER];

	void binaryadd(GreatNumber *a, GreatNumber *b,GreatNumber *result, bool isPower);
	void binaryadd(GreatNumber *a, GreatNumber *b, bool isPower);
	void binarynot(GreatNumber *a, bool isPower);
	void binaryneg(GreatNumber *a, bool isPower);
	void align(GreatNumber *a, GreatNumber *b, GreatNumber *dif);
	void right(GreatNumber *a, GreatNumber *b, GreatNumber *dif);
	bool equZero(GreatNumber* a, bool isPower);
	//��Ϊ����ʱ�Ķ����Ʊ�ʾ�ĳ˷�
	void binarymul(GreatNumber *a, GreatNumber *b, GreatNumber *result);
	void load(std::string s, long number, GreatNumber *b);
	void normalize(GreatNumber *a);
	//����
	void left1bit(GreatNumber *a);
	//�߼�����һλ
	void left1bit(GreatNumber *a, bool logigal);
	//����
	void right1bit(GreatNumber *a);	
	//��ֵ
	void assign(GreatNumber *a,GreatNumber *b,bool isPower);
	//β����������֤��β��ΪС��
	void mantissaAlign(GreatNumber *a,GreatNumber *b);
	//�������
	void subPower(GreatNumber *a,GreatNumber *b,GreatNumber *result);
	//�ȽϷ���λ
	bool signCmp(GreatNumber *r,GreatNumber *y);
	//β�����,resultΪ����
	void div(GreatNumber *a,GreatNumber *b,GreatNumber *result);
	//����У��
	void floatDiv(GreatNumber *a,GreatNumber *b,GreatNumber *result);
	//���������
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