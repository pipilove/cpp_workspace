#include"Maze.h"
#include<iostream>
#include<cstdlib>
using namespace std;

int main(){
	freopen("in.txt","r",stdin);//for test
	freopen("out.txt","w",stdout);//for test
	/*#include <stdio.h>
	FILE *freopen(const char *fname,const char *mode,FILE *stream );
	和fileopen的区别*/

	//while(1){//for test
		Maze aMaze;
		int width = 0,length = 0,entrX = 0,entrY = 0,exitX = 0,exitY = 0;
		printf("\n");//for test
		cout<<"Please input the width and length of maze:"<<endl;
		cin>>width>>length;
		if(width<=0||length<=0||width>100||length>100){
			cout<<"input error!"<<endl;
			//return 0;
			//continue;//for test
		}
		aMaze.setLW(width,length);

		cout<<"Please input the map of maze:"<<endl;
		if(!aMaze.getMaze()){
			cout<<"input error!"<<endl;
			//continue;//for test
			return 0;
		}
		cout<<"Please input the coodinate of entrance and exit:"<<endl;
		cin>>entrX>>entrY>>exitX>>exitY;
		if(!aMaze.setEntrance(entrX,entrY)||!aMaze.setExit(exitX,exitY)){
			cout<<"input error!"<<endl;
			//continue;//for test
			return 0;
		}

		aMaze.getPath();
		system("pause");
	//}
	//getchar();
	//getchar();
	return 0;
}