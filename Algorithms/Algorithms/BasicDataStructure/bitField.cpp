/*********************************************************************************************/
/*	位域 - 计算一个字符串中每个字符的奇偶校验码，并输出该字符及其二进制表示形式	2014-7-1 皮皮	 */
/*********************************************************************************************/
#include <stdio.h>

typedef struct bitField{
	unsigned b0:1,b1:1,b2:1,b3:1,b4:1,b5:1,b6:1,b7:1;
}bit;


void bitFieldTest(){
	char str[] = "abcdef";
	char * str_ptr = str;
	bit * bit_str;
	unsigned parity;

	while(*str_ptr){
		bit_str = (bit*)str_ptr;											//强制类型转换
		parity = ( bit_str->b7 + bit_str->b6 + bit_str->b5 + bit_str->b4 + 
			bit_str->b3 + bit_str->b2 + bit_str->b1 + bit_str->b0 )%2;		//奇偶校验位
		printf("%c = %u%u%u%u%u%u%u%u\n",*str_ptr, parity , bit_str->b6 , bit_str->b5 , bit_str->b4 , 
			bit_str->b3 , bit_str->b2 , bit_str->b1 , bit_str->b0 );		//奇偶校验位放在二进制表示最前面
		str_ptr++;
	}
}


void __1main(){
	bitFieldTest();
}
