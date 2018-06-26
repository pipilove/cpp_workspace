//***************************************************/
//*		 ��Ȥ����	nyoj 85			ƤƤ 2014-9-7	*/
//***************************************************/
#include <assert.h>
#include <stdio.h>
#include <math.h>

static void funnyNum(){
	int n;
	scanf("%d", &n);								//n < 100,000

	int den = sqrt(float(n * 2));					//n != INT_MAX
	while(den*(den + 1) < n * 2)
		den++;
	int inc = n - den * (den - 1) / 2;
	if(den%2)
		printf("%d/%d\n", den + 1 - inc, inc);
	else
		printf("%d/%d\n", inc, den + 1 - inc);
}

static void funnyNum1(){  
	int m,d,s,g,i;
	scanf("%d", &d);								//d���� = INT_MAX
	s=g=0;  
	for(i=1;i<d;i++){								//�Ӻ�һֱ�ӵ�a*(a+1) > n
		s+=i;  
		if(s>=d) break;  
		g+=i;  
	}  
	if(i%2==0) 
		printf("%d/%d\n", d - g, i - (d - g - 1));
	else 
		printf("%d/%d\n", i - (d - g - 1), d - g);
}

int __514564165main(){
	assert( freopen("Math\\FunnyNum.in", "r", stdin) );
	int cases;
	scanf("%d", &cases);

	while(cases--){
		funnyNum();
		funnyNum1();
	}

	fclose(stdin);
	return 0;
}
