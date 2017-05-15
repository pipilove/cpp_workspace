//*******************************************************************/
//*		CCF软件能力认证考试模拟题 —— I'm stuck	皮皮 2014-9-20		*/
//*******************************************************************/
#include <assert.h>
#include <stdio.h>

void stuck(){
	char map[52][52];
	int r, c;
	scanf("%d%d", &r, &c);
	for(int i = r; i < r; i++)
		for(int j = 0; j < c; j++)
			scanf("%c", &map[i][j]);
	printf("%s\n", "I'm stuck!");
}

int __main(){
	//assert( freopen("ccf\\Stuck.in", "r", stdin) );
	stuck();

	//fclose(stdin);
	return 0;
}
