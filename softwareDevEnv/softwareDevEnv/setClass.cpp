//强制偏移访问类中private变量
#include "stdio.h"
class Tes{
private:
	char a;
	int i;
	short s;
	char c2;
	short s2;
	char c3;
public:
	short getS2(){
		return s2;
	}
};

typedef struct test{
	char a;
	int i;
	short s;
	char c2;
	short s2;
	char c3;
}strtest;
int main(){
	Tes* test1 = new Tes();
	//short* offset = ((short*)tes1)+6;
	//*offset = 12;
	/*int* offset = (int*)test1+3;
	*(short*)offset = 12;*/

	(strtest*)test1= 12;


	
	printf("%d",test1->getS2());
}
