/****************************************************************************/
/*				�ַ�����ת�㷨		ƤƤ 2014-7-9							*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

/*	�ַ�����ת�㷨	*/
static char * strReverse(char *str){		//�ַ�����ת��������'\0'	//������ǰ��static��ֹ�����ض���
	char * head = str,* tail = str;
	/*while(*tail++);
	tail -= 2;*/
	while(*tail){
		tail++;
	}
	tail--;									//tailָ�����һ����'\0'�ַ�

	char tmp;
	while(head < tail){
		tmp= *head;
		*head++ = *tail;
		*tail-- = tmp;
	}
	return str;
}

/*	�ַ�����ת�㷨1	*/
static  char * strReverse1(char *str){
	int j, i;
	for(i = 0, j = strlen(str) - 1; i < j; i++, j--){
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
	return str;
}

/*	�ַ�����ת�ݹ��㷨	*/
static  char *recStrRev(char *str, int head, int tail){
	if( head >= tail )
		return str;
	char tmp = str[head];
	str[head] = str[tail];
	str[tail] = tmp;
	 return recStrRev(str, ++head, --tail);	//����head++�� ����head���������0��3; ����ʱ�Ż�䣬����1��2
}

/*	�ַ�����ת�ݹ��㷨1	*/
static  char *recStrRev1(char* str) {
    int len = strlen(str);
    if (len <= 1)
        return str;
    char lastData = str[len-1];				//�������һ���ַ�
    str[len-1] = '\0';						//ȥ����β�����ַ�
    recStrRev1(str+1);
    str[len-1] = str[0];
    str[0] = lastData;
    return str;
}

//int main(){
//	char str[] = "ABCDEFG";					//char* str�ᵼ��strrev�з���д��λ�ó�ͻ	
//	printf("%s\n", strReverse(str) );
//	printf("%s\n", recStrRev(str, 0, strlen(str) - 1) );
//	printf("%s\n", strReverse1(str) );
//	printf("%s\n", recStrRev1(str) );
//	return 0;
//}
