/*	函数调用和局部变量-子函数返回大字节数据	
struct myrd{
	int i1;
	int i2;
};

myrd myfunc();
myrd r;

void main(){
	//myrd r;
	r=myfunc();
}

myrd myfunc(){
	myrd r1;
	r1.i1=1;
	r1.i2=2;
	return r1;
}
*/