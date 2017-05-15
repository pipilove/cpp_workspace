/*	�ʷ������� ƤƤ 2014.5.10	*/
#include "GetChar.h"
#include "GetStr.h"
#include "Getnbc.h"
#include "Letter.h"
#include "Digit.h"
#include "Concat.h"
#include "Retract.h"
#include "Reserve.h"
#include "SymTable.h"
#include "Constant.h"
#include "Error.h"
#include "CateDef.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define EOLN '\n'

typedef struct binary_exp{		/*	��Ԫʽ�ṹ(������𣬵�������)	*/
	int category;	//token���
	int position;	//token�ڶ�Ӧ����λ��
}binary_exp;

typedef struct binary_word{		/*	������ļ��ϵĶ�Ԫʽ�ṹ�����ʷ��� �ֱ�	*/
	char* word;
	int category;
}binary_word;

/*	set global extern variable	*/
char character;
char token[16];

/*	�ʷ�������	*/
binary_exp* lexAnalyzer(){ 
	extern int token_index;
	int cate_num;		//token������
	//int position;		//token�ڶ�Ӧ����λ��
	binary_exp* be = (binary_exp*)malloc(sizeof(binary_exp));

	token_index = 0;	//ÿ�ε���lexAnalyzer,token�����ַ�����λ
	getnbc();

	if(letter()){							//�����֡���ʶ��
		do{
			concat();
			getChar();
		}while( letter() || digit() );
		retract();
		cate_num = reserve();
		if(cate_num != 0)
			be->category = cate_num;
		else{
			be->category = $SYMBOL;
			be->position = symbol();
			return be;
		}
	}else if(digit()){						//����
		do{
			concat();
			getChar();
		}while( digit() );
		retract();
		be->category = $CONSTANT;
		be->position = constant();
		return be;
	}else{									//����������
		switch(character){
		case'=':
			be->category = $E;
			return be;
		case'-':
			be->category = $SUB;
			return be;
		case'*':
			be->category = $MUL;
			return be;
		case'(':
			be->category = $LPAR;
			return be;
		case')':
			be->category = $RPAR;
			return be;
		case'<':{
			getChar();
			if(character == '=')
				be->category = $LE;
			else if(character == '>')
				be->category = $NE;
			else{
				retract();
				be->category = $L;
			}
			return be;
				}
		case'>':{
			getChar();
			if(character == '=')
				be->category = $GE;
			else{
				retract();
				be->category = $G;
			}
			return be;
				}
		case':':{
			getChar();
			if(character == '=')
				be->category = $ASSIGN;
			else
				error();
			return be;
				}
		case';':
			be->category = $SEM;
			return be;
			//case'\n':
			//case'\r':
		case EOLN:
			be->category = -1;
			return be;
		case EOF:
			be->category = 0;
			return be;
		default:
			error();
		}
	}
}


//int main(){
int runLexAnalyzer(){
	extern char* symbolTable[];
	extern char* constTable[];
	extern char* key_word[];
	binary_exp* be = (binary_exp*)malloc(sizeof(binary_exp));
	binary_word* bw = (binary_word*)malloc(sizeof(binary_word));
	FILE* fp;

	getStr();									//��ȡfile�е�code��str��

	if(  (fp= fopen("testFun.dyd","w")) == NULL){//��д�ļ�
		printf("testFun.dyd file open fail !!!\n");
		system("pause");
		exit(-1);
	}

	do{
		be = lexAnalyzer();							//�ʷ���������һ�����ʶ�Ԫʽ
		if(be->category == -1){						//end of line
			fprintf(fp,"            EOLN 24\n");
			continue;
		}
		if(be->category == 0){						//end of file
			fprintf(fp,"             EOF 25\n");
			break;
		}
		bw->category = be->category ;
		if(be->category == $SYMBOL)
			bw->word = symbolTable[be->position];
		else if(be->category == $CONSTANT)
			bw->word = constTable[be->position];
		else
			bw->word = key_word[be->category-1];

		//printf ("%8s	%2d\n",bw->word,bw->category);
		fprintf(fp,"%16s %2d\n",bw->word,bw->category);
	}while(be->category != 0);
	fclose(fp);
	//system("pause");
	return 0;
}
