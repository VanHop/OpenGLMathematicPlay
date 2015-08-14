#ifndef _LOAD_
#define _LOAD_
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class texture{
	public:
		
		GLUquadric *bg;
		GLuint bgTexture;
		int LoadBitmap(char *);
		void Load(char*);
		
};
#endif
