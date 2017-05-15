/****************************************************************************/
/*			 POJ����ʼ�2.4 ���� ���	2801	ƤƤ 2014-7-3					*/
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
	int N, M, P;			//������N�У� ÿ��M���ַ��� P�е���
	cin>>N>>M>>P;

	int char_count = N * M;	//���������ܹ�char_count���ַ�
	char c;
	while(char_count--){
		cin>>c;				//�Զ����Կո�
		grid.insert(c);
	}

	while(P--){				//�ܹ�P�������ַ���
		char* s =  new char(char_count);
		cin>>s;
		while(*s){
			grid.erase( grid.find(*s) );//ÿ��ֻɾ�����ҵ��ĵ�һ���ַ�
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

