
#include <stdio.h> 
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include "print.h"
#include "Block.h"
#include "Button.h"

const double PI = atan(1.0)*4;

Button::Button(){
	value = -1;
}

Button::Button(Point position, int width, int height, bool enable,int value,char name,char *filename, char *filename1){
	this->position = position;
	this->root = position;
	this->width = width;
	this->height = height;
	this->Enable = enable;
	this->value = value;
	this->name = name;
	t.Load(filename);
	buffer.Load(filename1);
	Click = false;
	Focus = false;
}

bool Button::isWithinButton(int x, int y){
	
	if(x > position.x && x < position.x + width && y > position.y && y < position.y + height)
		return true;
	return false;
}

void Button::setClick(bool state){
	Click = state;
}

void Button::setFocus(bool state){
	Focus = state;
}

void Button::setRelease(bool state){
	Release = state;
}

void Button::setSize(){
	if(Click){
		width--;
		height--;
	}
	else{
		width++;
		height++;
	}
}

bool Button::isClick(){
	return Click;
}

bool Button::isFocus(){
	return Focus;
}

bool Button::isRelease(){
	return Release;
}

bool Button::isEnable(){
	return Enable;
}

void Button::setEnable(bool state){
	Enable = state;
}
void Button::draw(){	 
	
	if(Enable){
		glEnable ( GL_TEXTURE_2D );
		glBindTexture ( GL_TEXTURE_2D, t.bgTexture);
		
		if(Focus == true)
			glBindTexture ( GL_TEXTURE_2D, buffer.bgTexture);
		
		if (name == 'G' || name == 'N'){
			float angle, radian, x, y, tx, ty, xcos, ysin;
			int rX = width/2, 
				rY = height/2,
				centerX = position.x + rX,
				centerY = position.y + rY;

   			glBegin(GL_POLYGON);
    		for (angle=0.0; angle<360.0; angle+=2.0)
    		{
        		radian = angle * (PI/180.0f);

				xcos = (float)cos(radian);
				ysin = (float)sin(radian);
				
				x = xcos * rX  + centerX;
				y = ysin * rY  + centerY;
				
				tx = xcos * 0.5 + 0.5;
				ty = ysin * 0.5 + 0.5;

				glTexCoord2f(tx, ty);
				glVertex2f(x, y);
    		}
    		glEnd();
		} 
		else {
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(position.x, position.y);
				glTexCoord2f(1.0f, 1.0f); glVertex2f(position.x + width, position.y);
				glTexCoord2f(1.0f, 0.0f); glVertex2f(position.x + width, position.y + height);
				glTexCoord2f(0.0f, 0.0f);glVertex2f(position.x, position.y + height);
			glEnd();
		}
		glDisable ( GL_TEXTURE_2D );
		
		if(value > 0){
			Point p(position.x + width/2, position.y + height/2);
			print(p, value, name);
		}
		else{
			int v =(int)name - '0';
			Point p(position.x + width/2, position.y + height/2);
			print(p, value, name);
		}
	}
}
void Button::setValue(int v){
	value = v;
}

int Button::getValue(){
	return value;
}

void Button::setName(char name){
	this->name= name;
}

char Button::getName(){
	return name;
}
