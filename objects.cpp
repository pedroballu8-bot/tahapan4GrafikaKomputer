#include "objects.h"
#include "building.h"
#include "lighting.h"
#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>

// ============================================================
// VARIABEL GLOBAL ANIMASI
// ============================================================
float animTime = 0.0f;
float fountainTime = 0.0f;

// Data orang berjalan
WalkingPerson persons[5];

// ============================================================
// FUNGSI OBJEK
// ============================================================

void drawLamp(float x, float z) {
    drawCylinder(x, 0.0f, z, 0.12f, 4.0f, 0.6f, 0.6f, 0.6f);
    
    // Lampu berkedip
    float blink = sin(animTime * 2.0f + x + z) * 0.3f + 0.7f;
    drawSphere(x, 4.2f, z, 0.25f, 1.0f * blink, 1.0f * blink, 0.7f * blink);
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
// FUNGSI ORANG BERJALAN
// ============================================================
void drawPerson(float x, float z, float angle, float phase) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glRotatef(angle, 0, 1, 0);
    
    float walkCycle = sin(animTime * 2.0f + phase);
    float step = walkCycle * 0.15f;
    
    // Badan
    drawCube(0, 1.0f, 0, 0.3f, 0.6f, 0.2f, 0.3f, 0.5f, 0.8f);
    
    // Kepala
    drawSphere(0, 1.6f, 0, 0.15f, 0.9f, 0.7f, 0.5f);
    
    // Kaki kiri
    glPushMatrix();
    glTranslatef(-0.1f, 0.3f, 0.1f + step);
    glScalef(0.06f, 0.6f, 0.06f);
    setMaterial(0.2f, 0.2f, 0.8f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Kaki kanan
    glPushMatrix();
    glTranslatef(0.1f, 0.3f, -0.1f - step);
    glScalef(0.06f, 0.6f, 0.06f);
    setMaterial(0.2f, 0.2f, 0.8f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Tangan kiri
    glPushMatrix();
    glTranslatef(-0.2f, 1.2f, step * 0.3f);
    glScalef(0.04f, 0.4f, 0.04f);
    setMaterial(0.9f, 0.7f, 0.5f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Tangan kanan
    glPushMatrix();
    glTranslatef(0.2f, 1.2f, -step * 0.3f);
    glScalef(0.04f, 0.4f, 0.04f);
    setMaterial(0.9f, 0.7f, 0.5f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
}

// ============================================================
// INISIALISASI POSISI ORANG
// ============================================================
void initPersonPositions() {
    // Orang 1 - berjalan di depan gedung
    persons[0] = {0, 12, 0, 0.8f, 0.0f, 4.0f, 0, 12, true};
    
    // Orang 2 - berjalan di samping kiri
    persons[1] = {-15, -2, 90, 0.6f, 1.5f, 3.0f, -15, -2, true};
    
    // Orang 3 - berjalan di samping kanan
    persons[2] = {15, 8, -90, 0.7f, 3.0f, 3.0f, 15, 8, true};
    
    // Orang 4 - berjalan di belakang
    persons[3] = {-5, -8, 180, 0.5f, 4.5f, 5.0f, -5, -8, true};
    
    // Orang 5 - berjalan di taman
    persons[4] = {20, -15, 45, 0.9f, 6.0f, 4.0f, 20, -15, true};
}

// ============================================================
// UPDATE POSISI ORANG
// ============================================================
void updatePersonPositions() {
    for (int i = 0; i < 5; i++) {
        if (persons[i].active) {
            // Gerak melingkar
            float angleOffset = animTime * persons[i].speed + persons[i].phase;
            persons[i].x = persons[i].centerX + persons[i].pathRadius * cos(angleOffset);
            persons[i].z = persons[i].centerZ + persons[i].pathRadius * sin(angleOffset);
            persons[i].angle = -angleOffset * 180 / 3.14159f + 90;
        }
    }
}

// ============================================================
// AIR MANCUR - VERSI BESAR & JELAS
// ============================================================
void drawFountain(float x, float z, float size) {
    float s = size * 1.5f;  // Perbesar 1.5x
    float time = animTime;
    
    // ===== KOLAM BAWAH (Biru terang) =====
    glPushMatrix();
    glTranslatef(x, 0.02f, z);
    glScalef(s * 3.0f, 0.1f, s * 3.0f);
    setMaterial(0.1f, 0.4f, 0.8f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Dinding kolam (putih)
    glPushMatrix();
    glTranslatef(x, 0.25f, z);
    glScalef(s * 3.2f, 0.4f, s * 3.2f);
    setMaterial(0.8f, 0.8f, 0.85f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Air di kolam (biru transparan)
    glPushMatrix();
    glTranslatef(x, 0.08f, z);
    glScalef(s * 2.8f, 0.05f, s * 2.8f);
    glDisable(GL_LIGHTING);
    glColor4f(0.2f, 0.6f, 1.0f, 0.5f);
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    // ===== TIANG TENGAH (Lebih tinggi) =====
    drawCylinder(x, 0.4f, z, s * 0.3f, s * 1.0f, 0.7f, 0.7f, 0.75f);
    drawCylinder(x, s * 1.2f + 0.4f, z, s * 0.15f, s * 1.5f, 0.75f, 0.75f, 0.8f);
    
    // ===== MANGKUK ATAS =====
    glPushMatrix();
    glTranslatef(x, s * 2.5f + 0.4f, z);
    glScalef(s * 0.9f, 0.2f, s * 0.9f);
    setMaterial(0.7f, 0.7f, 0.75f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Air di mangkuk
    glPushMatrix();
    glTranslatef(x, s * 2.6f + 0.4f, z);
    glScalef(s * 0.7f, 0.05f, s * 0.7f);
    glDisable(GL_LIGHTING);
    glColor4f(0.3f, 0.7f, 1.0f, 0.6f);
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    // ============================================================
    // ANIMASI SEMPROTAN AIR (Lebih banyak & besar)
    // ============================================================
    
    // Semburan air ke atas (tetesan besar)
    for (int i = 0; i < 40; i++) {
        float angle = (float)i / 40 * 2.0f * 3.14159f;
        float radius = s * (0.05f + 0.3f * (0.5f + 0.5f * sin(time * 1.5f + i * 0.5f)));
        float height = s * (0.5f + 1.8f * (0.5f + 0.5f * sin(time * 2.0f + i * 0.3f)));
        float offsetX = radius * cos(angle + time * 0.3f);
        float offsetZ = radius * sin(angle + time * 0.3f);
        
        glPushMatrix();
        glTranslatef(x + offsetX, s * 2.7f + 0.4f + height * 0.4f, z + offsetZ);
        glScalef(s * 0.08f, s * 0.15f, s * 0.08f);
        glDisable(GL_LIGHTING);
        glColor4f(0.5f, 0.8f, 1.0f, 0.9f);
        glutSolidSphere(0.5, 10, 10);
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    
    // Semburan melengkung ke samping
    for (int i = 0; i < 24; i++) {
        float angle = (float)i / 24 * 2.0f * 3.14159f;
        for (int j = 0; j < 6; j++) {
            float t = (float)j / 6.0f;
            float arcRadius = s * (0.2f + t * 2.0f);
            float arcHeight = s * (1.0f * sin(t * 3.14159f + time * 0.3f));
            float offsetX = arcRadius * cos(angle + t * 0.3f + time * 0.2f);
            float offsetZ = arcRadius * sin(angle + t * 0.3f + time * 0.2f);
            
            glPushMatrix();
            glTranslatef(x + offsetX, s * 2.7f + 0.4f + arcHeight, z + offsetZ);
            glScalef(s * 0.06f, s * 0.08f, s * 0.06f);
            glDisable(GL_LIGHTING);
            glColor4f(0.6f, 0.9f, 1.0f, 0.8f);
            glutSolidSphere(0.5, 8, 8);
            glEnable(GL_LIGHTING);
            glPopMatrix();
        }
    }
    
    // ===== EFEK AIR BERKILAU =====
    for (int i = 0; i < 20; i++) {
        float angle = (float)i / 20 * 2.0f * 3.14159f + time * 0.5f;
        float radius = s * (0.3f + 2.2f * (0.5f + 0.5f * sin(time * 1.2f + i * 0.3f)));
        float offsetX = radius * cos(angle);
        float offsetZ = radius * sin(angle);
        
        glPushMatrix();
        glTranslatef(x + offsetX, 0.06f, z + offsetZ);
        glScalef(s * 0.06f, s * 0.02f, s * 0.06f);
        glDisable(GL_LIGHTING);
        glColor4f(1.0f, 1.0f, 1.0f, 0.4f + 0.3f * sin(time * 3.0f + i));
        glutSolidSphere(0.5, 6, 6);
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    
    // ===== ORNAMEN DEKORATIF (Berputar) =====
    float rotAngle = time * 25.0f;
    glPushMatrix();
    glTranslatef(x, s * 3.0f + 0.4f, z);
    glRotatef(rotAngle, 0, 1, 0);
    
    // Patung di puncak (emas)
    drawSphere(0, 0, s * 0.2f, s * 0.1f, 0.9f, 0.8f, 0.3f);
    drawCone(0, s * 0.08f, s * 0.2f, s * 0.06f, s * 0.12f, 0.9f, 0.8f, 0.3f);
    drawCone(s * 0.05f, s * 0.1f, s * 0.2f + s * 0.05f, s * 0.04f, s * 0.08f, 0.9f, 0.8f, 0.3f);
    drawCone(-s * 0.05f, s * 0.1f, s * 0.2f + s * 0.05f, s * 0.04f, s * 0.08f, 0.9f, 0.8f, 0.3f);
    
    glPopMatrix();
}