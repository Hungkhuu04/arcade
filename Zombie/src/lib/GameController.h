#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "BossZombie.h"
#include <vector>
#include <array>

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
    static void CheckBossZombieBulletPlayerCollision();
    static void UpdateZombies();
    static void SpawnZombie();
    static void Shoot(float targetX, float targetY);
    static void IncrementWave();
    static Player* player;
    static bool keyStates[256];
    static std::vector<Bullet> bullets;
    static std::vector<Bullet> bossZombieBullets;
    static std::vector<Zombie> zombies;
    static std::vector<BossZombie> bossZombies;
    static GameState currentState; 
    static int currentWave;
    static float timer;
    static const int waveDuration;
    static float spawnTimer;
    static float spawnRate;
    static int GetWave();
    static float GetTimer();
    static int GetScore();
    static int score;
    static void ShootFromBossZombie(const BossZombie& bossZombie);
    static void SpawnBossZombie();
    static const int LEADERBOARD_SIZE = 5;
    static std::array<int, LEADERBOARD_SIZE> leaderboard;
    static void UpdateLeaderboard();
    static void SaveLeaderboard();
    static void LoadLeaderboard();
private:
    
};

#endif // GAMECONTROLLER_H
