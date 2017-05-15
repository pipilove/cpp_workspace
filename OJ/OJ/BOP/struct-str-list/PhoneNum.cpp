/****************************************************************************/
/*		BOP����ʼ�3.2 - �绰�����ӦӢ�ﵥ��		ƤƤ 2014-9-15				*/
/****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*	����phone_num[i]��answer[i]�������ַ�		*/
char pnt[10][5] = {		//���Զ���ÿ���ַ������һ��\0
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
/*	0~9ÿ�������ܱ�ʾ���ַ�����	*/
int total[10] = {0, 0, 3, 3, 3, 3, 3, 4, 3, 4};


/*	ֱ��ѭ������phone_len not fixed��	*/
static void phoneNum(int *phone_num, int phone_len){
	int *answer = (int *)malloc(sizeof(int) * phone_len);	//���ִ����ַ����ܱ�ʾ���ַ����е�λ��
	memset(answer, 0, sizeof(int) * phone_len);				//phonne_num��ÿ����num��Ӧ���ַ��ӵ�0����ʼ

	//int count = 0;
	while(1){
		for(int i = 0; i < phone_len; i++)					//��ӡһ��phone_num�ܶ�Ӧ���ַ�����i��Ӧ�ַ�����i���ַ�
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

int answer[10];											//λ��:���ִ����ַ����ܱ�ʾ���ַ����е�λ��
static int count = 0;
/*	�ݹ��㷨	*/
static void recursivePhoneNum(int *phone_num, int index, int phone_len){
	if(index == phone_len){
		for(int i = 0; i < phone_len; i++)
			printf("%c", pnt[ phone_num[i] ][ answer[i] ]);
		printf("\n");
		count++;
	}else{
		for(answer[index] = 0; answer[index] < total[ phone_num[index] ]; answer[index]++)	//��indexλҪ��ӡtotal[ phone_num[index]��
			recursivePhoneNum(phone_num, index + 1, phone_len);	//��indexλÿ��ӡ1�Σ�index+1λҪ��ӡindex+1��Ӧ�Ĵ���������phone_len-1λֱ�Ӵ�ӡ
	}
}


int __5418465498main(){
	assert( freopen("BOP\\�ṹ - �ַ���������\\PhoneNum.in", "r", stdin) );
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
