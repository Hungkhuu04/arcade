#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include <vector>

class GameController {
public:
    enum class GameState {
        START,
        PLAYING,
        GAME_OVER
    };
    static void Initialize();
    static void KeyboardHandler(unsigned char key, int x, int y);
    static void KeyboardUpHandler(unsigned char key, int x, int y);
    static void UpdatePlayer();
    static void UpdateBullets();
    static void CheckBulletZombieCollisions();
    static void HandlePlayerZombieCollision();
    static void UpdateZombies();
    static void SpawnZombie();
    static void Shoot(float targetX, float targetY);
    static Player* player;
    static bool keyStates[256];
    static std::vector<Bullet> bullets;
    static std::vector<Zombie> zombies;
    static GameState currentState; 

private:
    // Private members (if any)
};

#endif // GAMECONTROLLER_H
