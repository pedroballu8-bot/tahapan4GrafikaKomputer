#ifndef OBJECTS_H
#define OBJECTS_H

// Variabel global untuk animasi
extern float animTime;
extern float fountainTime;

// Struktur untuk orang berjalan
struct WalkingPerson {
    float x, z;
    float angle;
    float speed;
    float phase;
    float pathRadius;
    float centerX, centerZ;
    bool active;
};

extern WalkingPerson persons[5];

void drawLamp(float x, float z);
void drawTree(float x, float z);
void drawCar(float x, float z);
void drawHumanStatue(float x, float z);
void drawHalte(float x, float z);
void drawFountain(float x, float z, float size = 1.0f);
void drawPerson(float x, float z, float angle, float phase);
void updatePersonPositions();
void initPersonPositions();

#endif