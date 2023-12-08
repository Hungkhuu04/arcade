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

    //Core Game Loop
    static void Initialize();
    static void IncrementWave();
    static GameState currentState; 
    static int currentWave;
    static float timer;
    static const int waveDuration;
    static float spawnTimer;
    static float spawnRate;
    static int score;
    
    //KeyboardHandling
    static void KeyboardHandler(unsigned char key, int x, int y);
    static void KeyboardUpHandler(unsigned char key, int x, int y);
    static bool keyStates[256];

    //Update
    static void UpdatePlayer();
    static void UpdateBullets();
    static void UpdateZombies();

    //Combat
    static void CheckBulletZombieCollisions();
    static void HandlePlayerZombieCollision();
    static void CheckBossZombieBulletPlayerCollision();
    static void Shoot(float targetX, float targetY);
    static void ShootFromBossZombie(const BossZombie& bossZombie);

    //Zombies and BossZombies
    static void SpawnZombie();
    static std::vector<Zombie> zombies;
    static std::vector<BossZombie> bossZombies;
    static std::vector<Bullet> bossZombieBullets;
    static void SpawnBossZombie();

    //Player
    static Player* player;
    static std::vector<Bullet> bullets;

    //Getters
    static int GetWave();
    static float GetTimer();
    static int GetScore();

    //LeaderBoard
    static const int LEADERBOARD_SIZE = 5;
    static std::array<int, LEADERBOARD_SIZE> leaderboard;
    static void UpdateLeaderboard();
    static void SaveLeaderboard();
    static void LoadLeaderboard();
private:
    
};

#endif // GAMECONTROLLER_H
