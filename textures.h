#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/freeglut.h>

extern GLuint textures[10];

void loadTextures();
GLuint loadBMPTexture(const char* filename);

#endif