#ifndef BOSSZOMBIE_H
#define BOSSZOMBIE_H

#include "Zombie.h"

class BossZombie : public Zombie {
public:
    BossZombie(float x, float y);

    void Update(float playerX, float playerY) override;  // Override to implement unique behavior
    void SpecialAttack();  // Unique attack pattern for the boss

private:
    float specialAttackCooldown;
    float specialAttackTimer;
    // Other unique attributes for the boss zombie
};

#endif // BOSSZOMBIE_H
