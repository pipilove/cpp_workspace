///*	hashTable 2014.3.2	皮皮		*/
#include "myDataStructDefine.h"

class hashnode{
public:
	ITEMTYPE key;
	int position;	//the position in hashTable
	hashnode* pre;
	hashnode* next;

};

class hashTable{
private:
	int size0;
	hashnode* table;
public:
	hashnode nil;	
	hashnode deleted;
public:
	hashTable(int size0 = 10);
	int size();	//返回hashTable大小
	//direct addressing
	hashnode directAddressSearch(int k);
	void directAddressInsert(hashnode& x);
	void directAddressDelete(hashnode& x);

	//open addressing
	//prob sequence - double hashing
	int h(int k,int i);
	int h1(int k);
	int h2(int k);
	
	int hashInsert(ITEMTYPE k);
	int hashInsert(hashnode &x);

	hashnode hashSearch(int k);

	bool hashDelete(int k);

	//展示hashTable
	void display();
};

//比较两个hashnode看是否相等
bool equ(hashnode tablej,hashnode nil);
