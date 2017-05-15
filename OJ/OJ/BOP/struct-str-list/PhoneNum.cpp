/****************************************************************************/
/*		BOP读书笔记3.2 - 电话号码对应英语单词		皮皮 2014-9-15				*/
/****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*	数字phone_num[i]第answer[i]个代表字符		*/
char pnt[10][5] = {		//会自动在每个字符串后加一个\0
	"",					//0
	"",					//1
	"ABC",				//2
	"DEF",				//3
	"GHI",				//4
	"JKL",				//5
	"MNO",				//6
	"PQRS",				//7
	"TUV",				//8
	"WXYZ"				//9
};
/*	0~9每个数字能表示的字符个数	*/
int total[10] = {0, 0, 3, 3, 3, 3, 3, 4, 3, 4};


/*	直接循环法（phone_len not fixed）	*/
static void phoneNum(int *phone_num, int phone_len){
	int *answer = (int *)malloc(sizeof(int) * phone_len);	//数字代表字符在能表示的字符串中的位置
	memset(answer, 0, sizeof(int) * phone_len);				//phonne_num中每个的num对应的字符从第0个开始

	//int count = 0;
	while(1){
		for(int i = 0; i < phone_len; i++)					//打印一轮phone_num能对应的字符串，i对应字符串第i个字符
			printf("%c", pnt[ phone_num[i] ][ answer[i] ]);
		printf("\n");
		//count ++;

		int k = phone_len - 1;
		while( k >= 0 ){
			if(answer[k] < total[ phone_num[k] ] - 1){
				answer[k]++;
				break;
			}else
				answer[k--] = 0;
		}
		if( k < 0 ){			
			//printf("counter = %d\n", count);
			break;
		}
	}
}

int answer[10];											//位置:数字代表字符在能表示的字符串中的位置
static int count = 0;
/*	递归算法	*/
static void recursivePhoneNum(int *phone_num, int index, int phone_len){
	if(index == phone_len){
		for(int i = 0; i < phone_len; i++)
			printf("%c", pnt[ phone_num[i] ][ answer[i] ]);
		printf("\n");
		count++;
	}else{
		for(answer[index] = 0; answer[index] < total[ phone_num[index] ]; answer[index]++)	//第index位要打印total[ phone_num[index]次
			recursivePhoneNum(phone_num, index + 1, phone_len);	//第index位每打印1次，index+1位要打印index+1对应的次数；其中phone_len-1位直接打印
	}
}


int __5418465498main(){
	assert( freopen("BOP\\结构 - 字符串及链表\\PhoneNum.in", "r", stdin) );
	int phone_len;
	scanf("%d", &phone_len);

	int phone_num[10];
	//int *phone_num = (int *)malloc(sizeof(int) * phone_len);
	for(int i = 0; i < phone_len; i++)
		scanf("%d", &phone_num[i]);

	//phoneNum(phone_num, phone_len);

	recursivePhoneNum(phone_num, 0, phone_len);
	printf("%d", count);

	fclose(stdin);
	return 0;
}
