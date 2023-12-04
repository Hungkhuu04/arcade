#include "lib/Renderer.h"
#include <GL/glut.h>
#include <cmath>
#include <algorithm>
void Renderer::RenderPlayer(float x, float y) {
    // For now, represent the player as a green square
    glColor3f(0.0f, 1.0f, 0.0f); // Set color to green
    glRectf(x - 0.05f, y - 0.05f, x + 0.05f, y + 0.05f);
}

void Renderer::RenderZombie(float x, float y, float width, float height) {
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glRectf(x - width / 2.0f, y - height / 2.0f, x + width / 2.0f, y + height / 2.0f);
}


void Renderer::RenderBullet(float x, float y, float width, float height) {
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glRectf(x - width / 2.0f, y - height / 2.0f, x + width / 2.0f, y + height / 2.0f);
}

void Renderer::DrawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float degInRad = i * 3.14159f / 180.0f;
        glVertex2f(x + std::cos(degInRad) * radius, y + std::sin(degInRad) * radius);
    }
    glEnd();
}
