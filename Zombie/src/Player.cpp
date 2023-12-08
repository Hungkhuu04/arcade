#include "lib/Player.h"
#include "lib/Renderer.h"
#include <algorithm>
#include <iostream>
#include "lib/stb_image.h"

// Constructor for the Player class, initializes player attributes and loads texture
Player::Player(float x, float y) 
    : x(x), y(y), width(0.1125f), height(0.2f), speed(0.01f), health(100.0f), shootCooldown(0.3f), shootTimer(0.0f), damageCooldown(0.0f), damageCooldownDuration(0.25f) {
    
    this->spriteWidth = static_cast<float>(width) * 1.05f;
    this->spriteHeight = static_cast<float>(height) * 1.05f;
    
    loadTexture("Zombie/src/assets/player.png");

    
}

// Move the player upward
void Player::MoveUp() {
    float newY = y + speed;
    if (newY + spriteHeight / 2 <= 1.0) {
        y = newY;
    }
}

// Move the player downward
void Player::MoveDown() {
    float newY = y - speed;
    if (newY - spriteHeight / 2 >= -1.0) {
        y = newY;
    }
}

// Move the player to the left
void Player::MoveLeft() {
    float newX = x - speed;
    if (newX - spriteWidth / 2 >= -1.0) {
        x = newX;
    }
}

// Move the player to the right
void Player::MoveRight() {
    float newX = x + speed;
    if (newX + spriteWidth / 2 <= 1.0) {
        x = newX;
    }
}

// Render the player on the screen
void Player::Render() {
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

// Check if the player is alive
bool Player::IsAlive() const {
    return health > 0;
}

// Inflict damage to the player
void Player::TakeDamage(float amount) {
    if (damageCooldown <= 0) {
        health -= amount;
        damageCooldown = damageCooldownDuration;
    }
}

// Update damage cooldown based on deltaTime
void Player::UpdateCooldown(float deltaTime) {
    if (damageCooldown > 0) {
        damageCooldown -= deltaTime;
    }
}

// Check if the player can take damage
bool Player::IsDamageable() const {
    return damageCooldown <= 0;
}

// Check if the player is dead
bool Player::IsDead() const {
    return health <= 0;
}

// Load a texture for the player from a file
void Player::loadTexture(const char* filepath) {
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
