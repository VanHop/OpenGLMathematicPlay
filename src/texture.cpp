#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include "texture.h"
int texture::LoadBitmap(char *filename){
	FILE * file;
    char temp;
    long i;

    BITMAPINFOHEADER infoheader;
    unsigned char *infoheader_data;

    GLuint num_texture;

    if( (file = fopen(filename, "rb"))==NULL) return (-1);

    fseek(file, 18, SEEK_CUR);
    fread(&infoheader.biWidth, sizeof(int), 1, file);

    fread(&infoheader.biHeight, sizeof(int), 1, file);

    fread(&infoheader.biPlanes, sizeof(short int), 1, file);
    if (infoheader.biPlanes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
		return 0;
    }


    fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
    if (infoheader.biBitCount != 24) {
		printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
		return 0;
    }

    fseek(file, 24, SEEK_CUR);


    if(infoheader.biWidth<0)
		infoheader.biWidth = -infoheader.biWidth;
    if(infoheader.biHeight<0)
		infoheader.biHeight = -infoheader.biHeight;
    infoheader_data = (unsigned char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
    if (infoheader_data == NULL) {
      printf("Error allocating memory for color-corrected image data\n");
      return 0;
    }

    if ((i = fread(infoheader_data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
      printf("Error reading image data from %s.\n", filename);
      return 0;
    }

    for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { 
      temp = infoheader_data[i];
      infoheader_data[i] = infoheader_data[i+2];
      infoheader_data[i+2] = temp;
    }


    fclose(file); 

    glGenTextures(1, &num_texture);
    glBindTexture(GL_TEXTURE_2D, num_texture);

    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   
    glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, infoheader_data);

    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, infoheader_data);

    free(infoheader_data);

    return (num_texture);
}

void texture::Load(char *filename){
	bg = gluNewQuadric();
	gluQuadricTexture( bg, GL_TRUE);
	bgTexture = LoadBitmap(filename);
}
