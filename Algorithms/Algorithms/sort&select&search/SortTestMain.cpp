//*	测试排序的main函数	*/
const int LEN  = 50;	//定义要排序的数组的大小
const int LOWER= 1;	//定义要排序的数组的最小值
const int UPPER= 10000;	//定义要排序的数组的最大值

#include "mySortDefine.h"
#include "InsertionSort.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "CountingSort.h"
#include "RadixSort.h"
#include "RandomizedSelect.h"

void showDatagenerateMode();
void showSortMode();
int dataGenerate(int* A);
short sortData(int* A,int* B,int A_length);
void saveAndPrint(int* A,int* B,int A_length,short sortDataSelectFlag);

int __151514main(){
	int A[LEN],B[LEN];

	int A_length = dataGenerate(A);	//返回生成数组的长度
	system("cls");
	short sortDataSelectFlag = sortData(A,B,A_length);	//返回标志判断选择的为conntingSort还是randomizedSelect还是其它
	if(sortDataSelectFlag != 2)saveAndPrint(A,B,A_length,sortDataSelectFlag);
	return 0;
}

void showDatagenerateMode(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);	//system("color 2");system("color F");
	printf("please input the Generation methods that the array need to sort:\n\n");
	printf("1 Randomly generate and save into file in.txt\n");
	printf("2 use the privious data in file in.txt that generate randomly\n");
	printf("3 manually generate and save into file in.txt\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
}

void showSortMode(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	printf("\nplease input the way of sort :\n\n");
	printf(" 1 for insertionsort          \t   2 for heapsort\n"           );
	printf(" 3 for quickSort              \t   4 for randomizedQuickSort\n");
	printf(" 5 for midRandomizedQuickSort \t   6 for hoareQuickSort\n"     );
	printf(" 7 for countingSort           \t   8 for radixSort\n"        );
	printf(" 9 for RandomizedSelect       \t   others for input again\n\n" );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
}

int dataGenerate(int* A){
	int A_length;
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
		switch(casechoice){
		case 1:{//生成随机数存入in.txt
			if((fp=fopen("in.txt","w"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("the data generates randomly is saving into in.txt ...... ");
			srand((unsigned)time(0));
			for(int k=0;k<LEN;k++){
				//srand(getpid());	//相同元素数组的排序
				A[k]=random(LOWER,UPPER);
				fprintf(fp,"%d ",A[k]);
				//printf("%d ",A[k]);
			}
			A_length = LEN;
			printf("\n");break;}

		case 2:{//从in.txt中取出随机数
			if((fp=fopen("in.txt","r"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("the data gets from in.txt is assign to array A ...... ");
			int k=0;
			while(!feof(fp)){										//A_length不知道的时候呢？？？
				fscanf(fp,"%d ",&A[k++]);
				//printf("%d ",A[k]);
			}
			A_length = k;
			printf("\n\n");break;}

		case 3:{//手动输入
			if((fp=fopen("in.txt","w"))==NULL){
				printf("can't open the file in.txt !!!\n");system("pause");exit(0);}
			printf("please input the data you want to sort(end when the data input is illegal) :\n");
			int k=0;
			while(scanf("%d ",&A[k])){		//以输入一个非法数据结束！！！
				//printf("A[%d] = %d  ",k,A[k]);
				fprintf(fp,"%d ",A[k++]);
			}
			fflush(stdin);	//清除stdin中的非法数据
			A_length = k;
			printf("the data input is saving into in.txt ...... \n");
			Sleep(1000);break;}

		default :
			//fflush(stdin);	//清除输入的非法字符！
			printf("input wrong num,please input again ......\n");
			Sleep(1000);
			input_flag=1;
			system("cls");break;
		}
	}while(input_flag);

	fclose(fp);
	return A_length;
}

short sortData(int* A,int* B,int A_length){
	bool input_flag;	//输入正误判断标志
	short sortDataSelectFlag=0;
	int startTime;
	do{
		showSortMode();
		input_flag=0;

		int casechoice;
		scanf("%d",&casechoice);
		startTime=clock();
		switch(casechoice){
		case 1://插入排序：
			insertionSort(A,A_length);break;

		case 2://堆排序测试：
			heapSort(A,A_length);break;

		case 3://quickSort快排测试：
			quickSort(A,0,A_length-1);break;
		case 4://randomizedQuickSort
			randomizedQuickSort(A,0,A_length-1);break;
		case 5://midRandomizedQuickSort
			midRandomizedQuickSort(A,0,A_length-1);break;
		case 6://hoareQuickSort
			hoareQuickSort(A,0,A_length-1);break;

		case 7:{//计数排序：
			countingSort(A,B,LOWER,UPPER,A_length);
			sortDataSelectFlag=1;}break;

		case 8:{//基数排序：
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			if(LOWER<0){printf("the array must be positive number ...\n ");system("pause");exit(0);};	//基数排序不能为负
			printf("please input the value of radix ... \n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
			int radix;
			scanf("%d",&radix);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
			int keynum = 0;
			int maxNum = randomizedSelect(A,0,A_length-1,A_length);	//printf("maxNum is %d\n",maxNum);
			while(maxNum){	//通过radix计算出每个数的关键字数（位数）
				maxNum /= radix;
				keynum++;
			}printf("\nthe keynum of the array is %d\n",keynum);
			startTime=clock();	//除去输入radix and keynum的时间
			radixSort(A,A_length,radix,keynum);}break;
			/*initialization of 'radix''keynum' is skipped by 'default'
			You cannot jump past a declaration with an initializer unless the declaration is enclosed in a block. 
			(Unless it is declared within a block, the variable is within scope until the end of the switch statement.) */

		case 9:{//选择第pos大的数（1最小）
			int pos = A_length;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			printf("please input the posth max indix pos (1-%d):\n",A_length);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
			do{
				scanf("%d",&pos);
				if(pos<=A_length&&pos>=1)break;
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);
					printf("input error , please input again ... \n");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
				}
			}while(1);
			startTime=clock();
			int selectNum = randomizedSelect(A,0,A_length-1,pos);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
			printf("the %dth max num in A is : %d\n",pos,selectNum);
			sortDataSelectFlag = 2;
			   }break;

		default:
			fflush(stdin);
			printf("input error,please input again ......\n");
			Sleep(1000);
			input_flag=1;
			system("cls");break;
		}
	}while(input_flag);	
	int endTime=clock();
	printf("\nthe running time is: %d\n\n",endTime-startTime);
	system("pause");
	system("cls");
	return sortDataSelectFlag;
}

void saveAndPrint(int* A,int* B,int A_length,short sortDataSelectFlag){
	//将排好序的数组存入out.txt
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
	FILE* fp;
	if((fp=fopen("out.txt","w"))==NULL){
		printf("can't open the file!!!\n");system("pause");exit(0);}
	printf("\nthe sorted array is :\n");
	if(!sortDataSelectFlag)	//for计数排序
		for(int k=0;k<A_length;k++){
			fprintf(fp,"%d ",A[k]);
			printf("%d ",A[k]);
		}
	else{
		for(int k=0;k<A_length;k++){
			fprintf(fp,"%d ",B[k]);
			printf("%d   ",B[k]);
		}}
	printf("\n\nthe data sorted is saving into out.txt ...... \n\n");
	fclose(fp);	
	system("pause");
}
