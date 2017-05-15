//c++��һ��ʵ��--p241
#include <iostream>

class Set{
private:
	int n;			//Set��Ԫ�صĸ���
	int *pS;		//��̬����Set�е�Ԫ��
public:
	Set(){
		n = 0;
		pS = NULL;
	}

	Set(Set &s){			//�������캯��
		n = s.n;
		if (n!= 0)
		{
			pS = new int [n];
			for (int i = 0; i<n; i++)
			{
				pS[i] = s.pS[i];
			}
		}
	}
	~Set()				//����������delete����̬�ڴ�
	{
		if (pS)
		{
			delete []pS;
			pS = NULL;
			n = 0;
		}
	}


	void ShowElement() const;
	bool IsEmpt();
	int size();
	void clear();
	bool IsElement(int e) const;

	bool IsSubset(const Set &s) const;

	bool IsEqual(const Set &s) const;

	Set & insert(int e);

	Set & deleteElement(int e);

	Set Union(const Set &s) const;

	Set intersection(const Set &s) const;

	Set difference(const Set &s) const;
};

