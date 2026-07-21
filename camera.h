#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    float camX, camY, camZ;
    float yaw, pitch;
    int mouseX, mouseY;
    bool mousePressed;
    
    Camera();
    void update();
    void keyboard(unsigned char key, int x, int y);
    void mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);
    void reset();
    void apply();
};

#endif