#include "lib/BossZombie.h"
#include <cmath>
#include <iostream>

/*This is constructor that intializes specified attributes for the sprite called BossZombie*/
BossZombie::BossZombie(float x, float y) : Zombie(x, y), shootCooldown(1.0f), shootTimer(0.0f) {
    SetHealth(120.0f);
    SetSpeed(0.01f);
    SetWidth(0.1125f * 1.2f);
    SetHeight(0.3f * 1.2f);
    SetSpriteWidth(GetWidth() * 1.05f);
    SetSpriteHeight(GetHeight() * 1.05f);
    
    loadTexture("Zombie/src/assets/BossZombie.png");
}

/*This function updates the BossZombie by updating the same way every sprite class zombie does as well as it's own specifice
actions which is shooting*/
void BossZombie::Update(float playerX, float playerY) {
    Zombie::Update(playerX, playerY);

    if (shootTimer > 0) {
        shootTimer -= 1.0f / 60.0f;
    }
}

/*This function checks whether or not the BossZombie is ready to shoot based on the shootTimer */
bool BossZombie::WantsToShoot() {
    if (shootTimer <= 0) {
        shootTimer = shootCooldown;
        return true;
    }
    return false;
}