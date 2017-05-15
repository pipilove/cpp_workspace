/****************************************************************************/
/*	 POJ����ʼ�2.5 ���� װ������1017			ƤƤ 2014-7-3					*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

void encase(){
	int case_count;
	int rectangle[6];					//for the num of rectangle 1~6
	int space[2];						//for the remain space rectangle 1 2

	while(1){
		case_count = 0;
		memset(space, 0, sizeof(space) );//ÿ�ζ�Ҫ���
		scanf("%d %d %d %d %d %d", &rectangle[0], &rectangle[1], &rectangle[2], &rectangle[3], &rectangle[4], &rectangle[5]);
		if( !(rectangle[0] || rectangle[1] || rectangle[2] || rectangle[3] || rectangle[4] || rectangle[5]) )
			break;						//����0 0 0 0 0 0�˳�

		//����Ҫһ������װ��6*6���Σ�5*5����ʣ��11��1*1��4*4����ʣ��5��2*2
		case_count += rectangle[5] + rectangle[4] + rectangle[3];
		space[0] += 11 * rectangle[4];
		space[1] += 5 * rectangle[3];

		//3*3���α���Ҫһ������װ��ʣ��5��2*2+7��1*1 �� 3��2*2+5��1*1 �� 1��2*2+3��1*1
		case_count += (rectangle[2] + 3)/4;	//����ȡ��������
		if( rectangle[2] % 4 ){				//������
			space[1] += 7 - (rectangle[2] % 4) * 2;
			space[0] += 8 - rectangle[2] % 4;
		}

		if( space[1] >= rectangle[1])	//2*2���ο�����������ʣ�µ�2*2spaceװ��װ����ļ����ӣ�����ʣ�µĶ�ת��Ϊ1*1��
			space[0] += (space[1] - rectangle[1]) * 4;
		else{
			case_count += (rectangle[1] - space[1] + 8) / 9;
			if( (rectangle[1] - space[1]) % 9 )
				space[0] += (9 - (rectangle[1] - space[1]) % 9) * 4;
		}

		if( space[0] < rectangle[0])	//1*1���ο�����������ʣ�µ�1*1spaceװ��װ����ļ����ӣ�����ʣ�µľ�ֻ�ܿ�����
			case_count += (rectangle[0] - space[0] + 35) / 36;

		printf("%d\n", case_count);
	}
}

int __15646main(){
	encase();
	return 0;
}
