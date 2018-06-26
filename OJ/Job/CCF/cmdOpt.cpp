//***********************************************************************/
//*		CCF���������֤����ģ���� ���� ������ѡ��			ƤƤ 2014-9-19	*/
//***********************************************************************/
#include <assert.h>
#include <stdio.h>
#include <set>
#include <map>
#include <string>
using namespace std;

void cmdOpt(){
	/*	��ʽ�ַ�������	*/
	char* format_str = new char[53];
	gets(format_str);
	set<char> opt_set, opt_set_p;
	int str_len = strlen(format_str);
	for(int i = str_len - 1; i >= 0; i--){
		if(format_str[i] == ':')
			opt_set_p.insert(format_str[--i]);					//������ѡ����ַ�
		else
			opt_set.insert(format_str[i]);						//��������ѡ��
	}


	int cases;
	scanf("%d\n", &cases);

	for(int case_i = 1; case_i <= cases; case_i++){				//Ҫ��������������Ŀ
		printf("Case %d: ", case_i);
		map<char, char*> opt_map_out;
		char *s = new char[257];								//ÿ���������ַ���
		gets(s);

		int s_len = strlen(s);
		if( s[0] != 'l' || s[1] != 's')							//casesҪcontinue����break
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

			if(opt_set.find(s[i]) == opt_set.end()){			//���ǲ�������ѡ��
				int opt_i = i;
				if(opt_set_p.find(s[i++]) == opt_set_p.end() || i >= s_len)	//Ҳ���Ǵ�����ѡ����break
					break;
				else{
					while(++i < s_len && s[i] != ' ');			//�ҵ�����
					i--;
					int start = opt_i + 2;
					if( i < start )								//!!
						break;
					char* parameter = new char[i - start + 2];
					parameter[i - start +1] = '\0';
					for(int k = 0; k < strlen(parameter); k++)
						parameter[k] = s[start++];

					opt_map_out[s[opt_i]] = parameter;			//�����ӵ���Ӧѡ��map��
				}
			}else
				opt_map_out[s[i]] = "$";						//������ţ����������޲���ѡ������ڴ�ӡ��ʱ���ж��Ƿ���opt_set��
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
