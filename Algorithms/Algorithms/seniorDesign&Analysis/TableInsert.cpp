///*	amortized analysis - Table Insert	2014.1.6	ƤƤ		*/
#include "TableInsert.h"
//ģ�����������ʵ�־�Ŀǰ�ı�������˵��ò�Ҫ�ֿ��ļ�������h�ļ���д
//������main.cpp �ļ��а���"List.cpp"�ļ�

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
