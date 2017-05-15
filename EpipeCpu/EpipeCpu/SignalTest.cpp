#include "Signal.h"
using namespace std;

int __main(){
	Signal s;
	s = 0x1234;
	cout<<hex<<s.value<<endl;

	Signal s1 = s.sub(5,0);
	cout<<s1.value<<endl;
	system("pause");
	return 0;
}
