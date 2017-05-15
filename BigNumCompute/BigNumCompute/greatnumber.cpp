#include  "greatnumber.h"
using namespace std;

void GreatNumber::Initialize()
{
	for (int i = 0; i < MAXNUMBER; i++) this->number[i] = 0;
	for (int i = 0; i < MAXPOWER; i++) this->power[i] = 0;
}

//���ּӷ�
void GreatNumber::binaryadd(GreatNumber *a, GreatNumber *b, GreatNumber *result, bool isPower){
	//λ������ʶ
	unsigned char mark = 1;
	//��λ��ʶ
	unsigned char C0 = 0;
	//�ӷ�����
	//��ÿһ��char��ע��С�˻��Ǵ�����)
	unsigned char ca, cb, p, g;
	if(!isPower)
	{
		for(int i = 0; i<MAXNUMBER; i++)
		{
			//�ֱ�λ����
			for(int j = 0; j<BYTE; j++)
			{
				ca = a->number[i] & mark;
				cb = b->number[i] & mark;
  				p = ca ^ cb;
  				g = ca & cb;
				//������Ž�result
				result->number[i] |= p ^ C0;
				//�����λ���
				C0 = g | (p & C0);
				//��λ������ƣ�ʹ�ö�����һλ
				C0 = ROL(C0);
				//��־λ���ƣ�ʹ�ö�����һλ
				mark = ROL(mark);
			}
		 }
	}
	else
	{
  		for(int i=0;i<MAXPOWER;i++)
  		{
  			for(int j=0;j<BYTE;j++)
  			{
  				ca = a->power[i] & mark;
  				cb = b->power[i] & mark;
  				p = ca ^ cb;
  				g = ca & cb;
  				result->power[i] |= p ^  C0;
  				C0 = g | (p& C0);
  				C0 = ROL(C0);
  				mark = ROL(mark);
  			}
  		}
	}
}

//���ּӷ�����
void GreatNumber::binaryadd(GreatNumber *a, GreatNumber *b, bool isPower)
{
	GreatNumber * one = new GreatNumber();
	binaryadd(a,b,one,isPower);
	if(isPower)
		for (int i = 0; i < MAXPOWER; i++)
			a->power[i]  = one->power[i];
	else
		for (int i = 0; i < MAXNUMBER; i++)
			a->number[i]  = one->number[i];
}

//����
void GreatNumber::binarynot(GreatNumber *a, bool isPower)
{
	if(isPower)
		for(int i = 0; i<MAXPOWER; i++)
			a->power[i] = ~a->power[i];
	else
		for(int i=0;i<MAXNUMBER;i++)
			a->number[i]=~a->number[i];
}

//���෴��
void GreatNumber::binaryneg(GreatNumber *a, bool isPower)
{
	if(isPower)
	{
		binarynot(a, true);
		GreatNumber * p = new GreatNumber();
		p->power[0]=1;
		GreatNumber * t = new GreatNumber();
		binaryadd(a, p, t, true);
		for(int i=0;i<MAXPOWER;i++) a->power[i] = t->power[i];
	}
	else
	{
		binarynot(a, false);
		GreatNumber * p = new GreatNumber();
		p->number[0]=1;
		GreatNumber * t = new GreatNumber();
		binaryadd(a, p, t, false);
		for(int i=0;i<MAXNUMBER;i++) a->number[i] = t->number[i];
	}
}

//�Խ�
void GreatNumber::align(GreatNumber *a, GreatNumber *b, GreatNumber *dif)
{
	GreatNumber * t = new GreatNumber();
	bool isamax = 0;
	unsigned char mark = 0x80;
	assign(t,b,true);
	binaryneg(t, true);
	binaryadd(a, t, dif, true);
	if(dif->power[MAXPOWER-1]&mark)  // difΪ����
		for(int i =0; i < MAXPOWER; i++) a->power[i] = b->power[i];
	else
		for(int i =0; i < MAXPOWER; i++) b->power[i] = a->power[i];
}

//����һλ
void GreatNumber::left1bit(GreatNumber *a){
	unsigned char high = 0, highnext = 0;
	high = a->number[0] & 0x80;
	a->number[0] <<= 1;
	for(int i = 1;i < MAXNUMBER;i++){
		highnext = a->number[i] & 0x80;
		high>>=7;
		a->number[i] = a->number[i]<<1 | high;
		high = highnext;
	}
}

//����һλ
void GreatNumber::right1bit(GreatNumber *a){
	unsigned char low = 0, lownext = 0;
	low = a->number[MAXNUMBER-1] & 0x01;
	a->number[MAXNUMBER-1] = a->number[MAXNUMBER-1]&0x80 | a->number[MAXNUMBER-1]>>1;
	for(int i = MAXNUMBER-2;i >= 0;i--){
		lownext = a->number[i] & 0x01;
		low<<=7;
		a->number[i] = a->number[i]>>1 | low;
		low = lownext;
	}
}

//ֵ����
void GreatNumber::assign(GreatNumber *a,GreatNumber *b,bool isPower){
	if(!isPower)
		for(int i=0;i<=MAXNUMBER-1;i++)
			a->number[i] = b->number[i];
	else
		for(int i=0;i<=MAXPOWER-1;i++)
			a->power[i] = b->power[i];
}

//β����������֤��β��ΪС��
void GreatNumber::mantissaAlign(GreatNumber *a,GreatNumber *b){
	GreatNumber *one = new GreatNumber(), *dif = new GreatNumber();
	one->power[0] = 1;
	right1bit(a);
	binaryadd(a,one,true);		//a�Ľ����1,dif�����壬a�����������
}

//�������
void GreatNumber::subPower(GreatNumber *a,GreatNumber *b,GreatNumber *result){
	GreatNumber *negb = new GreatNumber;
	*negb = *b;
	binaryneg(negb,true);
	binaryadd(a, negb, result, true);
}

//�ȽϷ���λ
bool GreatNumber::signCmp(GreatNumber *r,GreatNumber *y){
	return (r->number[MAXNUMBER-1]&0x80 ^ y->number[MAXNUMBER-1]&0x80);
}

//β�����,resultΪ����
void GreatNumber::div(GreatNumber *r,GreatNumber *y,GreatNumber *result){
	GreatNumber *negy = new GreatNumber();
	*negy = *y;
	binaryneg(negy,false);		//��y�ĸ�
	unsigned char mark;
	for(int i = MAXNUMBER -1;i >= 0; i--){//MAXNUMBER -2
		for(int j = 0; j < BYTE; j++){
			if(signCmp(r,y)){				//����r�ͳ���y�������0,����r = 2*r+y
				/*mark = 0x7F;
				result->number[i] &= ROR(mark,j);*/
				left1bit(r);
				if(equZero(r, false))
					return;
				binaryadd(r,y,false);
			}
			else{
				mark = 0x80;
				result->number[i] |= ROR(mark,j);
				if(equZero(r, false))
					return;
				left1bit(r);
				binaryadd(r,negy,false);
			}
		}
	}
}

//����У��
void GreatNumber::quotientRevise(GreatNumber *result){
	result->number[MAXNUMBER-1] ^= 0x80;		//����λ�䷴
	result->number[0] |= 0X01;		//ĩλ����1
}

//���������
void GreatNumber::floatDiv(GreatNumber *a,GreatNumber *b,GreatNumber *result){
	GreatNumber *ta = new GreatNumber();
	*ta = *a;
	if(equZero(b,false)){		//����0��
		printf("error! can't be divided by zero!!!\n");exit(0);}
	if(equZero(ta,false)){		//���Ա������Ƿ�Ϊ0��������
		for(int i = 0;i < MAXNUMBER;i++)
			result->number[i] = 0;		//���ֱ��Ϊ0
		return;
	}
	//ȷ���̵ķ���λ
	//char as = ta->number[MAXPOWER-1] & 0x80;
	//char bs = b->number[MAXPOWER-1] & 0x80;
	//if((as ^ bs) == 0)
	//	result->number[MAXPOWER-1] &= 0;
	//else
	//	result->number[MAXPOWER-1] &= 0x80;
	//β������
	mantissaAlign(ta,b);
	//�������
	subPower(ta,b,result);
	//β�����
	div(ta,b,result);	
	//����У��
	quotientRevise(result);
	normalize(result);
}

//�Щ�
bool GreatNumber::equZero(GreatNumber* a, bool isPower)
{
	if(isPower)
	{
		for (int i = 0; i < MAXPOWER; i++)
			if(a->power[i]!=0) return false;
		return true;
	}
	else
	{
		for (int i = 0; i < MAXNUMBER; i++)
			if(a->number[i]!=0) return false;
		return true;
	}
}

//�Խ�����
void GreatNumber::right(GreatNumber *a, GreatNumber *b, GreatNumber *dif)
{
	GreatNumber *one = new GreatNumber();
	GreatNumber *r = new GreatNumber();
	one->power[0]=1;
	if(dif->power[MAXPOWER-1]&0x80)  // difΪ����
	{
		while(!equZero(dif,true))
		{
			right1bit(a);
			binaryadd(dif,one,r,true);
			for (int i = 0; i < MAXPOWER; i++)
				dif->power[i] = r->power[i];
		}
	}
	else
	{
		binaryneg(dif,true);
		while(!equZero(dif,true))
		{
			right1bit(b);
			binaryadd(dif,one,r,true);
			for (int i = 0; i < MAXPOWER; i++)
				dif->power[i] = r->power[i];
		}
	}
}

//��������ӷ�
void GreatNumber::add(GreatNumber *a,GreatNumber *b,GreatNumber * result)
{
	GreatNumber *one = new GreatNumber();
	GreatNumber *ta = new GreatNumber();
	GreatNumber *tb = new GreatNumber();
	one->power[0] =1;
	right1bit(a);
	binaryadd(a,one,ta,true);
	assign(a,ta,true);
	right1bit(b);
	binaryadd(b,one,tb,true);
	assign(b,tb,true);
	align(a,b,result);
	right(a,b,result);
	binaryadd(a,b,result,false);
	assign(result,a,true);
	normalize(result);
}

//���
void GreatNumber::normalize(GreatNumber *a)
{
	GreatNumber *negOne = new GreatNumber();
	negOne->power[0]=1;
	binaryneg(negOne, true);
	for (int i = 0; i < MAXNUMBER*8; i++)
	{
		if(((a->number[MAXNUMBER-1]&0x80)>>7)^((a->number[MAXNUMBER-1]&0x40)>>6)) break;
		else
		{
			left1bit(a);
			binaryadd(a,negOne,true);
		}
	}
}

//��������˷�
void GreatNumber::mul(GreatNumber *a, GreatNumber *b, GreatNumber *result)
{
	GreatNumber *one = new GreatNumber();
	one->power[0] = 1;
	right1bit(a);
	binaryadd(a,one,true);
	right1bit(b);
	binaryadd(b,one,true);

	unsigned char mark = 0x80;
	unsigned char asign = a->number[MAXNUMBER-1] & mark;
	unsigned char bsign = b->number[MAXNUMBER-1] & mark;

	if (asign == 1 && bsign == 0)//a�Ǹ���
	{
		binaryneg(a,false);
		binarymul(a,b,result);
		binaryneg(result,false);
		binaryadd(a,b,result,true);
	}

	else if (asign == 0 && bsign == 1)
	{
		binaryneg(b,false);
		binarymul(a,b,result);
		binaryneg(result,false);
		binaryadd(a,b,result,true);
	}

	else if (asign == 1 && bsign == 1)
	{
		binaryneg(a,false);
		binaryneg(b,false);
		binarymul(a,b,result);
		binaryadd(a,b,result,true);
	}

	else
	{
		binarymul(a,b,result);
		binaryadd(a,b,result,true);
	}
	binaryadd(result,one,true);
	normalize(result);
}

//��Ϊ����ʱ�Ķ����Ʊ�ʾ�ĳ˷�
void GreatNumber::binarymul(GreatNumber *a, GreatNumber *b, GreatNumber *result)
{
	GreatNumber *newA = new GreatNumber();
	*newA = *a;//������λʱ���Ͳ��øı�a��ֵ��
	unsigned char mark = 1;

	for(int i=0; i<MAXNUMBER; i++)
	{
		for (int j=0; j<BYTE; j++)
		{
			unsigned char b_bit = b->number[i] & mark;
			if (b_bit)
			{
				binaryadd(result,newA,false);
				right1bit(result);
			} 
			else right1bit(result);
			mark = ROL(mark);
		}
	}
}
//�ַ�������
void GreatNumber::load(string s, long number, GreatNumber* b)
{
	for (int i = MAXNUMBER-1; i >= 0; i--)
	{
		string p = s.substr((MAXNUMBER-i-1)*BYTE, BYTE);
		for (int j = 0 ; j < BYTE; j++)
		{
			b->number[i] |= (p[j]-'0')<<(BYTE - j - 1);
		}
	}
	*(long*)b->power = number;
	if(number<0) 
	for (int i = 8; i < MAXPOWER; i++)
	{
		b->number[i] = 0xFF;
	}
}

//����������

GreatNumber GreatNumber::operator=(string s)
{
	this->Initialize();
	long numberLength;
	bool isPositive;
	string binaryString = StringNumber::ManipulateString(s,numberLength, isPositive);
	load(binaryString ,numberLength, this);
	if(!isPositive)binaryneg(this, false);
	normalize(this);
	return *this;
}

GreatNumber GreatNumber::operator=(GreatNumber b)
{
	assign(this,&b,true);
	assign(this,&b,false);
	return *this;
}

GreatNumber GreatNumber::operator+(GreatNumber b)
{
	GreatNumber *result = new GreatNumber();
	GreatNumber *tb = new GreatNumber();
	assign(tb,&b,true);
	assign(tb,&b,false);

	add(this,tb,result);

	assign(this,result,true);
	assign(this,result,false);
	delete result;
	delete tb;
	return *this;
}

GreatNumber GreatNumber::operator-(GreatNumber b)
{
	GreatNumber *result = new GreatNumber();
	GreatNumber *tb = new GreatNumber();
	assign(tb,&b,true);
	assign(tb,&b,false);

	binaryneg(tb, false);
	add(this,tb,result);

	assign(this,result,true);
	assign(this,result,false);
	delete result;
	delete tb;
	return *this;
}

GreatNumber GreatNumber::operator*(GreatNumber b)
{
	GreatNumber *result = new GreatNumber();
	GreatNumber *tb = new GreatNumber();
	assign(tb,&b,true);
	assign(tb,&b,false);

	mul(this,tb,result);

	assign(this,result,true);
	assign(this,result,false);
	delete result;
	delete tb;
	return *this;
}

GreatNumber GreatNumber::operator/(GreatNumber b)
{
	GreatNumber *result = new GreatNumber();
	GreatNumber *tb = new GreatNumber();
	assign(tb,&b,true);
	assign(tb,&b,false);

	floatDiv(this,tb,result);

	//assign(this,result,true);
	//assign(this,result,false);
	//delete result;
	//delete tb;
	//return *this;
	return *result;
}