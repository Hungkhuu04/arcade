#include "lib/Player.h"
#include "lib/Renderer.h"
#include <algorithm>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

Player::Player(float x, float y) 
    : x(x), y(y), width(0.1125f), height(0.2f), speed(0.01f), health(100.0f), shootCooldown(0.3f), shootTimer(0.0f), damageCooldown(0.0f), damageCooldownDuration(0.25f) {
    
    this->spriteWidth = static_cast<float>(width) + 0.005f;
    this->spriteHeight = static_cast<float>(height) + 0.005f;
    
    loadTexture("Zombie/src/assets/zombie.png");
}

void Player::MoveUp()    { y += speed; }
void Player::MoveDown()  { y -= speed; }
void Player::MoveLeft()  { x -= speed; }
void Player::MoveRight() { x += speed; }

void Player::Render() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x - width / 2, y - height / 2);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width / 2, y - height / 2);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width / 2, y + height / 2);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x - width / 2, y + height / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

bool Player::IsAlive() const {
    return health > 0;
}

void Player::TakeDamage(float amount) {
    if (damageCooldown <= 0) {
        health -= amount;
        damageCooldown = damageCooldownDuration; // Reset cooldown
    }
}

void Player::UpdateCooldown(float deltaTime) {
    if (damageCooldown > 0) {
        damageCooldown -= deltaTime;
    }
}

bool Player::IsDamageable() const {
    return damageCooldown <= 0;
}

bool Player::IsDead() const {
    return health <= 0;
}

void Player::loadTexture(const char* filepath) {
    // Flip image vertically
    stbi_set_flip_vertically_on_load(true);

    // Load image data
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture" << std::endl;
        return;
    }

    // Store sprite dimensions
    width = static_cast<float>(width);
    height = static_cast<float>(height);

    // Generate texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture into OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

    // Free image data
    stbi_image_free(data);
}
