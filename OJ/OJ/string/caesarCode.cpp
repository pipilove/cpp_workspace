/****************************************************************************/
/*		POJ����ʼ�4.5 ���� Caesar����2975\3749	ƤƤ 2014-7-5				*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

void caesar(){
	char code[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str[201];
	while( 1 ){
		gets(str);//scanf( "%[^\n]", str ); 
		if( !strcmp(str, "ENDOFINPUT") ){
			break;
		}else if( strcmp(str, "START") && strcmp(str, "END") ){	//����START��ENDʱ����
			char * s = str;
			while( *s ){
				if( *s <= 'Z' && *s >= 'A')
					*s = code[(*s - 'A' + 21) % 26];
				s++;
			}
			puts(str);
		}
	}
}

int __2646main(){
	caesar();
	return 0;
}
