///*	hashTable 2014.3.2	ƤƤ		*/
#include "HashTable.h"
using namespace std;

hashTable::hashTable(int size){
	this->size0 = size;	//初始化hashTable大小
	nil.key = -1;	//初始化空元素,NULL表示有值0,nil.key必须为一个相对无意义的数
	nil.pre = NULL;
	nil.next = NULL;
	nil.position = NULL;
	deleted.key = -2;	//distinguish from nil
	deleted.pre = NULL;
	deleted.next = NULL;
	deleted.position =NULL;

	table = new hashnode[size];
	for(int i = 0;i <= size-1;i++)	//初始化hashTable为nil
		table[i] = nil;
}
int hashTable::size(){
	return size0;
}

//direct addressing
hashnode hashTable::directAddressSearch(int k){
	return table[k];
}

void hashTable::directAddressInsert(hashnode& x){
	table[x.key] = x;
}

void hashTable::directAddressDelete(hashnode& x){
	table[x.key] = nil;
}

//open addressing
//prob sequence - double hashing
int hashTable::h(int k,int i){
	return (h1(k)+i*h2(k))%size0;
}
int hashTable::h1(int k){
	return k%size0;
}
int hashTable::h2(int k){
	return 1 + k%(size0-2);	//or size0-1...
}

int hashTable::hashInsert(ITEMTYPE k){
	int j;
	for(int i = 0;i <= size0-1;i++){
		j = h(k,i);
		if(equ(table[j],nil) || equ(table[j],deleted)){	//!!!hashTable实例不能直接比较
			table[j].key = k;
			table[j].position = j;
			return j;			//insert into jth slot
		}
	}
	cout<<"hashTable overflow ! "<<endl;
	system("pause");
	exit(0);
}
int hashTable::hashInsert(hashnode &x){
	int j,k;
	k = x.key;
	for(int i = 0;i < size0;i++){
		j = h(k,i);
		if(equ(table[j],nil)){	//!!!hashTable实例不能直接比较
			x.position = j;
			table[j] = x;
			return j;
		}
	}
	cout<<"hashTable overflow ! "<<endl;
	system("pause");
	exit(0);
}

hashnode hashTable::hashSearch(int k){
	int i=0,j;
	do{
		j = h(k,i);
		if(table[j].key == k){
			return table[j];
		}
		i++;
	}while(i <= size0-1 && !equ(table[j],nil));
	return nil;
}

bool hashTable::hashDelete(int k){
	int i = 0,j;
	do{
		j = h(k,i);
		if(table[j].key == k){
			table[j] = deleted;
			return true;
		}
		i++;
	}while(i <= size0-1 && !equ(table[j],nil));
	return false;	//delete fail
}

//展示hashTable
void hashTable::display(){
	cout<<"the keys in hashTable are : "<<endl;
	for(int i = 0;i <= size0-1;i++)
		cout<<left<<setw(4)<<i;		//set cout format
	cout<<endl;
	for(int i = 0;i <= size0-1;i++)
		cout<<left<<setw(4)<<table[i].key;
	cout<<endl;
}


bool equ(hashnode hashnode1,hashnode hashnode2){
	//position compare ???
	if(hashnode1.key == hashnode2.key &&hashnode1.next == hashnode2.next 
		&& hashnode1.pre == hashnode2.pre && hashnode1.position == hashnode2.position)
		return true;
	else
		return false;
}
