//***********************************************************************/
//*	 CCF软件能力认证考试模拟题 —— 窗口 - 鼠标模拟点击	皮皮 2014-9-19	*/
//***********************************************************************/
#include <assert.h>
#include <stdio.h>

int __54151156main(){
	assert( freopen("ccf\\windows.in", "r", stdin) );
	int line, click;						//line个窗口，click次点击
	scanf("%d%d", &line, &click);

	int win[10][5];
	for(int i = 0; i < line; i++){
		for(int j = 0; j < 4; j++)			//每个窗口的位置
			scanf("%d", &win[i][j]);
		win[i][4] = i + 1;					//窗口编号，按输入顺序
	}

	int x, y;
	for(int i = 0; i < click; i++){			//每次点击判断在哪个窗口中
			scanf("%d", &x);
			scanf("%d", &y);
		int flag = 0;
		for(int k = line - 1; k >= 0; k--){
			if( x >= win[k][0] && x <= win[k][2] && y >= win[k][1] && y <= win[k][3] ){
				flag = 1;
				printf("%d\n", win[k][4]);	//每次点中的窗口要交换到最上层，交换包括编号
				for(int h = 0; h < 5; h++){
					int tmp = win[line - 1][h];
					win[line - 1][h] = win[k][h];
					win[k][h] = tmp;
				}
				break;						//击中一个就要break
			}
		}
		if(flag == 0)
			printf("IGNORED\n");
	}

	return 0;
}
