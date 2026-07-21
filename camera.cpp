#include "camera.h"
#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>

Camera::Camera() {
    camX = 0.0f;
    camY = 6.0f;
    camZ = 28.0f;
    yaw = 0.0f;
    pitch = 0.0f;
    mouseX = 0;
    mouseY = 0;
    mousePressed = false;
}

void Camera::keyboard(unsigned char key, int x, int y) {
    float speed = 0.5f;
    float dirX = sin(yaw);
    float dirZ = -cos(yaw);
    float strafeX = cos(yaw);
    float strafeZ = sin(yaw);
    
    switch(key) {
        case 'w': camX += dirX * speed; camZ += dirZ * speed; break;
        case 's': camX -= dirX * speed; camZ -= dirZ * speed; break;
        case 'a': camX -= strafeX * speed; camZ -= strafeZ * speed; break;
        case 'd': camX += strafeX * speed; camZ += strafeZ * speed; break;
        case 'q': camY += speed; break;
        case 'e': camY -= speed; break;
        case 'r': reset(); break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void Camera::mouse(int button, int state, int x, int y) {
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

void Camera::mouseMotion(int x, int y) {
    if (mousePressed) {
        float sensitivity = 0.005f;
        float dx = x - mouseX;
        float dy = y - mouseY;
        
        yaw += dx * sensitivity;
        pitch -= dy * sensitivity;
        
        if (pitch > 1.4f) pitch = 1.4f;
        if (pitch < -1.4f) pitch = -1.4f;
        
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

void Camera::reset() {
    camX = 0.0f;
    camY = 6.0f;
    camZ = 28.0f;
    yaw = 0.0f;
    pitch = 0.0f;
}

void Camera::apply() {
    gluLookAt(
        camX, camY, camZ,
        camX + sin(yaw) * cos(pitch), 
        camY + sin(pitch), 
        camZ - cos(yaw) * cos(pitch),
        0.0, 1.0, 0.0
    );
}