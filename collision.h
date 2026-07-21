#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

struct AABB {
    float xmin, xmax, zmin, zmax;
};

struct Circle {
    float cx, cz, radius;
};

extern std::vector<AABB> solidBoxes;
extern std::vector<Circle> solidCircles;
extern const float PLAYER_RADIUS;

void buildCollisionBoxes();
bool collidesAt(float x, float z);

#endif