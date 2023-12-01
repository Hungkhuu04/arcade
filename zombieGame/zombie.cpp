// Zombie.cpp
#include "zombie.h"
#include <GL/glut.h>

Zombie::Zombie(float x, float y) : x(x), y(y), speed(2.0f) {
    // Initialize other necessary zombie properties
}

void Zombie::update() {
    // Random movement
    x += (rand() % 3 - 1) * speed;
    y += (rand() % 3 - 1) * speed;

    // Boundary checks
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x > 800)
        x = 800;
    if (y > 600)
        y = 600;
}

void Zombie::draw() {
    // Draw the zombie as a simple shape or textured sprite
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Use this to adjust colour

    glBegin(GL_QUADS);
    glVertex2f(-10.0f, -10.0f); // Use this to adjust the size
    glVertex2f(10.0f, -10.0f);
    glVertex2f(10.0f, 10.0f);
    glVertex2f(-10.0f, 10.0f);
    glEnd();
}
