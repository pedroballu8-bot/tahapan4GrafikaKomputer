#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>

// ============================================================
// GLOBAL VARIABLES
// ============================================================
bool doorOpen = false;
float doorAngle = 0.0f;

// ============================================================
// CAMERA CLASS
// ============================================================
class Camera {
public:
    float camX, camY, camZ;
    float yaw, pitch;
    int mouseX, mouseY;
    bool mousePressed;
    float speed;
    float sensitivity;
    
    Camera() {
        camX = 0.0f; camY = 8.0f; camZ = 35.0f;
        yaw = 0.0f; pitch = -0.2f;
        mouseX = 0; mouseY = 0;
        mousePressed = false;
        speed = 0.6f;
        sensitivity = 0.005f;
    }
    
    void keyboard(unsigned char key, int x, int y) {
        float dirX = sin(yaw);
        float dirZ = -cos(yaw);
        float strafeX = cos(yaw);
        float strafeZ = sin(yaw);
        
        switch(key) {
            case 'w': case 'W':
                camX += dirX * speed;
                camZ += dirZ * speed;
                break;
            case 's': case 'S':
                camX -= dirX * speed;
                camZ -= dirZ * speed;
                break;
            case 'a': case 'A':
                camX -= strafeX * speed;
                camZ -= strafeZ * speed;
                break;
            case 'd': case 'D':
                camX += strafeX * speed;
                camZ += strafeZ * speed;
                break;
            case 'q': case 'Q':
                camY += speed;
                break;
            case 'e': case 'E':
                camY -= speed;
                break;
            case 'r': case 'R':
                reset();
                break;
            case ' ':
                toggleDoor();
                break;
            case 27:
                exit(0);
                break;
        }
        glutPostRedisplay();
    }
    
    void mouse(int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                mousePressed = true;
                mouseX = x;
                mouseY = y;
            } else {
                mousePressed = false;
            }
        }
    }
    
    void mouseMotion(int x, int y) {
        if (mousePressed) {
            float dx = x - mouseX;
            float dy = y - mouseY;
            
            yaw += dx * sensitivity;
            pitch -= dy * sensitivity;
            
            if (pitch > 1.5f) pitch = 1.5f;
            if (pitch < -1.5f) pitch = -1.5f;
            
            mouseX = x;
            mouseY = y;
            glutPostRedisplay();
        }
    }
    
    void reset() {
        camX = 0.0f;
        camY = 8.0f;
        camZ = 35.0f;
        yaw = 0.0f;
        pitch = -0.2f;
    }
    
    void apply() {
        gluLookAt(
            camX, camY, camZ,
            camX + sin(yaw) * cos(pitch), 
            camY + sin(pitch), 
            camZ - cos(yaw) * cos(pitch),
            0.0, 1.0, 0.0
        );
    }
    
    void toggleDoor() {
        doorOpen = !doorOpen;
        printf("Pintu %s\n", doorOpen ? "TERBUKA" : "TERTUTUP");
    }
};

Camera camera;

// ============================================================
// LIGHTING
// ============================================================
float lightPos1[] = { -15.0f, 20.0f, 5.0f, 1.0f };
float lightPos2[] = { 15.0f, 20.0f, -5.0f, 1.0f };
float lightPos3[] = { 0.0f, 25.0f, 0.0f, 1.0f };
float lightPos4[] = { 0.0f, 12.0f, 25.0f, 1.0f };

void setupLighting() {
    GLfloat ambientLight[] = { 0.35f, 0.35f, 0.35f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    GLfloat diffuse1[] = { 0.8f, 0.8f, 0.7f, 1.0f };
    GLfloat specular1[] = { 0.6f, 0.6f, 0.5f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
    glEnable(GL_LIGHT0);
    
    GLfloat diffuse2[] = { 0.7f, 0.7f, 0.8f, 1.0f };
    GLfloat specular2[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
    glEnable(GL_LIGHT1);
    
    GLfloat diffuse3[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat specular3[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse3);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular3);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
    glEnable(GL_LIGHT2);
    
    GLfloat diffuse4[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat specular4[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse4);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular4);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPos4);
    glEnable(GL_LIGHT3);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
}

void setMaterial(float r, float g, float b, float shininess = 32.0f) {
    GLfloat ambient[] = { r * 0.3f, g * 0.3f, b * 0.3f, 1.0f };
    GLfloat diffuse[] = { r * 0.8f, g * 0.8f, b * 0.8f, 1.0f };
    GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glColor3f(r, g, b);
}

// ============================================================
// TEXTURES
// ============================================================
GLuint textures[10];
const char* textureFiles[10] = {
    "brick.bmp", "wood.bmp", "grass.bmp", "stone.bmp", "roof.bmp",
    "glass.bmp", "floor.bmp", "road.bmp", "metal.bmp", "door.bmp"
};

GLuint loadBMPTexture(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    unsigned char textureData[64][64][3];
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            textureData[i][j][0] = 255;
            textureData[i][j][1] = 255;
            textureData[i][j][2] = 255;
        }
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    return textureID;
}

void loadTextures() {
    for (int i = 0; i < 10; i++) {
        textures[i] = loadBMPTexture(textureFiles[i]);
    }
}

// ============================================================
// DRAWING FUNCTIONS
// ============================================================
void drawTexturedCube(float x, float y, float z, float sx, float sy, float sz, 
                      int texID, float r = 1.0f, float g = 1.0f, float b = 1.0f) {
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

void drawCone(float x, float y, float z, float base, float height, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90, 1, 0, 0);
    setMaterial(r, g, b);
    glutSolidCone(base, height, 24, 24);
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

    // Sisi miring kiri
    glBegin(GL_QUADS);
        glNormal3f(-h, w, 0);
        glVertex3f(-w, 0, -d);
        glVertex3f(-w, 0, d);
        glVertex3f(0, h, d);
        glVertex3f(0, h, -d);
    glEnd();

    // Sisi miring kanan
    glBegin(GL_QUADS);
        glNormal3f(h, w, 0);
        glVertex3f(w, 0, -d);
        glVertex3f(0, h, -d);
        glVertex3f(0, h, d);
        glVertex3f(w, 0, d);
    glEnd();

    // Segitiga atap bagian depan
    glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, -1);
        glVertex3f(-w, 0, -d);
        glVertex3f(0, h, -d);
        glVertex3f(w, 0, -d);
    glEnd();

    // Segitiga atap bagian belakang
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

void drawCourtyardFloor(float x, float z, float w, float d) {
    glPushMatrix();
    glTranslatef(x, 0.015f, z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]); // brick texture

    setMaterial(0.6f, 0.6f, 0.6f); // abu-abu
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

void drawRoad(float x, float z, float length, float width, float yOffset = 0.0f) {
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

// ============================================================
// OBJECT DRAWING FUNCTIONS
// ============================================================
void drawLamp(float x, float z) {
    drawCylinder(x, 0.0f, z, 0.12f, 4.0f, 0.6f, 0.6f, 0.6f);
    drawSphere(x, 4.2f, z, 0.25f, 1.0f, 1.0f, 0.7f);
}

void drawTree(float x, float z) {
    drawCylinder(x, 0.0f, z, 0.25f, 2.0f, 0.45f, 0.25f, 0.1f);
    drawSphere(x, 2.8f, z, 1.8f, 0.1f, 0.55f, 0.15f);
    drawSphere(x - 0.7f, 2.5f, z, 1.2f, 0.12f, 0.5f, 0.12f);
    drawSphere(x + 0.7f, 2.5f, z, 1.2f, 0.12f, 0.5f, 0.12f);
}

void drawCar(float x, float z) {
    drawCube(x, 0.5f, z, 2.4f, 0.6f, 1.1f, 0.8f, 0.1f, 0.1f);
    drawCube(x, 1.0f, z, 1.4f, 0.5f, 1.0f, 0.9f, 0.2f, 0.2f);
    drawSphere(x - 1.0f, 0.2f, z + 0.8f, 0.45f, 0.05f, 0.05f, 0.05f);
    drawSphere(x + 1.0f, 0.2f, z + 0.8f, 0.45f, 0.05f, 0.05f, 0.05f);
    drawSphere(x - 1.0f, 0.2f, z - 0.8f, 0.45f, 0.05f, 0.05f, 0.05f);
    drawSphere(x + 1.0f, 0.2f, z - 0.8f, 0.45f, 0.05f, 0.05f, 0.05f);
}

void drawHumanStatue(float x, float z) {
    drawCylinder(x, 0.0f, z, 0.35f, 2.0f, 0.7f, 0.7f, 0.75f);
    drawSphere(x, 2.4f, z, 0.7f, 0.75f, 0.75f, 0.8f);
    drawCone(x, 0.0f, z, 0.8f, 1.2f, 0.55f, 0.55f, 0.6f);
}

void drawHalte(float x, float z) {
    drawCube(x, 0.2f, z, 2.0f, 0.1f, 0.9f, 0.85f, 0.85f, 0.9f);
    drawCylinder(x - 1.2f, 0.0f, z - 0.7f, 0.1f, 2.5f, 0.5f, 0.5f, 0.5f);
    drawCylinder(x + 1.2f, 0.0f, z - 0.7f, 0.1f, 2.5f, 0.5f, 0.5f, 0.5f);
    drawCube(x, 2.4f, z - 0.7f, 2.6f, 0.05f, 0.6f, 0.3f, 0.6f, 0.9f);
}

// ============================================================
// DRAW BUILDING - URUTAN PARAMETER YANG BENAR
// ============================================================
void drawBuilding(float x, float z, float sx, float sy, float sz, 
                  float r, float g, float b, bool textured = false, int texID = 0) {
    if (textured) {
        drawTexturedCube(x, sy/2.0f, z, sx, sy, sz, texID, r, g, b);
    } else {
        drawCube(x, sy/2.0f, z, sx, sy, sz, r, g, b);
    }
}

// ============================================================
// DOOR WITH ANIMATION
// ============================================================
void drawDoor(float x, float z) {
    float targetAngle = doorOpen ? 90.0f : 0.0f;
    doorAngle += (targetAngle - doorAngle) * 0.05f;
    
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    
    drawCube(-0.8f, 1.5f, 0.0f, 0.12f, 3.0f, 0.12f, 0.4f, 0.3f, 0.2f);
    drawCube(0.8f, 1.5f, 0.0f, 0.12f, 3.0f, 0.12f, 0.4f, 0.3f, 0.2f);
    drawCube(0.0f, 3.0f, 0.0f, 0.9f, 0.12f, 0.12f, 0.4f, 0.3f, 0.2f);
    drawCube(0.0f, 0.0f, 0.0f, 0.9f, 0.12f, 0.12f, 0.4f, 0.3f, 0.2f);
    
    // Pintu kiri
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
    
    // Pintu kanan
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

// ============================================================
// FENCE
// ============================================================
void drawFence(float x, float z, float length) {
    for (int i = 0; i < (int)length; i++) {
        drawCube(x + i * 1.0f, 0.6f, z, 0.12f, 1.2f, 0.12f, 0.7f, 0.7f, 0.7f);
        drawCube(x + i * 1.0f, 1.1f, z, 0.6f, 0.08f, 0.08f, 0.7f, 0.7f, 0.7f);
    }
}

// ============================================================
// INTERIOR FLOOR - LANTAI DI DALAM GEDUNG
// ============================================================
void drawInteriorFloor(float x, float y, float z, float w, float d) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[6]); // floor texture
    
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

// ============================================================
// PAGAR BETON KELILING + GERBANG MASUK
// ============================================================
void drawPerimeterWall() {
    float wallH = 2.5f;      // tinggi pagar = setengah tinggi lantai 1 gedung museum
    float wallT = 0.3f;      // ketebalan pagar
    float half = wallH / 2.0f;
    float gateHalfWidth = 3.0f; // lebar gerbang (total 6 meter)
    float xMin = -28.0f, xMax = 28.0f, zMin = -22.0f, zMax = 22.0f;
    float cr = 0.55f, cg = 0.55f, cb = 0.55f; // warna beton abu-abu

    // Dinding belakang (utuh)
    drawCube(0.0f, half, zMin, xMax - xMin, wallH, wallT, cr, cg, cb);

    // Dinding kiri & kanan (utuh)
    drawCube(xMin, half, 0.0f, wallT, wallH, zMax - zMin, cr, cg, cb);
    drawCube(xMax, half, 0.0f, wallT, wallH, zMax - zMin, cr, cg, cb);

    // Dinding depan - kiri gerbang
    float frontLeftLen = (-gateHalfWidth) - xMin;
    float frontLeftCenter = (xMin + (-gateHalfWidth)) / 2.0f;
    drawCube(frontLeftCenter, half, zMax, frontLeftLen, wallH, wallT, cr, cg, cb);

    // Dinding depan - kanan gerbang
    float frontRightLen = xMax - gateHalfWidth;
    float frontRightCenter = (gateHalfWidth + xMax) / 2.0f;
    drawCube(frontRightCenter, half, zMax, frontRightLen, wallH, wallT, cr, cg, cb);

    // ===== GERBANG MASUK =====
    // Tiang gerbang (lebih tinggi dari pagar)
    drawCube(-gateHalfWidth, (wallH + 0.5f) / 2.0f, zMax, 0.4f, wallH + 0.5f, 0.4f, 0.5f, 0.5f, 0.5f);
    drawCube(gateHalfWidth, (wallH + 0.5f) / 2.0f, zMax, 0.4f, wallH + 0.5f, 0.4f, 0.5f, 0.5f, 0.5f);

    // Plang/lintel di atas gerbang
    drawCube(0.0f, wallH + 0.5f, zMax, gateHalfWidth * 2.0f + 0.4f, 0.3f, 0.4f, 0.45f, 0.45f, 0.45f);
}

// ============================================================
// MUSEUM SCENE - DENGAN LANTAI DI DALAM
// ============================================================
// ============================================================
// GEDUNG UTAMA BERONGGA - DINDING + PLAFON DENGAN LUBANG PINTU
// (menggantikan kotak solid supaya bisa benar-benar dimasuki tanpa glitch)
// ============================================================
void drawMainBuildingHollow() {
    float wr = 0.75f, wg = 0.75f, wb = 0.75f;
    float wallH = 5.0f;
    float wallT = 0.3f;

    // Plafon dihapus - bagian bawah kotak lantai 2 sudah berfungsi sebagai langit-langit lantai 1

    // Dinding belakang (sisi luar rata di z = -6.0)
    drawCube(0, wallH / 2.0f, -5.85f, 20, wallH, wallT, wr, wg, wb);

    // Dinding kiri (sisi luar rata di x = -10.0)
    drawCube(-9.85f, wallH / 2.0f, 0, wallT, wallH, 12, wr, wg, wb);

    // Dinding kanan (sisi luar rata di x = 10.0)
    drawCube(9.85f, wallH / 2.0f, 0, wallT, wallH, 12, wr, wg, wb);

    // Dinding depan - kiri pintu
    drawCube(-5.5f, wallH / 2.0f, 5.85f, 9.0f, wallH, wallT, wr, wg, wb);
    // Dinding depan - kanan pintu
    drawCube(5.5f, wallH / 2.0f, 5.85f, 9.0f, wallH, wallT, wr, wg, wb);
    // Ambang atas lubang pintu
    drawCube(0, 4.1f, 5.85f, 2.0f, 1.8f, wallT, wr, wg, wb);
}

void drawMuseum() {
    drawQuadGround(0, 0, 0, 35, 35, 0.2f, 0.6f, 0.2f);
    
    // Pagar beton keliling + gerbang
    drawPerimeterWall();
    
    // Lantai bata abu-abu untuk halaman di dalam pagar
    drawCourtyardFloor(0, 0, 27.5f, 21.5f);
    
    // Jalan
    drawRoad(0, -10, 20, 3.0f);
    drawRoad(0, 10, 20, 3.0f, 0.005f);
    
    // ===== LANTAI DI DALAM GEDUNG UTAMA =====
    drawInteriorFloor(0, 0.05f, 0.0f, 9.5f, 5.5f);
    
    // ===== GEDUNG UTAMA - MUSEUM KLASIK 2 LANTAI DENGAN PILAR DEPAN =====
    // Lantai 1 (dasar) - dibuat berongga (dinding + plafon, ada lubang pintu) supaya bisa dimasuki tanpa glitch
    drawMainBuildingHollow();

    // Lantai 2 (agak masuk/set-back, khas gedung klasik bertingkat)
    drawCube(0, 5.0f + 1.75f, 0, 16, 3.5f, 9, 0.75f, 0.75f, 0.75f);

    // Atap di atas lantai 2 (menempel pas di puncak, y = 5 + 3.5 = 8.5)
    drawPolygonRoof(0, 8.52f, 0, 8.3f, 3.0f, 4.9f, 0.5f, 0.3f, 0.15f);

    // ===== PILAR DEPAN (KOLONADE GAYA KLASIK) =====
    // Pilar dimajukan (z 6.8 -> 8.6) agar sejajar dengan tepi depan teras
    float pilarZ = 8.6f;
    float pilarX[6] = { -8.0f, -4.8f, -1.6f, 1.6f, 4.8f, 8.0f };
    for (int i = 0; i < 6; i++) {
        drawCylinder(pilarX[i], 0.0f, pilarZ, 0.35f, 5.0f, 1.0f, 1.0f, 1.0f);
        drawCube(pilarX[i], 0.15f, pilarZ, 0.9f, 0.3f, 0.9f, 1.0f, 1.0f, 1.0f);  // alas pilar
        drawCube(pilarX[i], 5.0f, pilarZ, 0.9f, 0.3f, 0.9f, 1.0f, 1.0f, 1.0f);   // kepala pilar
    }

    // Atap depan teras - dibuat datar/lurus (bukan segitiga pedimen), warna putih seperti gedung
    // Sisi atasnya dibuat sejajar (rata) dengan puncak lantai 1 (y = 5.0)
    drawCube(0, 4.8f, pilarZ, 18.0f, 0.4f, 3.0f, 0.9f, 0.9f, 0.9f);

    // ===== TERAS DEPAN (DI LUAR, DI BAWAH KOLONADE) =====
    // Diperlebar kiri-kanan (sx 10 -> 20) dan diperdalam (sz 3.2 -> 4.4) supaya pilar tidak menggantung di luar tepi lantai
    // Warna disamakan dengan atap (coklat)
    drawTexturedCube(0, 0.05f, 7.8f, 20.0f, 0.1f, 4.4f, 6, 0.5f, 0.3f, 0.15f);
    
    // ===== LANTAI DALAM (DI DEPAN PINTU, DI DALAM) =====
    drawTexturedCube(0, 0.065f, 4.5f, 3.5f, 0.1f, 1.5f, 6, 0.5f, 0.5f, 0.5f);
    
    // Pintu utama
    drawDoor(0, 6.0f);
    
    // ===== JENDELA LANTAI 1 =====
    drawTexturedCube(-6.0f, 2.5f, 6.13f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(6.0f, 2.5f, 6.13f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(-8.0f, 2.5f, 6.13f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(8.0f, 2.5f, 6.13f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);

    // ===== JENDELA LANTAI 2 =====
    drawTexturedCube(-5.0f, 6.0f, 4.63f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(5.0f, 6.0f, 4.63f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(0.0f, 6.0f, 4.63f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);

    drawTexturedCube(-10.13f, 2.5f, 0.0f, 0.2f, 1.3f, 1.3f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(-10.13f, 2.5f, -4.0f, 0.2f, 1.3f, 1.3f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(10.13f, 2.5f, 0.0f, 0.2f, 1.3f, 1.3f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(10.13f, 2.5f, -4.0f, 0.2f, 1.3f, 1.3f, 5, 0.75f, 0.85f, 0.9f);
    
    // ===== GEDUNG SAMPING KIRI =====
    drawBuilding(-16, -3, 4, 4, 4, 0.75f, 0.75f, 0.75f, true, 3);
    // FIX: atap sebelumnya di y=5.0 sedangkan puncak gedung ada di y=4 (sy=4) -> melayang 1.0
    drawPolygonRoof(-16, 4.02f, -3, 2.2f, 1.5f, 2.2f, 0.5f, 0.3f, 0.15f);
    drawTexturedCube(-16, 2.5f, -1.1f, 1.0f, 1.0f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(-16, 2.5f, 1.1f, 1.0f, 1.0f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    
    // ===== GEDUNG SAMPING KANAN =====
    drawBuilding(16, -3, 4, 4, 4, 0.75f, 0.75f, 0.75f, true, 3);
    // FIX: sama seperti gedung samping kiri
    drawPolygonRoof(16, 4.02f, -3, 2.2f, 1.5f, 2.2f, 0.5f, 0.3f, 0.15f);
    drawTexturedCube(16, 2.5f, -1.1f, 1.0f, 1.0f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(16, 2.5f, 1.1f, 1.0f, 1.0f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    
    // ===== GEDUNG BELAKANG KIRI =====
    drawBuilding(-16, 5, 3, 3.5, 3, 0.75f, 0.75f, 0.75f, true, 0);
    // FIX: atap sebelumnya di y=5.5 sedangkan puncak gedung ada di y=3.5 (sy=3.5) -> melayang 2.0
    drawPolygonRoof(-16, 3.52f, 5, 1.7f, 1.2f, 1.7f, 0.5f, 0.3f, 0.15f);
    
    // ===== GEDUNG BELAKANG KANAN =====
    drawBuilding(16, 5, 3, 3.5, 3, 0.75f, 0.75f, 0.75f, true, 0);
    // FIX: sama seperti gedung belakang kiri
    drawPolygonRoof(16, 3.52f, 5, 1.7f, 1.2f, 1.7f, 0.5f, 0.3f, 0.15f);
    
    // Patung dihapus
    
    // Pohon
    drawTree(-22, -12);
    drawTree(-20, 14);
    drawTree(20, -14);
    drawTree(22, 12);
    drawTree(-22, 12);
    drawTree(22, -12);

    // Pohon tambahan - tersebar di sekeliling halaman gedung
    // Sisi kiri
    drawTree(-24, -18);
    drawTree(-24, -4);
    drawTree(-24, 2);
    drawTree(-24, 8);
    drawTree(-24, 18);
    drawTree(-20, -18);
    drawTree(-19, -6);
    drawTree(-19, 0);
    drawTree(-20, 18);
    drawTree(-13, -18);
    drawTree(-13, 18);

    // Sisi kanan
    drawTree(24, -18);
    drawTree(24, -4);
    drawTree(24, 2);
    drawTree(24, 8);
    drawTree(24, 18);
    drawTree(20, -18);
    drawTree(19, -6);
    drawTree(19, 0);
    drawTree(20, 18);
    drawTree(13, -18);
    drawTree(13, 18);

    // Belakang gedung
    drawTree(-9, -18);
    drawTree(9, -18);
    drawTree(0, -19);
    
    // Lampu
    drawLamp(-12, -8);
    drawLamp(-6, -8);
    drawLamp(6, -8);
    drawLamp(12, -8);
    
    // Pagar lama dihapus (sudah digantikan pagar beton keliling)
    
    // Mobil
    drawCar(-8, -12);
    drawCar(8, -12);
    drawCar(-4, -14);
    drawCar(4, -14);
    
    // Halte dihapus
}

// ============================================================
// MAIN PROGRAM
// ============================================================
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera.apply();
    setupLighting();
    drawMuseum();
    glutSwapBuffers();
}

void update(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    camera.keyboard(key, x, y);
}

void mouse(int button, int state, int x, int y) {
    camera.mouse(button, state, x, y);
}

void mouseMotion(int x, int y) {
    camera.mouseMotion(x, y);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.3f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.65f, 0.85f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    loadTextures();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.33, 0.3f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Museum Smart City - Dengan Lantai Dalam Gedung");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}