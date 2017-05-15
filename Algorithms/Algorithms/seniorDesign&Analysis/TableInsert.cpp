///*	amortized analysis - Table Insert	2014.1.6	皮皮		*/
#include "TableInsert.h"
//模板类的声明和实现就目前的编译器来说最好不要分开文件，都在h文件里写
//或者在main.cpp 文件中包含"List.cpp"文件

//constructor
template<class ItemType>
Table<ItemType>::Table(int size){
	this->size = size;
	this->num = 0;
	table = new ItemType[size];
}

template <class ItemType>
void Table<ItemType>::tableInsert(ItemType x){	//Table<ItemType>::
	if(size == 0){
		table = new ItemType;
		size = 1;
	}
	else if(num == size){
		ItemType *newTable = new ItemType[2*size];
		for(int i = 0;i <= num-1;i++)			
			newTable[i] = table[i];
		delete table;
		table = newTable;
		size = 2*size;
	}
	table[num] = x;
	num++;
}
