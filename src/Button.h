#ifndef BUTTON
#define BUTTON
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Point.h"
#include "texture.h"
using namespace std;
class Button{
	private:
		bool Focus, Click, Release, Enable;
		int value;
		char name;
		texture t;
		texture buffer;
		
	public:
		Point root;
		Point position;
		int width, height;
		Button();
		Button(Point, int, int, bool,int,char,char*,char*);
		bool isWithinButton(int, int);
		bool isEnable();
		bool isClick();
		bool isFocus();
		bool isRelease();
		void setClick(bool);
		void setFocus(bool);
		void setRelease(bool);
		void setEnable(bool);
		void setSize();
		void setValue(int);
		int getValue();
		void setName(char);
		char getName();
		void draw();
};
#endif
