#include "GCD.h"

int lcm(int x,int y){
	return x/gcd(x,y)*y;
}