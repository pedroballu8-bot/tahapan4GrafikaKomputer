#include "collision.h"
#include <vector>

std::vector<AABB> solidBoxes;
std::vector<Circle> solidCircles;
const float PLAYER_RADIUS = 0.4f;

void buildCollisionBoxes() {
    solidBoxes.clear();

    // Dinding gedung utama (lantai 1)
    solidBoxes.push_back({ -10.0f, 10.0f, -6.0f, -5.7f });
    solidBoxes.push_back({ -10.0f, -9.7f, -6.0f, 6.0f });
    solidBoxes.push_back({ 9.7f, 10.0f, -6.0f, 6.0f });
    solidBoxes.push_back({ -10.0f, -1.0f, 5.7f, 6.0f });
    solidBoxes.push_back({ 1.0f, 10.0f, 5.7f, 6.0f });

    // Gedung samping kiri & kanan
    solidBoxes.push_back({ -18.0f, -14.0f, -5.0f, -1.0f });
    solidBoxes.push_back({ 14.0f, 18.0f, -5.0f, -1.0f });

    // Gedung belakang kiri & kanan
    solidBoxes.push_back({ -17.5f, -14.5f, 3.5f, 6.5f });
    solidBoxes.push_back({ 14.5f, 17.5f, 3.5f, 6.5f });

    // Pagar beton keliling
    solidBoxes.push_back({ -28.0f, 28.0f, -22.15f, -21.85f });
    solidBoxes.push_back({ -28.15f, -27.85f, -22.0f, 22.0f });
    solidBoxes.push_back({ 27.85f, 28.15f, -22.0f, 22.0f });
    solidBoxes.push_back({ -28.0f, -3.0f, 21.85f, 22.15f });
    solidBoxes.push_back({ 3.0f, 28.0f, 21.85f, 22.15f });

    solidCircles.clear();

    // Pilar depan kolonade
    float pilarPosX[6] = { -8.0f, -4.8f, -1.6f, 1.6f, 4.8f, 8.0f };
    for (int i = 0; i < 6; i++) {
        solidCircles.push_back({ pilarPosX[i], 8.6f, 0.4f });
    }

    // Pohon
    float treePos[][2] = {
        { -22, -12 }, { -20, 14 }, { 20, -14 }, { 22, 12 }, { -22, 12 }, { 22, -12 },
        { -24, -18 }, { -24, -4 }, { -24, 2 }, { -24, 8 }, { -24, 18 },
        { -20, -18 }, { -19, -6 }, { -19, 0 }, { -20, 18 }, { -13, -18 }, { -13, 18 },
        { 24, -18 }, { 24, -4 }, { 24, 2 }, { 24, 8 }, { 24, 18 },
        { 20, -18 }, { 19, -6 }, { 19, 0 }, { 20, 18 }, { 13, -18 }, { 13, 18 },
        { -9, -18 }, { 9, -18 }, { 0, -19 }
    };
    for (int i = 0; i < 31; i++) {
        solidCircles.push_back({ treePos[i][0], treePos[i][1], 0.6f });
    }

    // Lampu jalan
    float lampPos[][2] = { { -12, -8 }, { -6, -8 }, { 6, -8 }, { 12, -8 } };
    for (int i = 0; i < 4; i++) {
        solidCircles.push_back({ lampPos[i][0], lampPos[i][1], 0.3f });
    }

    // Mobil
    float carPos[][2] = { { -8, -12 }, { 8, -12 }, { -4, -14 }, { 4, -14 } };
    for (int i = 0; i < 4; i++) {
        solidCircles.push_back({ carPos[i][0], carPos[i][1], 1.4f });
    }
}

bool collidesAt(float x, float z) {
    for (size_t i = 0; i < solidBoxes.size(); i++) {
        const AABB& b = solidBoxes[i];
        if (x + PLAYER_RADIUS > b.xmin && x - PLAYER_RADIUS < b.xmax &&
            z + PLAYER_RADIUS > b.zmin && z - PLAYER_RADIUS < b.zmax) {
            return true;
        }
    }
    for (size_t i = 0; i < solidCircles.size(); i++) {
        const Circle& c = solidCircles[i];
        float dx = x - c.cx;
        float dz = z - c.cz;
        float minDist = c.radius + PLAYER_RADIUS;
        if (dx * dx + dz * dz < minDist * minDist) {
            return true;
        }
    }
    return false;
}