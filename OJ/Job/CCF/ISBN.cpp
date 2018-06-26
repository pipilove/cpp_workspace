//****************************************************************************/
//*	 CCF软件能力认证考试模拟题/bjfu - 1158 —— ISBN号码	皮皮 2014-8-31		*/
//****************************************************************************/
#include <assert.h>
#include <iostream>
#include <fstream>
using namespace std;

void ISBN(){
	int a[13];
	char c;
	char input[14];
	for(int i = 0, j = 0; i < 10; j++){
		cin >> c;
		input[j] = c;
		if( c != '-' ){
			if( c == 'X')
				a[i] = 10;
			else
				a[i] = c - '0';
			i++;
		}
	}

	int idCode = 0;
	for(int i = 0; i < 9; i++){
		a[i] *= i+1;
		idCode += a[i];
	}
	idCode %= 11;

	if( idCode == a[9] )
		cout<< "Right"<<endl;
	else{ 
		for(int j = 0; j < 12; j++)
			cout<<input[j];
		if( idCode == 10 )
			cout<<'X'<<endl;
		else
			cout<<idCode<<endl;
	}
}

int __35161651main(){
	//assert( freopen("CCF\\isbn.in", "r", stdin) );
	ISBN();
	//fclose(stdin);
	return 0;
}
