#include "interior.h"
#include "building.h"
#include "lighting.h"
#include <GL/freeglut.h>
#include <cmath>  // <-- TAMBAHKAN INI

// Variabel global dari objects.cpp
extern float animTime;

void drawDisplayTable(float x, float z) {
    drawCube(x, 0.8f, z, 1.8f, 0.1f, 1.2f, 0.6f, 0.4f, 0.2f);
    drawCube(x - 0.8f, 0.4f, z - 0.55f, 0.08f, 0.8f, 0.08f, 0.5f, 0.5f, 0.5f);
    drawCube(x + 0.8f, 0.4f, z - 0.55f, 0.08f, 0.8f, 0.08f, 0.5f, 0.5f, 0.5f);
    drawCube(x - 0.8f, 0.4f, z + 0.55f, 0.08f, 0.8f, 0.08f, 0.5f, 0.5f, 0.5f);
    drawCube(x + 0.8f, 0.4f, z + 0.55f, 0.08f, 0.8f, 0.08f, 0.5f, 0.5f, 0.5f);
    
    glPushMatrix();
    glTranslatef(x, 0.9f, z);
    glScalef(1.7f, 0.02f, 1.1f);
    glDisable(GL_LIGHTING);
    glColor4f(0.7f, 0.8f, 1.0f, 0.3f);
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// ============================================================
// PATUNG DI DALAM MUSEUM - DENGAN ANIMASI BERPUTAR
// ============================================================
void drawInteriorStatue(float x, float z) {
    float rotAngle = animTime * 15.0f;  // Berputar perlahan
    
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glRotatef(rotAngle, 0, 1, 0);
    
    // Base (alas)
    drawCube(0, 0.1f, 0, 0.6f, 0.05f, 0.6f, 0.7f, 0.7f, 0.7f);
    
    // Badan patung
    drawCylinder(0, 0.1f, 0, 0.2f, 1.2f, 0.8f, 0.8f, 0.85f);
    
    // Kepala
    drawSphere(0, 1.5f, 0, 0.25f, 0.85f, 0.85f, 0.9f);
    
    // Lengan kanan (bergerak sedikit)
    float armAngle = sin(animTime * 0.5f) * 10.0f;
    glPushMatrix();
    glTranslatef(0.35f, 0.6f, 0);
    glRotatef(armAngle, 0, 0, 1);
    drawCylinder(0, 0, 0, 0.06f, 0.5f, 0.8f, 0.8f, 0.85f);
    glPopMatrix();
    
    // Lengan kiri (bergerak sedikit)
    glPushMatrix();
    glTranslatef(-0.35f, 0.6f, 0);
    glRotatef(-armAngle, 0, 0, 1);
    drawCylinder(0, 0, 0, 0.06f, 0.5f, 0.8f, 0.8f, 0.85f);
    glPopMatrix();
    
    glPopMatrix();
}

void drawChair(float x, float z) {
    drawCube(x, 0.3f, z, 0.5f, 0.05f, 0.5f, 0.4f, 0.3f, 0.2f);
    drawCube(x - 0.2f, 0.15f, z - 0.2f, 0.05f, 0.3f, 0.05f, 0.3f, 0.3f, 0.3f);
    drawCube(x + 0.2f, 0.15f, z - 0.2f, 0.05f, 0.3f, 0.05f, 0.3f, 0.3f, 0.3f);
    drawCube(x - 0.2f, 0.15f, z + 0.2f, 0.05f, 0.3f, 0.05f, 0.3f, 0.3f, 0.3f);
    drawCube(x + 0.2f, 0.15f, z + 0.2f, 0.05f, 0.3f, 0.05f, 0.3f, 0.3f, 0.3f);
    drawCube(x - 0.25f, 0.5f, z + 0.25f, 0.05f, 0.5f, 0.5f, 0.4f, 0.3f, 0.2f);
}

void drawPainting(float x, float y, float z, float rotY) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotY, 0, 1, 0);
    
    drawCube(0, 0, 0, 1.0f, 0.8f, 0.05f, 0.6f, 0.4f, 0.2f);
    
    glPushMatrix();
    glTranslatef(0, 0, 0.03f);
    glScalef(0.8f, 0.6f, 0.02f);
    setMaterial(0.9f, 0.2f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0.1f, 0.035f);
    glScalef(0.6f, 0.02f, 0.01f);
    setMaterial(0.9f, 0.8f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, -0.1f, 0.035f);
    glScalef(0.6f, 0.02f, 0.01f);
    setMaterial(0.9f, 0.8f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}

void drawVase(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.3f, z);
    glRotatef(-90, 1, 0, 0);
    setMaterial(0.2f, 0.5f, 0.3f);
    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, 0.15f, 0.2f, 0.3f, 16, 16);
    gluDeleteQuadric(q);
    glPopMatrix();
    
    drawSphere(x + 0.1f, 0.6f, z + 0.1f, 0.08f, 1.0f, 0.2f, 0.2f);
    drawSphere(x - 0.1f, 0.65f, z + 0.05f, 0.07f, 1.0f, 0.8f, 0.2f);
    drawSphere(x + 0.05f, 0.7f, z - 0.1f, 0.09f, 1.0f, 0.2f, 0.8f);
    drawSphere(x - 0.08f, 0.6f, z - 0.08f, 0.07f, 1.0f, 0.8f, 0.8f);
    drawSphere(x + 0.08f, 0.55f, z + 0.05f, 0.06f, 1.0f, 1.0f, 0.2f);
}

void drawGlassCase(float x, float z) {
    drawCube(x, 0.05f, z, 1.0f, 0.05f, 0.8f, 0.5f, 0.5f, 0.5f);
    drawSphere(x, 0.25f, z, 0.12f, 0.8f, 0.7f, 0.2f);
    drawCylinder(x + 0.15f, 0.2f, z + 0.1f, 0.05f, 0.15f, 0.6f, 0.4f, 0.2f);
    drawCylinder(x - 0.15f, 0.2f, z - 0.1f, 0.05f, 0.15f, 0.6f, 0.4f, 0.2f);
    
    glPushMatrix();
    glTranslatef(x, 0.35f, z);
    glScalef(0.9f, 0.3f, 0.7f);
    glDisable(GL_LIGHTING);
    glColor4f(0.7f, 0.8f, 1.0f, 0.2f);
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void drawCarpet(float x, float z, float radius) {
    glPushMatrix();
    glTranslatef(x, 0.02f, z);
    glScalef(radius, 0.01f, radius);
    setMaterial(0.6f, 0.1f, 0.1f);
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();
}