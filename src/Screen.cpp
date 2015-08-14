#include "Screen.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <iostream>
#include <stdio.h>
using namespace std;
Screen::Screen(){
	
}

Screen::Screen(char *path, bool state){
	t.Load(path);
	enable = state;
}

void drawChar(Point ps, void* font, const char* string)
{
	glRasterPos2f( ps.x , ps.y);
	char* p = (char*) string;
	while (*p != '\0') glutBitmapCharacter(font, *p++);
}

void Screen::display(Block A,Block B, vector<Button> button, Button Go, 
			Button Swap,Button Cong,Button Tru, Button Nhan, Button Chia,Button CounterTime, Button help, int score){
		glLoadIdentity();
		glEnable ( GL_TEXTURE_2D );
		glBindTexture ( GL_TEXTURE_2D, t.bgTexture);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(0,0);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(1366,0);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(1366,768);
		glTexCoord2f(0.0f, 0.0f);glVertex2f(0, 768);
		glEnd();
		glDisable ( GL_TEXTURE_2D );

		
		A.draw();B.draw();
		
		Cong.draw();Tru.draw();Nhan.draw();Chia.draw();
		
		Go.draw();Swap.draw();
		
		for(int i=0;i<button.size();i++)
			button.at(i).draw();
		
		CounterTime.draw();
		char str[12];
		sprintf(str, "%3.0f", (float)CounterTime.width);
		
		drawChar(Point(CounterTime.position.x + CounterTime.width, CounterTime.position.y - 5),GLUT_BITMAP_HELVETICA_18, str);
		
		glColor3ub(100, 100, 255);
		
		sprintf(str, "Your Score - %3.0f", (float)score);
		
		drawChar(Point(540,150),   GLUT_BITMAP_TIMES_ROMAN_24, str);
		help.draw();
		glColor3ub(255, 255, 255);
}

void Screen::setEnable(bool state){
	enable = state;
}

bool Screen::isEnable(){
	return enable;
}

