#include "lighting.h"
#include <GL/freeglut.h>

float lightPos1[] = { -10.0f, 15.0f, 0.0f, 1.0f };
float lightPos2[] = { 10.0f, 15.0f, 0.0f, 1.0f };
float lightPos3[] = { 0.0f, 20.0f, 0.0f, 1.0f };

void setupLighting() {
    // Ambient light
    GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    // Light 1 - Diffuse and Specular (from left)
    GLfloat diffuse1[] = { 0.8f, 0.8f, 0.7f, 1.0f };
    GLfloat specular1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
    glEnable(GL_LIGHT0);
    
    // Light 2 - Diffuse and Specular (from right)
    GLfloat diffuse2[] = { 0.7f, 0.7f, 0.8f, 1.0f };
    GLfloat specular2[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
    glEnable(GL_LIGHT1);
    
    // Light 3 - Top light
    GLfloat diffuse3[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat specular3[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse3);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular3);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
    glEnable(GL_LIGHT2);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
}

void setMaterial(float r, float g, float b, float shininess) {
    GLfloat ambient[] = { r * 0.3f, g * 0.3f, b * 0.3f, 1.0f };
    GLfloat diffuse[] = { r * 0.8f, g * 0.8f, b * 0.8f, 1.0f };
    GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glColor3f(r, g, b);
}