/****************************************************************************/
/*	 POJ����ʼ�4.2 ���� ͳ���ַ���2742			ƤƤ 2014-7-3				*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

void charCount(){
	int n;									//����
	int alphabet[26];
	char s[1001];							//ÿ���ַ���������1000���ַ�
	int i, max;

	scanf("%d", &n);

	while(n--){
		memset( alphabet, 0, sizeof(alphabet) );
		scanf("%s",s);
		for(i = 0; s[i]; i++)				//for(i = 0; i < strlen(str); i++)
			alphabet[s[i] - 'a'] ++;

		max = 0;
		for(i = 1; i < 26; i++){
			if(alphabet[i] > alphabet[max])
				max = i;
		}
		printf("%c %d\n",'a' + max, alphabet[max]);
	}
}

int __487main(){
	charCount();
	return 0;
}

