/****************************************************************************/
/*	 POJ读书笔记2.5 —— 装箱问题1017			皮皮 2014-7-3					*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

void encase(){
	int case_count;
	int rectangle[6];					//for the num of rectangle 1~6
	int space[2];						//for the remain space rectangle 1 2

	while(1){
		case_count = 0;
		memset(space, 0, sizeof(space) );//每次都要清空
		scanf("%d %d %d %d %d %d", &rectangle[0], &rectangle[1], &rectangle[2], &rectangle[3], &rectangle[4], &rectangle[5]);
		if( !(rectangle[0] || rectangle[1] || rectangle[2] || rectangle[3] || rectangle[4] || rectangle[5]) )
			break;						//输入0 0 0 0 0 0退出

		//必须要一个箱子装：6*6矩形，5*5矩形剩下11个1*1，4*4矩形剩下5个2*2
		case_count += rectangle[5] + rectangle[4] + rectangle[3];
		space[0] += 11 * rectangle[4];
		space[1] += 5 * rectangle[3];

		//3*3矩形必须要一个箱子装，剩下5个2*2+7个1*1 或 3个2*2+5个1*1 或 1个2*2+3个1*1
		case_count += (rectangle[2] + 3)/4;	//向上取整！！！
		if( rectangle[2] % 4 ){				//另解见书
			space[1] += 7 - (rectangle[2] % 4) * 2;
			space[0] += 8 - rectangle[2] % 4;
		}

		if( space[1] >= rectangle[1])	//2*2矩形可以用箱子中剩下的2*2space装，装不完的加箱子，再有剩下的都转化为1*1的
			space[0] += (space[1] - rectangle[1]) * 4;
		else{
			case_count += (rectangle[1] - space[1] + 8) / 9;
			if( (rectangle[1] - space[1]) % 9 )
				space[0] += (9 - (rectangle[1] - space[1]) % 9) * 4;
		}

		if( space[0] < rectangle[0])	//1*1矩形可以用箱子中剩下的1*1space装，装不完的加箱子，再有剩下的就只能空着了
			case_count += (rectangle[0] - space[0] + 35) / 36;

		printf("%d\n", case_count);
	}
}

int __15646main(){
	encase();
	return 0;
}
