#include <Windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Ball.h"

Ball::Ball(){
}

Ball::Ball(char n){
	num = 0;
	r = 100;
	name = n;
}

void Ball::setBall(int num){
	
	this->num = num;
}

int Ball::getBall(){
	
	return num;
}

void Ball::setEnable(bool state){
	enable = state;
}

void Ball::drawFilledSun(int n){
    double radius = r/n;
    double twicePi = 2.0 * 3.142;
    int x = 0, y = 0;
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (int i = 0; i <= 20; i++)
        glVertex2f ( (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20))) );
    glEnd();
}

void Ball::draw(){
	if(!enable) 	return;
	
	float point;
	
	if(name == 'A')	point = 100;
	else point = 950;
	
    glLoadIdentity();
	int index = 0;
	
	if(num == Level[0]){
		index = 0;
	}
	
	else if(Level[0] < num && num <= Level[1])	index = 1;
	else if(Level[1] < num && num <= Level[2])	index = 2;
	else if(Level[2] < num && num <= Level[3])	index = 3;
	else if(Level[3] < num && num <= Level[4])	index = 4;
	else if(Level[4] < num && num <= Level[5])	index = 5;
	else if(Level[5] < num && num <= Level[6])	index = 6;
	else if(Level[6] < num && num <= Level[7])	index = 7;
	else if(Level[7] < num && num <= Level[8])	index = 8;
    else if(Level[8] < num && num <= Level[9])	index = 9;
    
    double xt = point + r/Index[index];
    double yt = 100+ r/Index[index];
    
    int dem = 0;
    bool flag = false;
    
    glColor3ub(0, 255, 0);

	for(int i=0;i<Index[index];i++){
		for(int j=0;j<Index[index];j++){
			glLoadIdentity();
    		glTranslatef(xt, yt, 0);
    		drawFilledSun(Index[index]);
    		xt += 2*r/Index[index];
    		dem++;
			if(dem>=num) {
				flag = true;
				break;
			}
				
		}
		if(flag == true)	break;
		if(dem>=num) break;
		xt = point + r/Index[index];
		yt += 2*r/Index[index];
	}
	glColor3ub(255, 255, 255);
	
}
