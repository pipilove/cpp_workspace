//***********************************************************************/
//*		CCF软件能力认证考试模拟题 —— 命令行选项			皮皮 2014-9-19	*/
//***********************************************************************/
#include <assert.h>
#include <stdio.h>
#include <set>
#include <map>
#include <string>
using namespace std;

void cmdOpt(){
	/*	格式字符串分析	*/
	char* format_str = new char[53];
	gets(format_str);
	set<char> opt_set, opt_set_p;
	int str_len = strlen(format_str);
	for(int i = str_len - 1; i >= 0; i--){
		if(format_str[i] == ':')
			opt_set_p.insert(format_str[--i]);					//带参数选项的字符
		else
			opt_set.insert(format_str[i]);						//不带参数选项
	}


	int cases;
	scanf("%d\n", &cases);

	for(int case_i = 1; case_i <= cases; case_i++){				//要解析的命令行数目
		printf("Case %d: ", case_i);
		map<char, char*> opt_map_out;
		char *s = new char[257];								//每行命令行字符串
		gets(s);

		int s_len = strlen(s);
		if( s[0] != 'l' || s[1] != 's')							//cases要continue不是break
			continue;
		if(s_len == 2){
			printf(" \n");
			continue;
		}

		for(int i = 2; i < s_len; i++){
			if(s[i++] != ' ' || i >= s_len)
				break;
			if( s[i++] != '-' || i >= s_len)
				break;

			if(opt_set.find(s[i]) == opt_set.end()){			//不是不带参数选项
				int opt_i = i;
				if(opt_set_p.find(s[i++]) == opt_set_p.end() || i >= s_len)	//也不是带参数选项则break
					break;
				else{
					while(++i < s_len && s[i] != ' ');			//找到参数
					i--;
					int start = opt_i + 2;
					if( i < start )								//!!
						break;
					char* parameter = new char[i - start + 2];
					parameter[i - start +1] = '\0';
					for(int k = 0; k < strlen(parameter); k++)
						parameter[k] = s[start++];

					opt_map_out[s[opt_i]] = parameter;			//参数加到对应选项map中
				}
			}else
				opt_map_out[s[i]] = "$";						//特殊符号，代表它是无参数选项；或者在打印的时候判断是否在opt_set中
		}

		for(map<char, char*>::iterator opt_map_out_it = opt_map_out.begin(); opt_map_out_it != opt_map_out.end(); opt_map_out_it++){
			if( !strcmp(opt_map_out_it->second, "$") )
				printf("-%c ", opt_map_out_it->first);
			else
				printf("-%c %s ", opt_map_out_it->first, opt_map_out_it->second);
		}
		printf("\n");
	}
}

int __16854616515main(){
	assert( freopen("ccf\\cmdOpt.in", "r", stdin) );
	cmdOpt();
	return 0;
}
