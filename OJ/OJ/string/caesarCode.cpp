/****************************************************************************/
/*		POJ读书笔记4.5 —— Caesar密码2975\3749	皮皮 2014-7-5				*/
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
		}else if( strcmp(str, "START") && strcmp(str, "END") ){	//不是START、END时解码
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
