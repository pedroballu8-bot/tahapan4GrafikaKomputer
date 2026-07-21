#ifndef BUILDING_H
#define BUILDING_H

#include <GL/freeglut.h>

// Forward declarations
void drawCube(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b);
void drawSphere(float x, float y, float z, float s, float r, float g, float b);
void drawCylinder(float x, float y, float z, float radius, float height, float r, float g, float b);
void drawCone(float x, float y, float z, float base, float height, float r, float g, float b);
void drawPolygonRoof(float x, float y, float z, float w, float h, float d, float r, float g, float b);
void drawQuadGround(float x, float y, float z, float w, float d, float r, float g, float b);
void drawTexturedCube(float x, float y, float z, float sx, float sy, float sz, int texID, float r = 1.0f, float g = 1.0f, float b = 1.0f);
void drawBuilding(float x, float z, float sx, float sy, float sz, float r, float g, float b, bool textured = false, int texID = 0);
void drawInteriorFloor(float x, float y, float z, float w, float d);
void drawCourtyardFloor(float x, float z, float w, float d);
void drawRoad(float x, float z, float length, float width, float yOffset = 0.0f);
void drawDoor(float x, float z);
void drawMainBuildingHollow();
void drawPerimeterWall();
void drawFence(float x, float z, float length);

// Global variables
extern bool doorOpen;
extern float doorAngle;

#endif