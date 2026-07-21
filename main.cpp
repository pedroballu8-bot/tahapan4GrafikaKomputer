#include <GL/freeglut.h>
#include "camera.h"
#include "lighting.h"
#include "textures.h"
#include "museum.h"
#include "collision.h"
#include "objects.h"

// === DEFINISI GLOBAL CAMERA ===
Camera camera;

// ============================================================
// UPDATE ANIMASI - DIPANGGIL SETIAP FRAME
// ============================================================
void updateAnimation() {
    animTime += 0.016f;  // Tambah waktu (sekitar 60fps)
    updatePersonPositions();  // Update posisi orang berjalan
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    camera.apply();
    setupLighting();
    
    // Update animasi sebelum menggambar
    updateAnimation();
    
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
    gluPerspective(60.0, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.65f, 0.85f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    loadTextures();
    buildCollisionBoxes();
    initPersonPositions();  // Inisialisasi posisi orang
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.33, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Museum Smart City - Animasi & Interaksi");

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