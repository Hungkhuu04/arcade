// Zombie.cpp
#include "zombie.h"
#include <GL/glut.h>
#include <cmath>

Zombie::Zombie(float x, float y) : x(x), y(y), speed(2.0f) {
}

void Zombie::update(int playerX, int playerY) {
        // Calculate direction towards the player
        float deltaX = playerX - x;
        float deltaY = playerY - y;

        float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        float normX = deltaX / distance;
        float normY = deltaY / distance;

        // Move towards the player
        x += normX * speed;
        y += normY * speed;

        // Boundary checks
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > 800) x = 800;
        if (y > 600) y = 600;

}

void Zombie::draw() {
    // Draw the zombie as a simple shape
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // colour

    glBegin(GL_QUADS);

    // Use this to adjust the size
    glVertex2f(-20.0f, -20.0f);
    glVertex2f(20.0f, -20.0f);
    glVertex2f(20.0f, 20.0f);
    glVertex2f(-20.0f, 20.0f);
    glEnd();
}
