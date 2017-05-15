/****************************************************************************/
/*	 	POJ读书笔记9.6 —— 红与黑2816			皮皮 2014-7-16				*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

char chinas[22][22];

static int move(int x, int y){
	if(chinas[x][y] == '#')					//边界或已走过
		return 0;
	chinas[x][y] = '#';						//标记已走过
	return move(x, y + 1) + move(x, y - 1) + move(x + 1, y) + move(x - 1, y) + 1;
}

void redBlack(){
	while(1){
		//printf("%d", sizeof(chinas));
		/*	图形数据集合初始化	*/
		memset(chinas, '#', sizeof(chinas) );

		int w, h;
		scanf("%d %d\n", &w, &h);			//去掉'\n'
		if(w == 0 && h == 0)				//输入0 0退出循环
			break;

		/*	读入图形数据	*/
		char c;
		int start, end;
		for(int i = 1; i <= h; i++){
			for( int j = 1; j <= w; j++){
				scanf("%c", &c);
				if(c == '.')
					chinas[i][j] = '.';
				else if(c == '@'){
					start = i;
					end = j;
					//chinas[i][j] = '.';
					chinas[i][j] = '@';		//任意不为'#'的字符都可以
				}
			}
			getchar();						//读取换行
		}

		//chinas[start][end] = '.';
		/*	输出输入的图形	*/
		for(int i = 0; i <= 21; i++){
			for( int j = 0; j <= 21; j++)
				printf("%c", chinas[i][j]);
			printf("\n");
		}

		printf("%d\n", move(start, end));
	}
}

int __16187461main(){
	redBlack();
	return 0;
}
