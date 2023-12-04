#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include "Bullet.h"
#include "stb_image.h"
#include <GL/freeglut.h>

class Player {
public:
    Player(float x, float y);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Shoot(float targetX, float targetY);  // Method for shooting bullets
    void Update();  // Update player state
    void Render();  // Render the player
    float GetX() const { return x; }
    float GetY() const { return y; }
    void SetX(float newX) { x = newX; }
    void SetY(float newY) { y = newY; }
    void TakeDamage(float amount);
    bool IsAlive() const;
    bool IsDead() const;
    void UpdateCooldown(float deltaTime);
    bool IsDamageable() const;
    float GetHealth() const { return health; }
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetShootTimer() const { return shootTimer; }
    float GetShootCooldown() const { return shootCooldown; }
    void SetShootTimer(float newTimer) { shootTimer = newTimer; }
    void loadTexture(const char* filepath);
    void Reset();

private:
    float x, y;     // Position
    float speed;    // Movement speed
    float health;   // Player health
    float shootCooldown;    // Cooldown period between shots
    float shootTimer;       // Timer to track time since last shot
    float width, height;    // Dimensions of the player
    GLuint textureID;       // Texture ID
    float spriteWidth, spriteHeight;    // Dimensions of the sprite
    float damageCooldown;
    float damageCooldownDuration;
};



#endif // PLAYER_H

