/****************************************************************************/
/*	 	POJ����ʼ�9.6 ���� �����2816			ƤƤ 2014-7-16				*/
/****************************************************************************/
#include <stdio.h>
#include <string.h>

char chinas[22][22];

static int move(int x, int y){
	if(chinas[x][y] == '#')					//�߽�����߹�
		return 0;
	chinas[x][y] = '#';						//������߹�
	return move(x, y + 1) + move(x, y - 1) + move(x + 1, y) + move(x - 1, y) + 1;
}

void redBlack(){
	while(1){
		//printf("%d", sizeof(chinas));
		/*	ͼ�����ݼ��ϳ�ʼ��	*/
		memset(chinas, '#', sizeof(chinas) );

		int w, h;
		scanf("%d %d\n", &w, &h);			//ȥ��'\n'
		if(w == 0 && h == 0)				//����0 0�˳�ѭ��
			break;

		/*	����ͼ������	*/
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
					chinas[i][j] = '@';		//���ⲻΪ'#'���ַ�������
				}
			}
			getchar();						//��ȡ����
		}

		//chinas[start][end] = '.';
		/*	��������ͼ��	*/
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
