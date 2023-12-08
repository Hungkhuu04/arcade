#include "lib/Zombie.h"
#include "lib/Renderer.h"
#include <cmath>
#include "lib/stb_image.h"
#include <iostream>

#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <string>

// Constructor - Initialize member variables
Zombie::Zombie(float x, float y) 
    : x(x), y(y), 
      speed(0.005f), 
      health(20.0f), 
      width(0.1125f), 
      height(0.3f), 
      damage(5.0f),
      damageCooldown(0.0f),
      damageCooldownDuration(0.5f)
{
    this->spriteWidth = static_cast<float>(width) * 1.05f;
    this->spriteHeight = static_cast<float>(height) * 1.05f;
    
    loadTexture("Zombie/src/assets/zombie.png");
}

// Update zombie position based on player's position
void Zombie::Update(float playerX, float playerY) {
    float dx = playerX - x;
    float dy = playerY - y;
    float length = std::sqrt(dx * dx + dy * dy);

    if(length != 0) {
        x += speed * (dx / length);
        y += speed * (dy / length);
    }
    
}

// Render the zombie on the screen
void Zombie::Render() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x - spriteWidth / 2, y - spriteHeight / 2);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + spriteWidth / 2, y - spriteHeight / 2);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + spriteWidth / 2, y + spriteHeight / 2);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x - spriteWidth / 2, y + spriteHeight / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Check if the zombie is alive based on its health
bool Zombie::IsAlive() const {
    return health > 0;
}

// Inflict damage on the zombie, buffer for piercing bullets
void Zombie::TakeDamage(float amount) {
    if (damageCooldown <= 0) {
        health -= amount;
        damageCooldown = damageCooldownDuration;
    }
}

// Update the damage cooldown timer
void Zombie::UpdateCooldown(float deltaTime) {
    if (damageCooldown > 0) {
        damageCooldown -= deltaTime;
    }
}

// Check if the zombie can currently take damage, for piercing bullets 
bool Zombie::IsDamageable() const {
    return damageCooldown <= 0;
}

// Check if the zombie is dead based on its health
bool Zombie::IsDead() const {
    return health <= 0;
}

// Set the zombie's movement speed
void Zombie::SetSpeed(float newSpeed) {
    speed = newSpeed;
}

// Set the damage inflicted by the zombie
void Zombie::SetDamage(float newDamage) {
    damage = newDamage;
}

// Set the zombie's health
void Zombie::SetHealth(float newHealth) {
    health = newHealth;
}
// Textture Package
void Zombie::loadTexture(const char* filepath) {
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture" << std::endl;
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGB;
    if (nrChannels == 4) {
        format = GL_RGBA;
    } else if (nrChannels == 3) {
        format = GL_RGB;
    } else if (nrChannels == 1) {
        format = GL_RED;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}
