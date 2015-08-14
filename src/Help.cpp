#include "Help.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#include <iostream>
using namespace std;
Help::Help(){
	
}

Help::Help(char *path, bool state){
	t.Load(path);
	enable = state;
}

void Help::display(){
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
	
}

void Help::setEnable(bool state){
	enable = state;
}

bool Help::isEnable(){
	return enable;
}
