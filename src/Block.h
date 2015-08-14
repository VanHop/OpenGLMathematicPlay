#ifndef BLOCK
#define BLOCK
#include <GL/glut.h>
#include "Point.h"
#include "Button.h"
#include "texture.h"
class Block{
	private:
		bool enable;
		bool haveButton;
		texture t;
	public:
		
		Button button;
		Point position;
		int width, height;
		Block();
		Block(Point,int,int,Button,bool,char*);
		void setEnable(bool);
		bool isEnable();
		void setHaveButton(bool);
		bool getHaveButton();
		bool isWithinBlock(Button);
		bool isWithinMouse(int, int);
		void draw();
};

#endif
