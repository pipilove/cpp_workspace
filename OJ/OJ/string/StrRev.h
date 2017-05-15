/****************************************************************************/
/*				字符串反转算法		皮皮 2014-7-9							*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

/*	字符串反转算法	*/
static char * strReverse(char *str){		//字符串反转，不包括'\0'	//函数名前加static防止函数重定义
	char * head = str,* tail = str;
	/*while(*tail++);
	tail -= 2;*/
	while(*tail){
		tail++;
	}
	tail--;									//tail指向最后一个非'\0'字符

	char tmp;
	while(head < tail){
		tmp= *head;
		*head++ = *tail;
		*tail-- = tmp;
	}
	return str;
}

/*	字符串反转算法1	*/
static  char * strReverse1(char *str){
	int j, i;
	for(i = 0, j = strlen(str) - 1; i < j; i++, j--){
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
	return str;
}

/*	字符串反转递归算法	*/
static  char *recStrRev(char *str, int head, int tail){
	if( head >= tail )
		return str;
	char tmp = str[head];
	str[head] = str[tail];
	str[tail] = tmp;
	 return recStrRev(str, ++head, --tail);	//不能head++， 否则head传入的总是0，3; 返回时才会变，总是1，2
}

/*	字符串反转递归算法1	*/
static  char *recStrRev1(char* str) {
    int len = strlen(str);
    if (len <= 1)
        return str;
    char lastData = str[len-1];				//保留最后一个字符
    str[len-1] = '\0';						//去掉首尾两个字符
    recStrRev1(str+1);
    str[len-1] = str[0];
    str[0] = lastData;
    return str;
}

//int main(){
//	char str[] = "ABCDEFG";					//char* str会导致strrev中发生写入位置冲突	
//	printf("%s\n", strReverse(str) );
//	printf("%s\n", recStrRev(str, 0, strlen(str) - 1) );
//	printf("%s\n", strReverse1(str) );
//	printf("%s\n", recStrRev1(str) );
//	return 0;
//}
