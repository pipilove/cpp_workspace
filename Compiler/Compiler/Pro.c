#include "Advance.h"
#include "Error1.h"
#include "VarTable.h"
#include <stdio.h>
#include <string.h>
#include "funhead.h"
#include "ProTable.h"
#include "GetWordStruct.h"
#include "WriteVarFun.h"

/*	ȫ�ֱ�������ƥ���������	*/
extern int line_counter;
extern FILE* errorfp;					//.err

char * var_pro_name;					//������������������ǰ������
int plev;								//���̲��
extern int var_offset;					//i��ǰ�����ڱ������е�λ��

proIfo funInfo[256];					//������Ϣ��
int pro_counter = -1;					//���̸���

extern int category;
//extern int next_category;
extern int next_next_category;
extern word* all_word[];
extern int advance_index;


/*	����	Pro -> Sub	*/
void procedure(){
	advance();							//һ��ʼ��Ӧ��ȡ��һ��word
	subPro();
	writeVarFun();						//�������ʱ��д�������͹�������
}

/*	�ӳ���Sub -> 1 Stab 23 Etab 2	(1begin 23; 2end)*/
void subPro(){
	var_pro_name = "subPro";			//��������ʼ��Ϊ���
	if(category == 1){					//1����Ϊ$begin����
		advance();
after_begin:
		stateTable();
		if(category == 23){
			advance();
after_semi0:
			var_pro_name = "subPro";	//��������������������Ϊ���
			excTable();
			if(category != 2){
				error1();
				printf("loss 'end' or lose ';' \n");
				fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
			}
		}else{
			error1();
			printf("loss ';' or lose keyword \n");
			fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
			goto after_semi0;
		}
	}else{
		error1();
		printf("loss begin \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
		goto after_begin;
	}
}

/*	˵������Stab -> Sta Stab'	*/
void stateTable(){
	state();
	stateTable1();
}
/*	˵������1(������ݹ�)Stab' -> 23 Sta Stab' | ��	��23;��*/
void stateTable1(){
	if(category == 23 && next_next_category == 3){//����������Ļ��ݣ���������ô��???
		advance();
		state();		
		stateTable1();
	}
}

/*	˵�����Sta -> 3 Sta'	(3interger)*/
void state(){
	if(category == 3){
		advance();
		state1();
	}else{
		error1();
		printf("vriable used not declared \n");
		fprintf(errorfp,"***LINE:%2d  (3)�����޶�����ظ�����\n",line_counter);			
	}
}
/*	˵�����(��������������)Sta' -> 7 Fsta | 10	(7function 10identifier)*/
void state1(){
	if(category == 7){			//��������
		advance();
		pro_counter++;											//��һ��������¼index+1����ʼ-1
		var_pro_name = all_word[advance_index-1]->name;			//��ǰ�������ִ���var_pro_name
		funInfo[pro_counter].proName = all_word[advance_index-1]->name;
		funInfo[pro_counter].ptype = "interger";
		funInfo[pro_counter].plev = plev;						//�������
		plev++;													//���̲��Ҫ��1
		if(	proCheck() == 1){									//���̼��(�ض���)
			error1();											//�����ظ��������
			printf("process redefined \n");
			fprintf(errorfp,"***LINE:%2d  (1)�����ظ�����\n",line_counter);
		}

		funState();												//���뵱ǰ��������

		plev--;													//���������������Ҫ��1
	}
	else if(category == 10){									//��������
		if(varTable(0) == 1){									//���������
			error1();											//�����ظ��������
			printf("varible redefined \n");
			fprintf(errorfp,"***LINE:%2d  (1)�����ظ�����\n",line_counter);
		}
		advance();
	}
	else{
		error1();
		printf("loss funstate or variable statement \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
	}
}

/*	����˵�����Fsta -> 	Ide 21 Para 22 23 Fun ( 21( 22 ) 23; )*/
void funState(){
	identifier();
	if(category == 21){
		advance();
after_semi2:
		parameter();
		if(category == 22){
			advance();
after_bracket2:
			if(category == 23){
				advance();
after_semi1:
				func();
			}else{
				error1();
				printf("loss ';' \n");
				fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
				goto after_semi1;
			}
		}else{
			error1();
			printf("loss ')' \n");
			fprintf(errorfp,"***LINE:%2d  (2)����ƥ���\n",line_counter);
			goto after_bracket2;
		}
	}else{
		error1();
		printf("loss '(' \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
		goto after_semi2;
	}
}

/*	��ʶ��˵��Ide -> 10	*/
void identifier(){
	if(category == 10)
		advance();
	else{
		error1();
		printf("loss identifier \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
	}
}

/*	����˵��Pare -> Var	*/
void parameter(){
	variable(1);										//�����(����)����
}

/*	����˵�����Var -> 10	*/
void variable(int vkind){
	if(category == 10){
		if(varTable(vkind) == 1){						//���������
			error1();									//�����ظ�����
			printf("varible redefined \n");
			fprintf(errorfp,"***LINE:%2d  (3)�����ظ�����\n",line_counter);
		}
		advance();
	}else{
		error1();
		printf("loss parameter variable declaration \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
	}
}

/*	��������Fun -> 1 Stab 23 Etab 2 	(1begin 23; 2 end)*/
void func(){
	if(category == 1){				
		funInfo[pro_counter].fadr = var_offset;				//��������������ʼ����¼�����е�һ������λ��(ǰ�滹�в���)
		advance();
after_begin1:
		stateTable();
		if(category == 23){
			advance();
after_semi3:
			excTable();
			var_pro_name = funInfo[pro_counter-1].proName;	//�������������޸ĵ�ǰ������Ϊ�˶��庯������һ��������
			if(category == 2)
				advance();
			else{
				error1();
				printf("loss end \n");
				fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
			}
		}else{
			error1();
			printf("loss ';' \n");
			fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
			goto after_semi3;
		}
	}else{
		error1();
		printf("loss begin \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
		goto after_begin1;
	}
}


/*	ִ������Etab -> Exc Etab'	*/
void excTable(){
	excute();
	excTable1();
}
/*	ִ������(������ݹ�)Etab' -> 23 Exc Etab' | ��	*/
void excTable1(){
	if(category == 23){
		advance();
		excute();
		excTable1();
	}
}

/*	ִ�����Exc ->(R | W | A | Con)-> 8Var | 9Var | 10A | 4Con	(8read 9write 10identifier 4if)*/
void excute(){
	if(category == 8){
		advance();
		read();
	}else if(category == 9){
		advance();
		write();
	}else if(category == 10){
		advance();
		if( realParaCheck() == 0 && callProCheck() == 0){					//��鸳ֵ�����Ƿ���
				error1();
				printf("variable used not defined \n");
				fprintf(errorfp,"***LINE:%2d  (3)�����޶���\n",line_counter);
		}
		assign();
	}else if(category == 4){
		advance();
		condition();
	}else{
		error1();
		printf("not an exctutable or declaration statement \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
	}
}
/*	read���	*/
void read(){	
	if(category == 21){
		advance();
after_bracket:
		//variable(0);									//�������ò����������
		if(category == 10){
			advance();
			if( realParaCheck() == 0){					//���ʵ���Ƿ���
				error1();
				printf("variable used not defined \n");
				fprintf(errorfp,"***LINE:%2d  (3)�����޶���\n",line_counter);
			}
		}
		if(category == 22)
			advance();
		else{
			error1();
			printf("loss ')' \n");
			fprintf(errorfp,"***LINE:%2d  (2)����ƥ���\n",line_counter);
		}
	}else{
		error1();
		printf("loss '(' \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
			goto after_bracket;
	}
}
/*	write���	*/
void write(){
	if(category == 21){
		advance();
after_bracket1:
		//variable(0);									//�������ò����������
		if(category == 10){
			advance();
			if( realParaCheck() == 0){					//���ʵ���Ƿ���
				error1();
				printf("variable used not defined \n");
				fprintf(errorfp,"***LINE:%2d  (3)�����޶���\n",line_counter);
			}
		}
		if(category == 22)
			advance();
		else{
			error1();
			printf("loss ')' \n");
			fprintf(errorfp,"***LINE:%2d  (2)����ƥ���\n",line_counter);
		}
	}else{
		error1();
		printf("loss '(' \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
		goto after_bracket1;
	}
}
/*	��ֵ���	A -> 20 Exp	(20:=)*/
void assign(){
	if(category == 20){
		advance();
after_equa:
		expression();
	}else{
		error1();
		printf("loss :=  or lose ( \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
		goto after_equa;
	}
}

/*	���ʽExp -> Itm Exp'	*/
void expression(){
	item();
	expression1();
}
/*	���ʽExp' -> 18 Itm Exp' | ��	��18-��*/
void expression1(){
	if(category == 18){
		advance();
		item();
		expression1();
	}
}

/*	��Itm -> Fac Itm'	*/
void item(){
	factor();
	item1();
}
/*	��Itm' -> 19 Fac Itm' | ��	(19*)*/
void item1(){
	if(category == 19){
		advance();
		factor();
		item1();
	}
}

/*	����Fac ->(Var | 11 | Cfun) -> 10 Fac' | 11   (10identifier 11constant)*/
void factor(){
	if(category == 10){
		advance();
		factor1();
	}else if(category == 11){
		advance();
	}else{
		error1();
		printf("not an identifier \n");
		fprintf(errorfp,"***LINE:%2d  (3)�����޶�����ظ�����\n",line_counter);
	}
}
/*	����(������������ӡ��Ż���)Fac' -> 21 Cfun | ��	(21()*/
void factor1(){
	if(category == 21){
		if( callProCheck() == 0){				//���õ��ǹ�������(ǰһ��������)�����Ƿ���
			error1();
			printf("process used not defined \n");
			fprintf(errorfp,"***LINE:%2d  (3)�����޶���\n",line_counter);
		}					
		advance();
		callFun();
	}else if( realParaCheck() == 0){			//�����Ǳ�����ֵ����鸳ֵ�����Ƿ���
		error1();
		printf("variable used not defined \n");
		fprintf(errorfp,"***LINE:%2d  (3)�����޶���\n",line_counter);
	}
}

/*	���ú���Cfun -> Para 22	( 22) )*/
void callFun(){
	expression();
	//parameter();
	if(category == 22){
		advance();
	}else{
		error1();
		printf("loss ��)�� \n");			
		fprintf(errorfp,"***LINE:%2d  (2)����ƥ���\n",line_counter);

	}
}

/*	�������	Con -> B 5 Exc 6 Exc	(5then 6else)*/
void condition(){
	branch();
	if(category == 5){
		advance();
after_then:
		excute();
		if(category == 6){
			advance();
after_else:
			excute();
		}else{
			error1();
			printf("loss else \n");
			fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
			goto after_else;
		}
	}else{
		error1();
		printf("loss then \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
		goto after_then;
	}
}

/*	�������ʽB -> Exp Rop Exp	*/
void branch(){
	expression();
	relOperator();
	expression();
}

/*	��ϵ�����Rop -> 12 | 13 | 14 | 15 | 16 |17		( = <> <= < >= > )*/
void relOperator(){
	switch(category){
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		advance();
		break;
	default:{
		error1();
		printf("not a relation operator \n");
		fprintf(errorfp,"***LINE:%2d  (1)ȱ�ٷ��Ŵ�\n",line_counter);
			}
	}
}

