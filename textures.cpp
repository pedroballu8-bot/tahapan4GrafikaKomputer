#include "textures.h"
#include <cstring>

GLuint textures[10];
const char* textureFiles[10] = {
    "brick.bmp", "wood.bmp", "grass.bmp", "stone.bmp", "roof.bmp",
    "glass.bmp", "floor.bmp", "road.bmp", "metal.bmp", "door.bmp"
};

GLuint loadBMPTexture(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Fallback texture (checkerboard pattern)
    unsigned char textureData[64][64][3];
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            bool isBlack = ((i / 8) + (j / 8)) % 2 == 0;
            textureData[i][j][0] = isBlack ? 128 : 255;
            textureData[i][j][1] = isBlack ? 128 : 255;
            textureData[i][j][2] = isBlack ? 128 : 255;
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