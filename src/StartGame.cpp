#include "StartGame.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#include <iostream>
using namespace std;
StartGame::StartGame(){
	
}

StartGame::StartGame(char *path, bool state){
	start = Button(Point(1200,650), 100,70, true, -1 , 'S', "../image/next.bmp", "../image/next1.bmp");
	t.Load(path);
	enable = state;
}

void StartGame::display(){
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
	start.draw();
	
}

void StartGame::setEnable(bool state){
	enable = state;
	start.setEnable(state);
}

bool StartGame::isEnable(){
	return enable;
}
