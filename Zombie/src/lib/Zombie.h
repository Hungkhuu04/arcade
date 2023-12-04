#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie {
public:
    Zombie(float x, float y);
    virtual void Update(float playerX, float playerY);  // Update the zombie's state
    void Render();  // Render the zombie
    bool IsAlive() const;  // Check if the zombie is still alive
    float GetX() const { return x; }
    float GetY() const { return y; }
    void SetX(float newX) { x = newX; }
    void SetY(float newY) { y = newY; }
    void TakeDamage(float amount);
    bool IsDead() const;
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetDamage() const { return damage; }
    void UpdateCooldown(float deltaTime);
    bool IsDamageable() const;
    

private:
    float x, y;     // Position
    float speed;    // Movement speed
    float health;   // Zombie health
    float width, height; // Dimensions of the zombie
    float damage;   // Damage the zombie does
    float damageCooldown;
    float damageCooldownDuration;
};

#endif // ZOMBIE_H
