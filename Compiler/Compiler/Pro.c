#include "Advance.h"
#include "Error1.h"
#include "VarTable.h"
#include <stdio.h>
#include <string.h>
#include "funhead.h"
#include "ProTable.h"
#include "GetWordStruct.h"
#include "WriteVarFun.h"

/*	全局变量，待匹配符号类型	*/
extern int line_counter;
extern FILE* errorfp;					//.err

char * var_pro_name;					//变量所属过程名，当前函数名
int plev;								//过程层次
extern int var_offset;					//i当前变量在变量表中的位置

proIfo funInfo[256];					//过程信息表
int pro_counter = -1;					//过程个数

extern int category;
//extern int next_category;
extern int next_next_category;
extern word* all_word[];
extern int advance_index;


/*	程序	Pro -> Sub	*/
void procedure(){
	advance();							//一开始就应该取出一个word
	subPro();
	writeVarFun();						//程序结束时填写变量名和过程名表
}

/*	子程序Sub -> 1 Stab 23 Etab 2	(1begin 23; 2end)*/
void subPro(){
	var_pro_name = "subPro";			//过程名初始化为外层
	if(category == 1){					//1定义为$begin更好
		advance();
after_begin:
		stateTable();
		if(category == 23){
			advance();
after_semi0:
			var_pro_name = "subPro";	//各种声明结束过程名改为外层
			excTable();
			if(category != 2){
				error1();
				printf("loss 'end' or lose ';' \n");
				fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
			}
		}else{
			error1();
			printf("loss ';' or lose keyword \n");
			fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
			goto after_semi0;
		}
	}else{
		error1();
		printf("loss begin \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
		goto after_begin;
	}
}

/*	说明语句表Stab -> Sta Stab'	*/
void stateTable(){
	state();
	stateTable1();
}
/*	说明语句表1(消除左递归)Stab' -> 23 Sta Stab' | ε	（23;）*/
void stateTable1(){
	if(category == 23 && next_next_category == 3){//消除ε引起的回溯，还可以怎么改???
		advance();
		state();		
		stateTable1();
	}
}

/*	说明语句Sta -> 3 Sta'	(3interger)*/
void state(){
	if(category == 3){
		advance();
		state1();
	}else{
		error1();
		printf("vriable used not declared \n");
		fprintf(errorfp,"***LINE:%2d  (3)符号无定义或重复定义\n",line_counter);			
	}
}
/*	说明语句(消除公共左因子)Sta' -> 7 Fsta | 10	(7function 10identifier)*/
void state1(){
	if(category == 7){			//函数声明
		advance();
		pro_counter++;											//下一个函数记录index+1，初始-1
		var_pro_name = all_word[advance_index-1]->name;			//当前函数名字存入var_pro_name
		funInfo[pro_counter].proName = all_word[advance_index-1]->name;
		funInfo[pro_counter].ptype = "interger";
		funInfo[pro_counter].plev = plev;						//函数层次
		plev++;													//过程层次要加1
		if(	proCheck() == 1){									//过程检查(重定义)
			error1();											//过程重复定义错误
			printf("process redefined \n");
			fprintf(errorfp,"***LINE:%2d  (1)符号重复定义\n",line_counter);
		}

		funState();												//进入当前函数定义

		plev--;													//过程声明结束层次要减1
	}
	else if(category == 10){									//变量声明
		if(varTable(0) == 1){									//填变量名表
			error1();											//变量重复定义错误
			printf("varible redefined \n");
			fprintf(errorfp,"***LINE:%2d  (1)符号重复定义\n",line_counter);
		}
		advance();
	}
	else{
		error1();
		printf("loss funstate or variable statement \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
	}
}

/*	函数说明语句Fsta -> 	Ide 21 Para 22 23 Fun ( 21( 22 ) 23; )*/
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
				fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
				goto after_semi1;
			}
		}else{
			error1();
			printf("loss ')' \n");
			fprintf(errorfp,"***LINE:%2d  (2)符号匹配错\n",line_counter);
			goto after_bracket2;
		}
	}else{
		error1();
		printf("loss '(' \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
		goto after_semi2;
	}
}

/*	标识符说明Ide -> 10	*/
void identifier(){
	if(category == 10)
		advance();
	else{
		error1();
		printf("loss identifier \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
	}
}

/*	参数说明Pare -> Var	*/
void parameter(){
	variable(1);										//填变量(参数)名表
}

/*	变量说明语句Var -> 10	*/
void variable(int vkind){
	if(category == 10){
		if(varTable(vkind) == 1){						//填变量名表
			error1();									//符号重复定义
			printf("varible redefined \n");
			fprintf(errorfp,"***LINE:%2d  (3)符号重复定义\n",line_counter);
		}
		advance();
	}else{
		error1();
		printf("loss parameter variable declaration \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
	}
}

/*	函数定义Fun -> 1 Stab 23 Etab 2 	(1begin 23; 2 end)*/
void func(){
	if(category == 1){				
		funInfo[pro_counter].fadr = var_offset;				//函数变量声明开始处记录过程中第一个变量位置(前面还有参数)
		advance();
after_begin1:
		stateTable();
		if(category == 23){
			advance();
after_semi3:
			excTable();
			var_pro_name = funInfo[pro_counter-1].proName;	//函数结束定义修改当前函数名为此定义函数的上一个函数名
			if(category == 2)
				advance();
			else{
				error1();
				printf("loss end \n");
				fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
			}
		}else{
			error1();
			printf("loss ';' \n");
			fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
			goto after_semi3;
		}
	}else{
		error1();
		printf("loss begin \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
		goto after_begin1;
	}
}


/*	执行语句表Etab -> Exc Etab'	*/
void excTable(){
	excute();
	excTable1();
}
/*	执行语句表(消除左递归)Etab' -> 23 Exc Etab' | ε	*/
void excTable1(){
	if(category == 23){
		advance();
		excute();
		excTable1();
	}
}

/*	执行语句Exc ->(R | W | A | Con)-> 8Var | 9Var | 10A | 4Con	(8read 9write 10identifier 4if)*/
void excute(){
	if(category == 8){
		advance();
		read();
	}else if(category == 9){
		advance();
		write();
	}else if(category == 10){
		advance();
		if( realParaCheck() == 0 && callProCheck() == 0){					//检查赋值变量是否定义
				error1();
				printf("variable used not defined \n");
				fprintf(errorfp,"***LINE:%2d  (3)符号无定义\n",line_counter);
		}
		assign();
	}else if(category == 4){
		advance();
		condition();
	}else{
		error1();
		printf("not an exctutable or declaration statement \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
	}
}
/*	read语句	*/
void read(){	
	if(category == 21){
		advance();
after_bracket:
		//variable(0);									//函数调用不填变量名表
		if(category == 10){
			advance();
			if( realParaCheck() == 0){					//检查实参是否定义
				error1();
				printf("variable used not defined \n");
				fprintf(errorfp,"***LINE:%2d  (3)符号无定义\n",line_counter);
			}
		}
		if(category == 22)
			advance();
		else{
			error1();
			printf("loss ')' \n");
			fprintf(errorfp,"***LINE:%2d  (2)符号匹配错\n",line_counter);
		}
	}else{
		error1();
		printf("loss '(' \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
			goto after_bracket;
	}
}
/*	write语句	*/
void write(){
	if(category == 21){
		advance();
after_bracket1:
		//variable(0);									//函数调用不填变量名表
		if(category == 10){
			advance();
			if( realParaCheck() == 0){					//检查实参是否定义
				error1();
				printf("variable used not defined \n");
				fprintf(errorfp,"***LINE:%2d  (3)符号无定义\n",line_counter);
			}
		}
		if(category == 22)
			advance();
		else{
			error1();
			printf("loss ')' \n");
			fprintf(errorfp,"***LINE:%2d  (2)符号匹配错\n",line_counter);
		}
	}else{
		error1();
		printf("loss '(' \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
		goto after_bracket1;
	}
}
/*	赋值语句	A -> 20 Exp	(20:=)*/
void assign(){
	if(category == 20){
		advance();
after_equa:
		expression();
	}else{
		error1();
		printf("loss :=  or lose ( \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
		goto after_equa;
	}
}

/*	表达式Exp -> Itm Exp'	*/
void expression(){
	item();
	expression1();
}
/*	表达式Exp' -> 18 Itm Exp' | ε	（18-）*/
void expression1(){
	if(category == 18){
		advance();
		item();
		expression1();
	}
}

/*	项Itm -> Fac Itm'	*/
void item(){
	factor();
	item1();
}
/*	项Itm' -> 19 Fac Itm' | ε	(19*)*/
void item1(){
	if(category == 19){
		advance();
		factor();
		item1();
	}
}

/*	因子Fac ->(Var | 11 | Cfun) -> 10 Fac' | 11   (10identifier 11constant)*/
void factor(){
	if(category == 10){
		advance();
		factor1();
	}else if(category == 11){
		advance();
	}else{
		error1();
		printf("not an identifier \n");
		fprintf(errorfp,"***LINE:%2d  (3)符号无定义或重复定义\n",line_counter);
	}
}
/*	因子(清除公共左因子、ε回溯)Fac' -> 21 Cfun | ε	(21()*/
void factor1(){
	if(category == 21){
		if( callProCheck() == 0){				//调用的是过程则检查(前一个变量名)过程是否定义
			error1();
			printf("process used not defined \n");
			fprintf(errorfp,"***LINE:%2d  (3)符号无定义\n",line_counter);
		}					
		advance();
		callFun();
	}else if( realParaCheck() == 0){			//否则是变量赋值，检查赋值变量是否定义
		error1();
		printf("variable used not defined \n");
		fprintf(errorfp,"***LINE:%2d  (3)符号无定义\n",line_counter);
	}
}

/*	调用函数Cfun -> Para 22	( 22) )*/
void callFun(){
	expression();
	//parameter();
	if(category == 22){
		advance();
	}else{
		error1();
		printf("loss ‘)’ \n");			
		fprintf(errorfp,"***LINE:%2d  (2)符号匹配错\n",line_counter);

	}
}

/*	条件语句	Con -> B 5 Exc 6 Exc	(5then 6else)*/
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
			fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
			goto after_else;
		}
	}else{
		error1();
		printf("loss then \n");
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
		goto after_then;
	}
}

/*	条件表达式B -> Exp Rop Exp	*/
void branch(){
	expression();
	relOperator();
	expression();
}

/*	关系运算符Rop -> 12 | 13 | 14 | 15 | 16 |17		( = <> <= < >= > )*/
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
		fprintf(errorfp,"***LINE:%2d  (1)缺少符号错\n",line_counter);
			}
	}
}

