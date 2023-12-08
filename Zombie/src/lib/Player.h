#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include "Bullet.h"
#include "stb_image.h"
#include <GL/freeglut.h>

class Player {
public:
    Player(float x, float y);
    //Movement
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    //Shooting
    void Shoot(float targetX, float targetY);

    //Rendering
    void Update();
    void Render();
    void loadTexture(const char* filepath); 

    //Getters
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetHealth() const { return health; }
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetShootTimer() const { return shootTimer; }
    float GetShootCooldown() const { return shootCooldown; }
    
    //Setters
    void SetX(float newX) { x = newX; }
    void SetY(float newY) { y = newY; }
    void SetShootTimer(float newTimer) { shootTimer = newTimer; }
    void UpdateCooldown(float deltaTime);

    //Damage
    void TakeDamage(float amount);
    bool IsAlive() const;
    bool IsDead() const;
    bool IsDamageable() const;


private:
    float x, y;
    float speed;
    float health;
    float width, height;
    float shootCooldown;
    float shootTimer;
    float damageCooldown;
    float damageCooldownDuration;
    GLuint textureID;
    float spriteWidth, spriteHeight;
};



#endif

