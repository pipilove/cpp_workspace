///*	测试高级数据结构的main函数	2013.12.21	皮皮		*/
#pragma once
#include <stdio.h>
#include <iostream>

#include <limits.h>
#include <stdlib.h>		//system
#include <Windows.h>	//set color
#include <time.h>

#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#define ITEMTYPE int
#define INFINATY INT_MAX
#define random(low,upper)((rand()*rand())%((upper)-(low)+1)+(low))

//if include .h file  states #define ITEMTYPE int,#define ITEMTYPE char is invalid
#include "CutRod.h"				//DP
#include "LCS.h"
#include "ActivitySelector.h"	//贪心算法
#include "TableInsert.cpp"		//扩张表
using namespace std;

const int LEN  = 6 ;	//定义要测试的数组的大小
const int LOWER= 1  ;	//定义要测试的数组的最小值
const int UPPER= 100;	//定义要测试的数组的最大值

static void showDatagenerateMode();
vector<ITEMTYPE> dataGenerate();
template <class T>
void printfArray(vector<T> A);
//
void testBottmoupCutRod(vector<ITEMTYPE> A);
void testCutRod(vector<ITEMTYPE> A);
void testLCS(vector<ITEMTYPE> A,vector<ITEMTYPE> F);
//
void testActivitySelector(multimap<int,int> actMultimap);
//
void testTableInsert(vector<ITEMTYPE> A);

int __646464main(){
	vector<ITEMTYPE> A;
	A = dataGenerate();	//返回生成随机数vector
	printf("array A is :\n");
	printfArray(A);
	printf("\n");

	//vector<ITEMTYPE> F;
	//F = dataGenerate();
	//printf("array F is :\n");
	//printfArray(F);
	//printf("\n");

	//test for activitySelector
	//multimap<int,int> actMultimap;
	//for(vector<int>::iterator aIt = A.begin(),fIt = F.begin();aIt != A.end();aIt++,fIt++)
	//	actMultimap.insert(make_pair(*fIt,*aIt));
	//make_pair;finish is the key,start is the value;
	//if map then the key(finish time)can't be dulplicated!!!
	//testActivitySelector(actMultimap);

	//test for bottomupCutRod()
	//testBottmoupCutRod(A);

	//test for cutRod()
	testCutRod(A);

	//test for matrixChainOrder,matrix num is A.size()-1
	//testMatrixChainOrder(A);
	//test for recursiveMatrixChain
	//testRecursiveMatrixChain(A);
	//test for memoizedMatirxChain
	//testMemoizedMatirxChain(A);

	//test for lcs
	//testLCS(A,F);

	//test for tableInsert
	//testTableInsert(A);

	printf("\n");
	system("pause");
	return 0;
}

static void showDatagenerateMode(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("please input the Generation methods for array:\n\n");
	printf("1 Randomly generate and save into file in.txt\n");
	printf("2 use the privious data in file in.txt that generate randomly\n");
	printf("3 manually generate and save into file in.txt\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
}
vector<ITEMTYPE> dataGenerate(){
	vector<ITEMTYPE> A;
	FILE* fp;
	bool input_flag;	//输入正误判断标志
	do{
		showDatagenerateMode();
		input_flag=0;
		int casechoice;
		//scanf("%d",&casechoice);
		while(scanf("%d",&casechoice) == 0){
			fflush(stdin);	//清除输入的非法数据！
			printf("input illegal,please input again ......\n");
		}
		cin.sync();			//清除cin缓冲区未读信息("\n")
		switch(casechoice){
		case 1:{//生成随机数存入in.txt
			if((fp=fopen("in.txt","w"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("the data generates randomly is saving into in.txt ...... ");
			srand((unsigned)time(0));
			int data;
			for(int k=0;k<LEN;k++){
				//srand(getpid());	//相同元素数组的排序
				data = random(LOWER,UPPER);
				A.push_back(data);
				fprintf(fp,"%d ",data);
				//printf("%d ",data);
			}
			printf("\n");break;}

		case 2:{//从in.txt中取出随机数
			if((fp=fopen("in.txt","r"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("the data gets from in.txt is assign to array A ...... ");
			int data;
			while(!feof(fp)){
				fscanf(fp,"%d ",&data);
				A.push_back(data);
				//printf("%d ",data);
			}
			printf("\n");break;}

		case 3:{//手动输入
			if((fp=fopen("in.txt","w"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("please input the data you want to sort(end when the data input is illegal) :\n");
			ITEMTYPE data;
			//while(scanf("%d ",&data)){
			while((data = cin.get()) != '\n'){		//input any format data,end with ctl+z and return false 2 cin
				cin.unget();
				cin>>data;
				A.push_back(data);
				//printf("data = %d  ",data);
				cout<<data<<" ";
				fprintf(fp,"%d ",data);
			}
			fflush(stdin);	//清除stdin中的非法数据
			cin.clear();	//set the state of stream as good
			printf("the data input is saving into in.txt ...... \n");
			Sleep(1000);break;}

		default :
			//fflush(stdin);
			printf("input wrong num,please input again ......\n");
			Sleep(1000);
			input_flag=1;
			system("cls");break;
		}
	}while(input_flag);

	fclose(fp);
	return A;
}
template <class T>
void printfArray(vector<T> A){		//没有&会修改iterator?
	vector<T>::const_iterator i;
	for(i = A.begin();i != A.end();i++)	//!=A.end() or vector itrator not dereferencable
		cout<<*i<<" ";
	cout<<endl;
}

//test for bottomupCutRod()
void testBottmoupCutRod(vector<int> A){
	result *res = bottomupCutRod(A.size(),A);
	for(int i = 0;i<=A.size();i++)
		printf("%d ",res->r[i]);
	printf("\n");
	for(int i = 0;i<=A.size();i++)
		printf("%d ",res->s[i]);
	for(int i = 0;i <= A.size();i++){
		printf("\nwhen length = %d :",i);
		cutRodSolution(i,res->s);
	}
}
//test for cutRod()
void testCutRod(vector<int> A){
	int * sForCutRod = new int[A.size()];
	printf("the best res is:\n");
	for(int i = 0;i<=A.size();i++)
		printf("%d ",cutRod(i,A,sForCutRod));
	for(int i = 0;i <= A.size();i++){
		printf("\nwhen length = %d :",i);
		cutRodSolution(i,sForCutRod);
	}
	printf("\n");
}


//test for lcs
void testLCS(vector<ITEMTYPE> X,vector<ITEMTYPE> Y){
	vector< vector<int> > B(X.size()+1);//record the optimal solution
	for(int i = 0;i <= X.size();i++)
		B[i].resize(Y.size()+1);
	/*for(int i = 0;i <= X.size();i++)	//original value is 0
		printfArray(B[i]);*/
	vector< vector<int> > Z = lcs(X,Y,B);
	printf("the optimal res is: %d\n",Z[X.size()][Y.size()]);
	printf("the optimal solution is:\n");
	printfLCS(B,X,X.size(),Y.size());
	printf("\nthe optimal solution without B is:\n");//为什么输出不同解？
	printfLCSZ(Z,X,X.size(),Y.size());
	printf("\n");
}

//test for activitySelector
void testActivitySelector(multimap<int,int> actMultimap){
	printf("array actMultimap.S is :\n");
	for(multimap<int,int>::iterator actMapIt = actMultimap.begin();actMapIt != actMultimap.end();actMapIt++)
		printf("%d ",actMapIt->second);
	printf("\narray actMultimap.F is :\n");
	for(multimap<int,int>::iterator actMapIt = actMultimap.begin();actMapIt != actMultimap.end();actMapIt++)
		printf("%d ",actMapIt->first);
	vector<int> res = activitySelector(actMultimap);
	printf("\n");
	printfArray(res);
}

//test for tableInsert
void testTableInsert(vector<ITEMTYPE> A){
	Table<ITEMTYPE>* table1 = new Table<ITEMTYPE>(5);
	for(int i= 0;i <= A.size()-1;i++){
		table1->tableInsert(A[i]);
		printf("table1->size = %d\n",table1->size);
	}
	printf("\n");
	for(int i= 0;i <= table1->size-1;i++)
		printf("table1->table[%d] = %d\n",i,table1->table[i]);
}
