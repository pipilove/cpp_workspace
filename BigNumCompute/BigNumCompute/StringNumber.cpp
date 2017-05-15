#include "StringNumber.h"

using namespace std;
StringNumber::StringNumber(void)
{
}


StringNumber::~StringNumber(void)
{
}

string StringNumber::ManipulateString(string s, long &length, bool &isPositive)
{
	string::size_type t;
	t = s.find('.');
	string inter = s.substr(0,t);
	bool positive;
	string bI = "", bP = "";
	if(inter[0] == '-')
	{
		positive = false;
		inter = inter.substr(1);
		bI = div2(inter);
	}
	else
	{
		positive = true;
		bI = div2(inter);
	}
	if(t!=s.npos) 
	{
		string poinr = s.substr(t+1);
		if(poinr.length()!=0)bP = mul2(poinr, bI.length());
	}
	string results = '0' + bI + bP;
	length = bI.length();
	return results;
}


string StringNumber::div2(string s)
{
	string binaryArray;
	for (int i = 0; i < s.length(); i++)
	{
		if(s[i]<'0'||s[i]>'9') return NULL;
	}
	int * m = new int[s.length()];
	while(true)
	{
		if(s[s.length()-1]%2!=0)binaryArray+='1';
		else binaryArray+='0';
		int i = 0;
		for (int j = 0; j < s.length(); j++) m[j] = 0;
		for (; i < s.length() -1; i++)
		{
			if(s[i]%2!=0) m[i+1]+=5;
			s[i]= (s[i] - '0') / 2  + '0';
		}
		s[i]= (s[i] - '0') / 2  + '0';
		for (int j = 0; j < s.length(); j++) s[j] += m[j];
		if(equZero(s)) break;
	}
	reverse(binaryArray.begin(), binaryArray.end());
	return binaryArray;
}

string StringNumber::mul2(string s, long interLength)
{
	string binaryArray;
	for (int i = 0; i < s.length(); i++)
	{
		if(s[i]<'0'||s[i]>'9') return NULL;
	}
	int * m = new int[s.length()];
	for (int k = 0; k < MAXNUMBER * BYTE - interLength -1 ; k++)
	{
		for (int j = 0; j < s.length(); j++) m[j] = 0;
		for (int i = s.length() - 1; i > 0; i--)
		{
			s [i] = (s[i]-'0')*2+'0';
			if(s[i]>'9')
			{
				s[i] -= 10;
				m[i-1] = 1;
			}
		}
		s [0] = (s[0] - '0') * 2 + '0';
		if(s[0]>'9')
		{
			s[0] -= 10;
			binaryArray += '1';
		}
		else binaryArray += '0';
		for (int j = 0; j < s.length(); j++) s[j] += m[j];
	}
	return binaryArray;
}

bool StringNumber::equZero(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if(s[i]>'0') return false;
	}
	return true;
}
