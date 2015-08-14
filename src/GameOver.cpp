#include "GameOver.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;
GameOver::GameOver(){
	
}

GameOver::GameOver(char *path, bool state){
	tryAgain = Button(Point(620,600), 100,70, true, -1 , 'O', "../image/go.bmp", "../image/try.bmp");
	t.Load(path);
	enable = state;
	tryAgain.setEnable(false);
}

void GameOver::setKQ(int mang[], char pt[]){
	for(int i=0; i<4; i++)
		kq[i] = mang[i];
		
	for(int i=0; i<3; i++){
		phepToan[i] = pt[i];
		cout << phepToan[i];
	}
		
	
}

void yourScore(int x, int y,void* font, const char* string)
{
	glRasterPos2f( x , y);
	char* p = (char*) string;
	while (*p != '\0') glutBitmapCharacter(font, *p++);
}

void convert(int xx, int yy,int k,char c){
	if(k < 0){
		char x[1];
		x[0] = c;
		x[1] = '\0';
		yourScore(xx,yy,GLUT_BITMAP_TIMES_ROMAN_24, x);
		return;
	}
	if(0 <= k && k < 10){
		char x[1];
		char s = (char)k + '0';
		x[0] = s;
		x[1] = '\0';
		yourScore(xx,yy,GLUT_BITMAP_TIMES_ROMAN_24, x);
	}
	else if( 10 <= k && k <100){
		char x[2];
		for(int i=0;i<2;i++){
			int temp = k % 10;
			k = (k -temp)/10;
			x[1-i] = (char)temp + '0';
		}
		x[2] = '\0';
		yourScore(xx ,yy,GLUT_BITMAP_TIMES_ROMAN_24, x);
	}
}


void GameOver::display(int score){
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
	char str[20];
	glColor3ub(100, 100, 255);
	sprintf(str, "Your Score - %3.0f", (float)score);
	yourScore(580, 500, GLUT_BITMAP_TIMES_ROMAN_24, str);

	convert(550,550,kq[0],' ');convert(580,550,-1,phepToan[0]);
	convert(610,550,kq[1],' ');convert(640,550,-1,phepToan[1]);
	convert(670,550,kq[2],' ');convert(700,550,-1,phepToan[2]);
	convert(730,550,kq[3],' ');
	glColor3ub(255, 255, 255);
	
	tryAgain.draw();
}

void GameOver::setEnable(bool state){
	enable = state;
	tryAgain.setEnable(state);
}

bool GameOver::isEnable(){
	return enable;
}
