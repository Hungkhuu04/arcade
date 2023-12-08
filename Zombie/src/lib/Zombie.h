#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "stb_image.h"
#include <GL/freeglut.h>


class Zombie {
public:
    Zombie(float x, float y);
    virtual void Update(float playerX, float playerY);
    void Render();
    bool IsAlive() const;
    float GetX() const { return x; }
    float GetY() const { return y; }

    void SetX(float newX) { x = newX; }
    void SetY(float newY) { y = newY; }
    void SetWidth(float newWidth) { width = newWidth; }
    void SetHeight(float newHeight) { height = newHeight; }
    void SetSpriteWidth(float newSpriteWidth) { spriteWidth = newSpriteWidth; }
    void SetSpriteHeight(float newSpriteHeight) { spriteHeight = newSpriteHeight; }
    void TakeDamage(float amount);
    bool IsDead() const;
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetDamage() const { return damage; }
    void UpdateCooldown(float deltaTime);
    bool IsDamageable() const;
    void loadTexture(const char* filepath);

    void SetSpeed(float newSpeed);
    float GetSpeed() const {return speed;}
    void SetDamage(float newDamage);
    void SetHealth(float newHealth);
    float GetHealth() const {return health;}


   

    

private:
    float x, y;
    float speed;
    float health;
    float width, height;
    float damage;
    float damageCooldown;
    float damageCooldownDuration;
    float spriteWidth;
    float spriteHeight;
    GLuint textureID;
};

#endif // ZOMBIE_H
