#ifndef PRINT
#define PRINT
#include <iostream>
#include "stdio.h"
#include "Point.h"
using namespace std;

void render_string(int x,int y,void* font, const char* string)
{
	glRasterPos2f( x , y);
	char* p = (char*) string;
	while (*p != '\0') glutBitmapCharacter(font, *p++);
}

void print(Point p, int k, char name){
	if(0 <= k && k < 10){
		char x[1];
		char s = (char)k + '0';
		x[0] = s;
		x[1] = '\0';
		render_string(p.x - 5,p.y + 2,GLUT_BITMAP_HELVETICA_18, x);
	}
	else if( 10 <= k && k <100){
		char x[2];
		for(int i=0;i<2;i++){
			int temp = k % 10;
			k = (k -temp)/10;
			x[1-i] = (char)temp + '0';
		}
		x[2] = '\0';
		render_string(p.x - 10 ,p.y + 2,GLUT_BITMAP_HELVETICA_18, x);
	}
	else{
		char str[100];
		switch(name){
			case '+':
			case '-':
			case '*':
			case '/':
				char x[1];
				x[0] = name;
				x[1] = '\0';
				render_string(p.x -5 ,p.y + 2,GLUT_BITMAP_HELVETICA_18, x);
				break;
		}
	}
}
#endif
