#pragma once
#include<string>
#define MAXNUMBER 250
#define MAXPOWER 16
#define BYTE 8
class StringNumber
{
public:
	StringNumber(void);
	~StringNumber(void);
	static std::string ManipulateString(std::string s, long &length, bool &isPositive);
private:
	static std::string div2(std::string s);
	static bool equZero(std::string s);
	static std::string mul2(std::string s, long interLength);
};
