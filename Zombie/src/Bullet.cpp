#include "lib/Bullet.h"
#include "lib/Renderer.h"
#include <cmath>

// Constructor
Bullet::Bullet(float startX, float startY, float targetX, float targetY)
    : x(startX), y(startY), speed(0.03f), width(0.02f), height(0.02f), damage(10.0f), markedForDeletion(false) {
    // Calculate direction vector
    float length = std::sqrt((targetX - startX) * (targetX - startX) + (targetY - startY) * (targetY - startY));
    dirX = (targetX - startX) / length;
    dirY = (targetY - startY) / length;
}

void Bullet::Update() {
    // Update position based on speed and direction
    x += dirX * speed;
    y += dirY * speed;

    // Check if the bullet is off-screen
    if (IsOffScreen()) {
        MarkForDeletion();
    }
}

void Bullet::Render() {
    Renderer::RenderBullet(x, y, width, height); // Adjusted to include width and height
}

bool Bullet::IsOffScreen() const {
    return x < -1.0f || x > 1.0f || y < -1.0f || y > 1.0f;
}

