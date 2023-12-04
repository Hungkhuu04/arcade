#include "lib/BossZombie.h"

BossZombie::BossZombie(float x, float y)
    : Zombie(x, y), specialAttackCooldown(5.0f), specialAttackTimer(0.0f) {
    // Initialize unique attributes for BossZombie
}

void BossZombie::Update(float playerX, float playerY) {
    Zombie::Update(playerX, playerY); // Call base class update

    // Update special attack timer and trigger attack
    specialAttackTimer += 1.0f / 60.0f; // Assuming 60 FPS
    if (specialAttackTimer >= specialAttackCooldown) {
        SpecialAttack();
        specialAttackTimer = 0.0f;
    }

    // Implement other unique boss behaviors
}

void BossZombie::SpecialAttack() {
    // Implement the special attack pattern here
}
