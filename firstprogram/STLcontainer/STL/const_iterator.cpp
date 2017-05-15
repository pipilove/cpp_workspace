#include <vector>
#include <iostream>
#include <ctime>
using namespace std;
int main()  {
	vector<int> v; 
	v.push_back(1);	
	v.push_back(2); 
	v.push_back(3);  
	v.push_back(4);

	vector<int>::const_iterator i;   //常量迭代器
	for( i = v.begin(); i != v.end(); i ++ ) 
		cout << * i << ",";
	cout << endl;

	vector<int>::reverse_iterator r;  //反向迭代器
	for( r = v.rbegin(); r != v.rend(); r++ ) 
		cout << * r << ",";
	cout << endl;

	vector<int>::iterator j;   //非常量迭代器
	for( j = v.begin();j != v.end();j ++ ) 
		* j =  100;
	for( i = v.begin();i != v.end();i++ ) 
		cout << * i << ",";

	clock_t now = clock();
	while(clock() - now < 5000);
}