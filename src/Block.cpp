
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>   // The GL Utility Toolkit (GLUT) Header
#include "Block.h"

Block::Block(){}

Block::Block(Point position, int width, int height,Button button,bool state,char *filename){
	this->position = position;
	this->width = width;
	this->height = height;
	this->button = button;
	this->haveButton = state;
	t.Load(filename);
}

bool Block::isWithinMouse(int x, int y){
	if(x > position.x && x < position.x + width && y > position.y && y < position.y + height)
		return true;
	return false;
}

bool Block::isWithinBlock(Button a){
	if(a.position.x > position.x && a.position.y > position.y &&  a.position.x < position.x + width && a.position.y < position.y + height||
		a.position.x + a.width < position.x + width && a.position.y > position.y && a.position.x + a.width > position.x && a.position.y < position.y + height||
		a.position.x > position.x && a.position.y + a.height < position.y + height && a.position.x < position.x + width && a.position.y + a.height > position.y||
		a.position.x + a.width < position.x + width && a.position.y + a.height < position.y + height &&
		a.position.x + a.width > position.x && a.position.y + a.height > position.y 
		)
		
		return true;
	return false;
}

void Block::draw(){
	
	glEnable ( GL_TEXTURE_2D );
	glBindTexture ( GL_TEXTURE_2D, t.bgTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(position.x, position.y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(position.x + width, position.y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(position.x + width, position.y + height);
		glTexCoord2f(0.0f, 1.0f);glVertex2f(position.x, position.y + height);
	glEnd();
	glDisable ( GL_TEXTURE_2D );
	
	if(haveButton)	button.draw();
}

void Block::setEnable(bool state){
	enable = state;
}

bool Block::isEnable(){
	return enable;
}

void Block::setHaveButton(bool state){
	haveButton = state;
	if(state == false)
		button = Button();
}

bool Block::getHaveButton(){
	return haveButton;
}
