#include "building.h"
#include "lighting.h"
#include "textures.h"
#include <GL/freeglut.h>

bool doorOpen = false;
float doorAngle = 0.0f;

void drawTexturedCube(float x, float y, float z, float sx, float sy, float sz, 
                      int texID, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    
    setMaterial(r, g, b);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[texID]);
    
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
        
        glNormal3f(0, 0, -1);
        glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, -0.5f);
        
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
        glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, 0.5f);
        
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
        
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
        glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
        
        glNormal3f(0, -1, 0);
        glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
        glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawCube(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    setMaterial(r, g, b);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawSphere(float x, float y, float z, float s, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(s, s, s);
    setMaterial(r, g, b);
    glutSolidSphere(0.5, 24, 24);
    glPopMatrix();
}

void drawCylinder(float x, float y, float z, float radius, float height, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90, 1, 0, 0);
    setMaterial(r, g, b);
    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, radius, radius, height, 24, 24);
    gluDisk(q, 0.0, radius, 24, 1);
    glTranslatef(0, 0, height);
    gluDisk(q, 0.0, radius, 24, 1);
    gluDeleteQuadric(q);
    glPopMatrix();
}

void drawPolygonRoof(float x, float y, float z, float w, float h, float d, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    setMaterial(r, g, b);

    glBegin(GL_QUADS);
        glNormal3f(-h, w, 0);
        glVertex3f(-w, 0, -d);
        glVertex3f(-w, 0, d);
        glVertex3f(0, h, d);
        glVertex3f(0, h, -d);
    glEnd();

    glBegin(GL_QUADS);
        glNormal3f(h, w, 0);
        glVertex3f(w, 0, -d);
        glVertex3f(0, h, -d);
        glVertex3f(0, h, d);
        glVertex3f(w, 0, d);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, -1);
        glVertex3f(-w, 0, -d);
        glVertex3f(0, h, -d);
        glVertex3f(w, 0, -d);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, 1);
        glVertex3f(-w, 0, d);
        glVertex3f(w, 0, d);
        glVertex3f(0, h, d);
    glEnd();

    glPopMatrix();
}

void drawQuadGround(float x, float y, float z, float w, float d, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    setMaterial(r, g, b);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-w, 0, -d);
        glVertex3f(w, 0, -d);
        glVertex3f(w, 0, d);
        glVertex3f(-w, 0, d);
    glEnd();
    glPopMatrix();
}

// ===== TAMBAHAN FUNGSI YANG HILANG =====

void drawCourtyardFloor(float x, float z, float w, float d) {
    glPushMatrix();
    glTranslatef(x, 0.015f, z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    setMaterial(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0); glVertex3f(-w, 0, -d);
        glTexCoord2f(14, 0); glVertex3f(w, 0, -d);
        glTexCoord2f(14, 11); glVertex3f(w, 0, d);
        glTexCoord2f(0, 11); glVertex3f(-w, 0, d);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawRoad(float x, float z, float length, float width, float yOffset) {
    glPushMatrix();
    glTranslatef(x, 0.02f + yOffset, z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    setMaterial(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0); glVertex3f(-width, 0, -length);
        glTexCoord2f(10, 0); glVertex3f(width, 0, -length);
        glTexCoord2f(10, 10); glVertex3f(width, 0, length);
        glTexCoord2f(0, 10); glVertex3f(-width, 0, length);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawFence(float x, float z, float length) {
    for (int i = 0; i < (int)length; i++) {
        drawCube(x + i * 1.0f, 0.6f, z, 0.12f, 1.2f, 0.12f, 0.7f, 0.7f, 0.7f);
        drawCube(x + i * 1.0f, 1.1f, z, 0.6f, 0.08f, 0.08f, 0.7f, 0.7f, 0.7f);
    }
}

void drawBuilding(float x, float z, float sx, float sy, float sz, 
                  float r, float g, float b, bool textured, int texID) {
    if (textured) {
        drawTexturedCube(x, sy/2.0f, z, sx, sy, sz, texID, r, g, b);
    } else {
        drawCube(x, sy/2.0f, z, sx, sy, sz, r, g, b);
    }
}

void drawInteriorFloor(float x, float y, float z, float w, float d) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[6]);
    setMaterial(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0); glVertex3f(-w, 0, -d);
        glTexCoord2f(4, 0); glVertex3f(w, 0, -d);
        glTexCoord2f(4, 4); glVertex3f(w, 0, d);
        glTexCoord2f(0, 4); glVertex3f(-w, 0, d);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawDoor(float x, float z) {
    float targetAngle = doorOpen ? 90.0f : 0.0f;
    doorAngle += (targetAngle - doorAngle) * 0.05f;
    
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    
    drawCube(-0.8f, 1.5f, 0.0f, 0.12f, 3.0f, 0.12f, 0.4f, 0.3f, 0.2f);
    drawCube(0.8f, 1.5f, 0.0f, 0.12f, 3.0f, 0.12f, 0.4f, 0.3f, 0.2f);
    drawCube(0.0f, 3.0f, 0.0f, 0.9f, 0.12f, 0.12f, 0.4f, 0.3f, 0.2f);
    drawCube(0.0f, 0.0f, 0.0f, 0.9f, 0.12f, 0.12f, 0.4f, 0.3f, 0.2f);
    
    glPushMatrix();
    glTranslatef(-0.7f, 1.5f, 0.05f);
    glRotatef(doorAngle, 0.0f, -1.0f, 0.0f);
    glTranslatef(0.35f, 0.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[9]);
    setMaterial(0.6f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glTexCoord2f(0, 0); glVertex3f(-0.35f, -1.5f, -0.05f);
        glTexCoord2f(1, 0); glVertex3f(0.35f, -1.5f, -0.05f);
        glTexCoord2f(1, 1); glVertex3f(0.35f, 1.5f, -0.05f);
        glTexCoord2f(0, 1); glVertex3f(-0.35f, 1.5f, -0.05f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.7f, 1.5f, 0.05f);
    glRotatef(-doorAngle, 0.0f, -1.0f, 0.0f);
    glTranslatef(-0.35f, 0.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[9]);
    setMaterial(0.6f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glTexCoord2f(0, 0); glVertex3f(-0.35f, -1.5f, -0.05f);
        glTexCoord2f(1, 0); glVertex3f(0.35f, -1.5f, -0.05f);
        glTexCoord2f(1, 1); glVertex3f(0.35f, 1.5f, -0.05f);
        glTexCoord2f(0, 1); glVertex3f(-0.35f, 1.5f, -0.05f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    drawSphere(-0.4f, 1.5f, -0.2f, 0.08f, 0.8f, 0.7f, 0.2f);
    drawSphere(0.4f, 1.5f, -0.2f, 0.08f, 0.8f, 0.7f, 0.2f);
    
    glPopMatrix();
}

void drawMainBuildingHollow() {
    float wr = 0.75f, wg = 0.75f, wb = 0.75f;
    float wallH = 5.0f;
    float wallT = 0.3f;

    drawCube(0, wallH / 2.0f, -5.85f, 20, wallH, wallT, wr, wg, wb);
    drawCube(-9.85f, wallH / 2.0f, 0, wallT, wallH, 12, wr, wg, wb);
    drawCube(9.85f, wallH / 2.0f, 0, wallT, wallH, 12, wr, wg, wb);
    drawCube(-5.5f, wallH / 2.0f, 5.85f, 9.0f, wallH, wallT, wr, wg, wb);
    drawCube(5.5f, wallH / 2.0f, 5.85f, 9.0f, wallH, wallT, wr, wg, wb);
    drawCube(0, 4.1f, 5.85f, 2.0f, 1.8f, wallT, wr, wg, wb);
}

void drawPerimeterWall() {
    float wallH = 2.5f;
    float wallT = 0.3f;
    float half = wallH / 2.0f;
    float gateHalfWidth = 3.0f;
    float xMin = -28.0f, xMax = 28.0f, zMin = -22.0f, zMax = 22.0f;
    float cr = 0.55f, cg = 0.55f, cb = 0.55f;

    drawCube(0.0f, half, zMin, xMax - xMin, wallH, wallT, cr, cg, cb);
    drawCube(xMin, half, 0.0f, wallT, wallH, zMax - zMin, cr, cg, cb);
    drawCube(xMax, half, 0.0f, wallT, wallH, zMax - zMin, cr, cg, cb);

    float frontLeftLen = (-gateHalfWidth) - xMin;
    float frontLeftCenter = (xMin + (-gateHalfWidth)) / 2.0f;
    drawCube(frontLeftCenter, half, zMax, frontLeftLen, wallH, wallT, cr, cg, cb);

    float frontRightLen = xMax - gateHalfWidth;
    float frontRightCenter = (gateHalfWidth + xMax) / 2.0f;
    drawCube(frontRightCenter, half, zMax, frontRightLen, wallH, wallT, cr, cg, cb);

    drawCube(-gateHalfWidth, (wallH + 0.5f) / 2.0f, zMax, 0.4f, wallH + 0.5f, 0.4f, 0.5f, 0.5f, 0.5f);
    drawCube(gateHalfWidth, (wallH + 0.5f) / 2.0f, zMax, 0.4f, wallH + 0.5f, 0.4f, 0.5f, 0.5f, 0.5f);
    drawCube(0.0f, wallH + 0.5f, zMax, gateHalfWidth * 2.0f + 0.4f, 0.3f, 0.4f, 0.45f, 0.45f, 0.45f);
}
void drawCone(float x, float y, float z, float base, float height, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90, 1, 0, 0);
    setMaterial(r, g, b);
    glutSolidCone(base, height, 24, 24);
    glPopMatrix();
}