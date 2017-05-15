#include  "greatnumber.h"
using namespace std;

void GreatNumber::Initialize()
{
	for (int i = 0; i < MAXNUMBER; i++) this->number[i] = 0;
	for (int i = 0; i < MAXPOWER; i++) this->power[i] = 0;
}

//部分加法
void GreatNumber::binaryadd(GreatNumber *a, GreatNumber *b, GreatNumber *result, bool isPower){
	//位操作标识
	unsigned char mark = 1;
	//进位标识
	unsigned char C0 = 0;
	//加法过程
	//对每一个char（注意小端机是从左到右)
	unsigned char ca, cb, p, g;
	if(!isPower)
	{
		for(int i = 0; i<MAXNUMBER; i++)
		{
			//分别按位操作
			for(int j = 0; j<BYTE; j++)
			{
				ca = a->number[i] & mark;
				cb = b->number[i] & mark;
  				p = ca ^ cb;
  				g = ca & cb;
				//将结果放进result
				result->number[i] |= p ^ C0;
				//计算进位结果
				C0 = g | (p & C0);
				//进位结果左移，使得对其下一位
				C0 = ROL(C0);
				//标志位左移，使得对其下一位
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

//部分加法重载
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

//求逆
void GreatNumber::binarynot(GreatNumber *a, bool isPower)
{
	if(isPower)
		for(int i = 0; i<MAXPOWER; i++)
			a->power[i] = ~a->power[i];
	else
		for(int i=0;i<MAXNUMBER;i++)
			a->number[i]=~a->number[i];
}

//求相反数
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

//对阶
void GreatNumber::align(GreatNumber *a, GreatNumber *b, GreatNumber *dif)
{
	GreatNumber * t = new GreatNumber();
	bool isamax = 0;
	unsigned char mark = 0x80;
	assign(t,b,true);
	binaryneg(t, true);
	binaryadd(a, t, dif, true);
	if(dif->power[MAXPOWER-1]&mark)  // dif为负数
		for(int i =0; i < MAXPOWER; i++) a->power[i] = b->power[i];
	else
		for(int i =0; i < MAXPOWER; i++) b->power[i] = a->power[i];
}

//左移一位
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

//右移一位
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

//值拷贝
void GreatNumber::assign(GreatNumber *a,GreatNumber *b,bool isPower){
	if(!isPower)
		for(int i=0;i<=MAXNUMBER-1;i++)
			a->number[i] = b->number[i];
	else
		for(int i=0;i<=MAXPOWER-1;i++)
			a->power[i] = b->power[i];
}

//尾数调整，保证商尾数为小数
void GreatNumber::mantissaAlign(GreatNumber *a,GreatNumber *b){
	GreatNumber *one = new GreatNumber(), *dif = new GreatNumber();
	one->power[0] = 1;
	right1bit(a);
	binaryadd(a,one,true);		//a的阶码加1,dif无意义，a阶码可能上溢
}

//阶码相减
void GreatNumber::subPower(GreatNumber *a,GreatNumber *b,GreatNumber *result){
	GreatNumber *negb = new GreatNumber;
	*negb = *b;
	binaryneg(negb,true);
	binaryadd(a, negb, result, true);
}

//比较符号位
bool GreatNumber::signCmp(GreatNumber *r,GreatNumber *y){
	return (r->number[MAXNUMBER-1]&0x80 ^ y->number[MAXNUMBER-1]&0x80);
}

//尾数相除,result为假商
void GreatNumber::div(GreatNumber *r,GreatNumber *y,GreatNumber *result){
	GreatNumber *negy = new GreatNumber();
	*negy = *y;
	binaryneg(negy,false);		//求y的负
	unsigned char mark;
	for(int i = MAXNUMBER -1;i >= 0; i--){//MAXNUMBER -2
		for(int j = 0; j < BYTE; j++){
			if(signCmp(r,y)){				//余数r和除数y异号则商0,余数r = 2*r+y
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

//假商校正
void GreatNumber::quotientRevise(GreatNumber *result){
	result->number[MAXNUMBER-1] ^= 0x80;		//符号位变反
	result->number[0] |= 0X01;		//末位恒置1
}

//浮点数相除
void GreatNumber::floatDiv(GreatNumber *a,GreatNumber *b,GreatNumber *result){
	GreatNumber *ta = new GreatNumber();
	*ta = *a;
	if(equZero(b,false)){		//测试0除
		printf("error! can't be divided by zero!!!\n");exit(0);}
	if(equZero(ta,false)){		//测试被除数是否为0，简化运算
		for(int i = 0;i < MAXNUMBER;i++)
			result->number[i] = 0;		//结果直接为0
		return;
	}
	//确定商的符号位
	//char as = ta->number[MAXPOWER-1] & 0x80;
	//char bs = b->number[MAXPOWER-1] & 0x80;
	//if((as ^ bs) == 0)
	//	result->number[MAXPOWER-1] &= 0;
	//else
	//	result->number[MAXPOWER-1] &= 0x80;
	//尾数调整
	mantissaAlign(ta,b);
	//阶码相减
	subPower(ta,b,result);
	//尾数相除
	div(ta,b,result);	
	//假商校正
	quotientRevise(result);
	normalize(result);
}

//判〇
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

//对阶右移
void GreatNumber::right(GreatNumber *a, GreatNumber *b, GreatNumber *dif)
{
	GreatNumber *one = new GreatNumber();
	GreatNumber *r = new GreatNumber();
	one->power[0]=1;
	if(dif->power[MAXPOWER-1]&0x80)  // dif为负数
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

//基本浮点加法
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

//规格化
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

//基本浮点乘法
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

	if (asign == 1 && bsign == 0)//a是负数
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

//均为正数时的二进制表示的乘法
void GreatNumber::binarymul(GreatNumber *a, GreatNumber *b, GreatNumber *result)
{
	GreatNumber *newA = new GreatNumber();
	*newA = *a;//这样移位时，就不用改变a的值了
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
//字符串加载
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

//操作符重载

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