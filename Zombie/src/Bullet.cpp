#include "lib/Bullet.h"
#include "lib/Renderer.h"
#include <cmath>

// Constructor
// Constructor
Bullet::Bullet(float startX, float startY, float targetX, float targetY, BulletType bulletType)
    : x(startX), y(startY), type(bulletType), speed(0.03f), width(0.02f), height(0.02f), markedForDeletion(false) {
    switch (bulletType) {
        case BulletType::Player:
            damage = 15.0f; // Example damage value for player bullet
            break;
        case BulletType::BossZombie:
            damage = 10.0f; // Example damage value for boss zombie bullet
            speed = 0.015f;
            width = 0.04f;
            height = 0.04f;
            break;
        default:
            damage = 1.0f; // Default damage
            break;
    }

    float length = std::sqrt((targetX - startX) * (targetX - startX) + (targetY - startY) * (targetY - startY));
    dirX = (targetX - startX) / length;
    dirY = (targetY - startY) / length;
}


//Updates the Bullets by changing direction and sped and if goes off screen, it gets deleted. 
void Bullet::Update() {
    x += dirX * speed;
    y += dirY * speed;

    
    if (IsOffScreen()) {
        MarkForDeletion();
    }
}

void Bullet::Render() {
    Renderer::RenderBullet(x, y, width, height, type);
}

bool Bullet::IsOffScreen() const {
    return x < -1.0f || x > 1.0f || y < -1.0f || y > 1.0f;
}

