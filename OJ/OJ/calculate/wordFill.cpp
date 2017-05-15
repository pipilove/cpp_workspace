/****************************************************************************/
/*			 POJ读书笔记2.4 —— 填词	2801	皮皮 2014-7-3					*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
void wordFill(){
	int alphabet[26];
	int N, M, P,i;
	char * s;
	memset(alphabet, 0, sizeof(alphabet) );
	scanf("%d %d %d",&N, &M, &P);
	s = (char*)malloc(M*sizeof(char));

	while(N--){
		scanf("%s",s);
		while(*s){
			alphabet[*s - 'A']++;
			s++;
		}
	}
	while(P--){
		scanf("%s",s);
		while(*s){
			alphabet[*s - 'A']--;
			s++;
		}
	}
	for(i = 0; i < 26; i++){
		while(alphabet[i]--){
			printf("%c",'A' + i);
		}
	}
}


#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

void print(char c){
	cout<<c;
}
void wordFill2(){
	multiset<char> grid;
	int N, M, P;			//方格盘N行， 每行M个字符， P行单词
	cin>>N>>M>>P;

	int char_count = N * M;	//方格盘中总共char_count个字符
	char c;
	while(char_count--){
		cin>>c;				//自动忽略空格
		grid.insert(c);
	}

	while(P--){				//总共P个单词字符串
		char* s =  new char(char_count);
		cin>>s;
		while(*s){
			grid.erase( grid.find(*s) );//每次只删除查找到的第一个字符
			s++;
		}
	}
	for_each(grid.begin(), grid.end(), print);
}


int __21484main(){
	wordFill();
	wordFill2();
	return 0;
}

