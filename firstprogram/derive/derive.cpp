// derive.cpp : Defines the entry point for the console application.
//书P259--继承，类型兼容

#include "stdafx.h"
#include <iostream>
const double PI=3.14159;

using namespace std;

class Point{
private:
	int x,y;
public:
	Point(int x,int y){
		this->x=x;
		this->y=y;
	}
	void ShowXY(){
		cout<<"("<<x<<","<<y<<")"<<endl;
	}
};

class Circle:public Point
{
private:
	double radius;
public:
	Circle(double R,int X,int Y):Point(X,Y){
		radius=R;								//不加this
	}
	double area(){
		return PI*radius*radius;
	}
	void ShowCircle(){
		cout<<"Center of circle:";
		ShowXY();
		cout<<"radius:"<<radius<<endl;
	}
};

class Cylinder:public Circle{
private:
	double height;
public:
	Cylinder(double R,int X,int Y,double H):Circle(R,X,Y){
		height=H;
	}
	void ShouCylinder(){
		ShowCircle();
		cout<<"height of cylinder:"<<height<<endl;
	}
};

int main()
{
	Point P(1,1);
	Circle Cir(15,20,20);
	Cylinder CY(15,300,300,50);

	Point *Pp;
	Pp=&P;
	Pp->ShowXY();

	Pp=&Cir;
	Pp->ShowXY();

	Pp=&CY;
	Pp->ShowXY();

	Circle & RC=CY;
	RC.ShowXY();

	P=Cir;
	P.ShowXY();
	return 0;
}
