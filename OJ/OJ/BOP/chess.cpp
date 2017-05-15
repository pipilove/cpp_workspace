/****************************************************************************/
/*			编程之美1.2 - 中国象棋将帅问题		皮皮 2014-7-1				*/
/****************************************************************************/
#include <stdio.h>

typedef struct bitField{
	unsigned char a:4;
	unsigned char b:4;
}bit;


void chessTest1(){
	char column = 1;
	for(; column <=3 ; column ++){			//A的列选
		for(; column <= 9; column += 3){	//A（和B）的行选
			printf("A = %d, B = %d\n", column, column%3 + 1);
			printf("A = %d, B = %d\n", column, column%3 + 1 + 3);
			printf("A = %d, B = %d\n", column, column%3 + 1 + 6);
			printf("A = %d, B = %d\n", column, (column + 1)%3 + 1);
			printf("A = %d, B = %d\n", column, (column + 1)%3 + 1 + 3);
			printf("A = %d, B = %d\n", column, (column + 1)%3 + 1 + 6);
		}
		column -= 9;
	}
}

void chessTest2(){
	char i = 81;
	while(i--){
		if(i/9 % 3 == i % 9 %3)	//i/9(A的编号-1[0~8]) % 3(A的列); i%9(B的编号-1[8~0]) %3
			continue;			//同列则continue
		printf("A = %d, B = %d\n",i/9 + 1, i%9 + 1);
	}
}

void chessTest3(){
	bit i;	
	for(i.a = 1; i.a <= 9; i.a++)
		for(i.b = 1; i.b <= 9; i.b ++)
			if(i.a%3 != i.b%3)	//A B不同列
				printf("A = %d, B = %d\n", i.a, i.b);
}

void __5454main(){
	chessTest3();
}


