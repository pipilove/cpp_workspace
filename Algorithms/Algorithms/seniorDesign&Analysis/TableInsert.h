///*	amortized analysis - Table Insert	2014.1.6	皮皮		*/

template<class ItemType>
class Table{
public:
	int size;
	int num ;	//!
	ItemType *table;
public:
	Table(int = 10);	//initial the size of Table
	~Table(){
		delete[] table;
	}

	void tableInsert(const ItemType x);
};
