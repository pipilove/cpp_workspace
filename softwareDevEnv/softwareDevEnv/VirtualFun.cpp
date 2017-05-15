//#include <stdio.h>
//
//class A{
//public:
//	virtual void finish(){
//		printf("a finish \n");
//	}
//	virtual void work(){
//		printf("a work \n");
//	}
//};
//
//class B:public A{
//public:
//	virtual void finish(){
//		printf("b finish \n");
//	}
//};
//
//class C:public A{
//public:
//	virtual void finish(){
//		printf("c finish \n");
//	}
//};
//
//int main(){
//	A* p1,* p2;
//	A a;
//	B b;
//	B* b = new B;
//	C* c = new C;
//	int temp;
//	temp =(int) &b+4;
//
//	(int)( &b+4 ) = (int) &c+4;
//	(int)( &c+4 ) = temp;
//
//	b->finish();
//	c->finish();
//	return 0;
//}