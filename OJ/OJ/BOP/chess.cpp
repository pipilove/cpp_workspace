/****************************************************************************/
/*			���֮��1.2 - �й����彫˧����		ƤƤ 2014-7-1				*/
/****************************************************************************/
#include <stdio.h>

typedef struct bitField{
	unsigned char a:4;
	unsigned char b:4;
}bit;


void chessTest1(){
	char column = 1;
	for(; column <=3 ; column ++){			//A����ѡ
		for(; column <= 9; column += 3){	//A����B������ѡ
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
		if(i/9 % 3 == i % 9 %3)	//i/9(A�ı��-1[0~8]) % 3(A����); i%9(B�ı��-1[8~0]) %3
			continue;			//ͬ����continue
		printf("A = %d, B = %d\n",i/9 + 1, i%9 + 1);
	}
}

void chessTest3(){
	bit i;	
	for(i.a = 1; i.a <= 9; i.a++)
		for(i.b = 1; i.b <= 9; i.b ++)
			if(i.a%3 != i.b%3)	//A B��ͬ��
				printf("A = %d, B = %d\n", i.a, i.b);
}

void __5454main(){
	chessTest3();
}


