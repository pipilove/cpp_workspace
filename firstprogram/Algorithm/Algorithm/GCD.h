//最大公倍数算法（欧几里得算法，辗转相乘法）

/*int gcd(int x,int y){ 
	while (x!=y){ 
		if (x>y) x=x-y; 
		else 
			y=y-x; 
	} 
	return x;
} */

int temp;
int gcd(int x,int y){
	while(y>0){
		temp=y%x;
		x=y;
		y=temp;
	}
	return x;
}