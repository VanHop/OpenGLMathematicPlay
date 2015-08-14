#ifndef HEADER
#define HEADER

#define WCX 1366        // Window Width
#define WCY 768        // Window Height
#include <stdio.h>     // Standard C/C++ IO  
#include <windows.h>   // Standard Header For MSWindows Applications
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>   // The GL Utility Toolkit (GLUT) Header
#include "Point.h"

Point p[4] = { Point(200,600),
			   Point(350,600),
			   Point(500,600),
			   Point(650,600)
			};

enum Operator { ADD = '+', SUB = '-', MUL = '*', DIV = '/' };

const float TIME = 300;
const float DELTIME = 0.012; 

void render(int x,int y,void* font, const char* string)
{
	glRasterPos2f( x , y);
	char* p = (char*) string;
	while (*p != '\0') glutBitmapCharacter(font, *p++);
}


#endif
