//***********************************************************************/
//*	 CCF���������֤����ģ���� ���� ���� - ���ģ����	ƤƤ 2014-9-19	*/
//***********************************************************************/
#include <assert.h>
#include <stdio.h>

int __54151156main(){
	assert( freopen("ccf\\windows.in", "r", stdin) );
	int line, click;						//line�����ڣ�click�ε��
	scanf("%d%d", &line, &click);

	int win[10][5];
	for(int i = 0; i < line; i++){
		for(int j = 0; j < 4; j++)			//ÿ�����ڵ�λ��
			scanf("%d", &win[i][j]);
		win[i][4] = i + 1;					//���ڱ�ţ�������˳��
	}

	int x, y;
	for(int i = 0; i < click; i++){			//ÿ�ε���ж����ĸ�������
			scanf("%d", &x);
			scanf("%d", &y);
		int flag = 0;
		for(int k = line - 1; k >= 0; k--){
			if( x >= win[k][0] && x <= win[k][2] && y >= win[k][1] && y <= win[k][3] ){
				flag = 1;
				printf("%d\n", win[k][4]);	//ÿ�ε��еĴ���Ҫ���������ϲ㣬�����������
				for(int h = 0; h < 5; h++){
					int tmp = win[line - 1][h];
					win[line - 1][h] = win[k][h];
					win[k][h] = tmp;
				}
				break;						//����һ����Ҫbreak
			}
		}
		if(flag == 0)
			printf("IGNORED\n");
	}

	return 0;
}
