#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <functional>

using namespace std;

int count1(string);

int main(){
	string str1[]={"asayjk","bhjresaf","cebnmr","dttzlo","cqwsw","actrfs"};
	list<string> list_str(str1,str1+6);
	cout<<"In the list,the number of each letter is :"<<endl;
	for_each(list_str.begin(),list_str.end(),count1);
	system("pause");
}

int count1(string str1){
	int countor[27]={0};
	for(int i=1;i < str1.length();i++)
		if((str1[i]-96)==i)
			countor[i]++;
	for(int j=1;j<27;j++)
		cout<<countor[j]<<endl;
	return 1;
}
