#include "museum.h"
#include "building.h"
#include "interior.h"
#include "objects.h"
#include "textures.h"
#include "collision.h"
#include "lighting.h"
#include <GL/freeglut.h>

// === DEKLARASI EKSTERNAL ===
extern bool doorOpen;
extern float doorAngle;
extern GLuint textures[10];
extern float animTime;

void drawMuseum() {
    drawQuadGround(0, 0, 0, 35, 35, 0.2f, 0.6f, 0.2f);
    drawPerimeterWall();
    drawCourtyardFloor(0, 0, 27.5f, 21.5f);
    drawRoad(0, -10, 20, 3.0f);
    drawRoad(0, 10, 20, 3.0f, 0.005f);
    
    drawInteriorFloor(0, 0.05f, 0.0f, 9.5f, 5.5f);
    
    // ===== INTERIOR =====
    drawCarpet(0, 0, 1.5f);
    drawDisplayTable(0, 0);
    drawDisplayTable(-4, -2);
    drawDisplayTable(4, -2);
    drawDisplayTable(-4, 3);
    drawDisplayTable(4, 3);
    drawInteriorStatue(-2.5f, -1.5f);
    drawInteriorStatue(2.5f, -1.5f);
    drawInteriorStatue(0, 2.5f);
    drawChair(-8.0f, -4.5f);
    drawChair(8.0f, -4.5f);
    drawChair(-8.0f, 4.5f);
    drawChair(8.0f, 4.5f);
    
    drawPainting(-9.7f, 2.5f, -3.0f, 0.0f);
    drawPainting(-9.7f, 2.5f, 0.0f, 0.0f);
    drawPainting(-9.7f, 2.5f, 3.0f, 0.0f);
    drawPainting(9.7f, 2.5f, -3.0f, 180.0f);
    drawPainting(9.7f, 2.5f, 0.0f, 180.0f);
    drawPainting(9.7f, 2.5f, 3.0f, 180.0f);
    drawPainting(-5.0f, 2.5f, -5.7f, 0.0f);
    drawPainting(0.0f, 2.5f, -5.7f, 0.0f);
    drawPainting(5.0f, 2.5f, -5.7f, 0.0f);
    
    drawVase(-3.0f, 4.5f);
    drawVase(3.0f, 4.5f);
    drawGlassCase(-6.5f, -3.5f);
    drawGlassCase(6.5f, -3.5f);
    drawGlassCase(-6.5f, 3.5f);
    drawGlassCase(6.5f, 3.5f);
    
    // ===== BANGUNAN =====
    drawMainBuildingHollow();
    drawCube(0, 5.0f + 1.75f, 0, 16, 3.5f, 9, 0.75f, 0.75f, 0.75f);
    drawPolygonRoof(0, 8.52f, 0, 8.3f, 3.0f, 4.9f, 0.5f, 0.3f, 0.15f);

    float pilarZ = 8.6f;
    float pilarX[6] = { -8.0f, -4.8f, -1.6f, 1.6f, 4.8f, 8.0f };
    for (int i = 0; i < 6; i++) {
        drawCylinder(pilarX[i], 0.0f, pilarZ, 0.35f, 5.0f, 1.0f, 1.0f, 1.0f);
        drawCube(pilarX[i], 0.15f, pilarZ, 0.9f, 0.3f, 0.9f, 1.0f, 1.0f, 1.0f);
        drawCube(pilarX[i], 5.0f, pilarZ, 0.9f, 0.3f, 0.9f, 1.0f, 1.0f, 1.0f);
    }

    drawCube(0, 4.8f, pilarZ, 18.0f, 0.4f, 3.0f, 0.9f, 0.9f, 0.9f);
    drawTexturedCube(0, 0.05f, 7.8f, 20.0f, 0.1f, 4.4f, 6, 0.5f, 0.3f, 0.15f);
    drawTexturedCube(0, 0.065f, 4.5f, 3.5f, 0.1f, 1.5f, 6, 0.5f, 0.5f, 0.5f);
    drawDoor(0, 6.0f);
    
    // ============================================================
    // ===== ORANG BERJALAN =====
    // ============================================================
    for (int i = 0; i < 5; i++) {
        if (persons[i].active) {
            drawPerson(persons[i].x, persons[i].z, persons[i].angle, persons[i].phase);
        }
    }
    
    // ============================================================
    // ===== AIR MANCUR (DI SINI - BUKAN DI OBJECTS.CPP) =====
    // ============================================================
    drawFountain(0.0f, 10.0f, 1.5f);   // Tengah depan, size besar
    drawFountain(7.0f, 11.0f, 0.8f);   // Kanan depan
    drawFountain(-7.0f, 11.0f, 0.8f);  // Kiri depan
    
    // ============================================================
    // ===== JENDELA =====
    // ============================================================
    drawTexturedCube(-6.0f, 2.5f, 6.13f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(6.0f, 2.5f, 6.13f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(-8.0f, 2.5f, 6.13f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(8.0f, 2.5f, 6.13f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(-5.0f, 6.0f, 4.63f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(5.0f, 6.0f, 4.63f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(0.0f, 6.0f, 4.63f, 1.3f, 1.3f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(-10.13f, 2.5f, 0.0f, 0.2f, 1.3f, 1.3f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(-10.13f, 2.5f, -4.0f, 0.2f, 1.3f, 1.3f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(10.13f, 2.5f, 0.0f, 0.2f, 1.3f, 1.3f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(10.13f, 2.5f, -4.0f, 0.2f, 1.3f, 1.3f, 5, 0.75f, 0.85f, 0.9f);
    
    // ===== GEDUNG SAMPING =====
    drawBuilding(-16, -3, 4, 4, 4, 0.75f, 0.75f, 0.75f, true, 3);
    drawPolygonRoof(-16, 4.02f, -3, 2.2f, 1.5f, 2.2f, 0.5f, 0.3f, 0.15f);
    drawTexturedCube(-16, 2.5f, -1.1f, 1.0f, 1.0f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(-16, 2.5f, 1.1f, 1.0f, 1.0f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    
    drawBuilding(16, -3, 4, 4, 4, 0.75f, 0.75f, 0.75f, true, 3);
    drawPolygonRoof(16, 4.02f, -3, 2.2f, 1.5f, 2.2f, 0.5f, 0.3f, 0.15f);
    drawTexturedCube(16, 2.5f, -1.1f, 1.0f, 1.0f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    drawTexturedCube(16, 2.5f, 1.1f, 1.0f, 1.0f, 0.2f, 5, 0.75f, 0.85f, 0.9f);
    
    // ===== GEDUNG BELAKANG =====
    drawBuilding(-16, 5, 3, 3.5, 3, 0.75f, 0.75f, 0.75f, true, 0);
    drawPolygonRoof(-16, 3.52f, 5, 1.7f, 1.2f, 1.7f, 0.5f, 0.3f, 0.15f);
    
    drawBuilding(16, 5, 3, 3.5, 3, 0.75f, 0.75f, 0.75f, true, 0);
    drawPolygonRoof(16, 3.52f, 5, 1.7f, 1.2f, 1.7f, 0.5f, 0.3f, 0.15f);
    
    // ===== POHON =====
    drawTree(-22, -12);
    drawTree(-20, 14);
    drawTree(20, -14);
    drawTree(22, 12);
    drawTree(-22, 12);
    drawTree(22, -12);
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
    drawTree(-9, -18);
    drawTree(9, -18);
    drawTree(0, -19);
    
    // ===== LAMPU =====
    drawLamp(-12, -8);
    drawLamp(-6, -8);
    drawLamp(6, -8);
    drawLamp(12, -8);
    
    // Mobil dihapus
    // drawCar(-8, -12);
    // drawCar(8, -12);
    // drawCar(-4, -14);
    // drawCar(4, -14);
}