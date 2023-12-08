#ifndef BOSSZOMBIE_H
#define BOSSZOMBIE_H

#include "Zombie.h"

class BossZombie : public Zombie {
public:
    BossZombie(float x, float y);

    virtual void Update(float playerX, float playerY) override;
    bool WantsToShoot();

private:
    float shootCooldown;
    float shootTimer;
};

#endif
