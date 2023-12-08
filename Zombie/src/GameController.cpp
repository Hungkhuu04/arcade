#include "lib/GameController.h"
#include "lib/Utility.h"
#include "lib/Bullet.h"
#include "lib/Zombie.h"
#include "lib/Player.h"
#include "lib/BossZombie.h"
#include <cstring>
#include <algorithm>
#include <random>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <array>
#include <fstream>


//Global Variable Declarations
GameController::GameState GameController::currentState = GameController::GameState::START;
Player* GameController::player = nullptr;
bool GameController::keyStates[256];
std::vector<Bullet> GameController::bullets;
std::vector<Bullet> GameController::bossZombieBullets;
std::vector<Zombie> GameController::zombies;
std::vector<BossZombie> GameController::bossZombies;
int GameController::currentWave = 1;
float GameController::timer = 0.0f;
const int GameController::waveDuration = 10;
float GameController::spawnTimer = 0.0f;
float GameController::spawnRate = 2.0f;
int GameController::score = 0;
std::array<int, GameController::LEADERBOARD_SIZE> GameController::leaderboard = {};

//Initializes game elements at the start or restart of the game
void GameController::Initialize() {
    currentState = GameState::START;
    bullets.clear();
    bossZombieBullets.clear();
    zombies.clear();
    bossZombies.clear();
    timer = 0.0f;
    spawnTimer = 0.0f;
    currentWave = 1;
    player = new Player(0.0f, 0.0f);
    memset(keyStates, false, sizeof(keyStates));
    LoadLeaderboard();
}

//Handles keyboard input for gameplay
void GameController::KeyboardHandler(unsigned char key, int x, int y) {
    if (currentState == GameState::START) {
        if (key == 's') {
            Initialize();
            currentState = GameState::PLAYING;
        }
    } else if (currentState == GameState::PLAYING) {
        keyStates[key] = true;
    } else if (currentState == GameState::GAME_OVER) {
        if (key == 'r') {
            Initialize();
            currentState = GameState::PLAYING;
        }
        if (key == 'x') {
            exit(0);
        }
        if (key == 's') {
            currentState = GameState::START;
        }
    }
}

//Handles keyboard key release
void GameController::KeyboardUpHandler(unsigned char key, int x, int y) {
    if (currentState == GameState::PLAYING) {
        keyStates[key] = false;
    }
}

//Updates player's position and state
void GameController::UpdatePlayer() {
    if (currentState == GameState::PLAYING) {
    if (keyStates['w'] || keyStates['W']) player->MoveUp();
    if (keyStates['s'] || keyStates['S']) player->MoveDown();
    if (keyStates['a'] || keyStates['A']) player->MoveLeft();
    if (keyStates['d'] || keyStates['D']) player->MoveRight();
    player->UpdateCooldown(1.0f / 60.0f);
    }
}
//Handles shooting mechanics
void GameController::Shoot(float targetX, float targetY) {
    if (currentState == GameState::PLAYING) {
    if (player->GetShootTimer() >= player->GetShootCooldown()) {
        bullets.push_back(Bullet(player->GetX(), player->GetY(), targetX, targetY, Bullet::BulletType::Player));
        player->SetShootTimer(0.0f);
    }
    }
}

//Updates bullets' positions and states
void GameController::UpdateBullets() {
    if (currentState == GameState::PLAYING) {
    float currentTimer = player->GetShootTimer();
    currentTimer += 1.0f / 60.0f;
    player->SetShootTimer(currentTimer);
    for (auto &bullet : bullets) {
        bullet.Update();
    }
    for (auto &bullet : bossZombieBullets) {
        bullet.Update();
    }

    bossZombieBullets.erase(std::remove_if(bossZombieBullets.begin(), bossZombieBullets.end(), [](const Bullet& b) { return b.IsOffScreen(); }), bossZombieBullets.end());
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.IsOffScreen(); }), bullets.end());
    }
}



//Checks and handles collisions between bullets and zombies
void GameController::CheckBulletZombieCollisions() {
    if (currentState == GameState::PLAYING) {
    for (auto& bullet : bullets) {
        for (auto& zombie : zombies) {
            if (zombie.IsDamageable() && Utility::CheckCollision(bullet.GetX(), bullet.GetY(), bullet.GetWidth(), bullet.GetHeight(),
                                        zombie.GetX(), zombie.GetY(), zombie.GetWidth(), zombie.GetHeight())) {
                zombie.TakeDamage(bullet.GetDamage());
            }
        }
    }
    for (auto& bullet : bullets) {
            for (auto& bossZombie : bossZombies) {
                if (bossZombie.IsDamageable() && Utility::CheckCollision(bullet.GetX(), bullet.GetY(), bullet.GetWidth(), bullet.GetHeight(),
                                            bossZombie.GetX(), bossZombie.GetY(), bossZombie.GetWidth(), bossZombie.GetHeight())) {
                    bossZombie.TakeDamage(bullet.GetDamage());
                }
            }
        }
    }
    

    for (const auto& zombie : zombies) {
        if (zombie.IsDead()) {
            score += 50;
        }
    }
    for (const auto& bossZombie : bossZombies) {
        if (bossZombie.IsDead()) {
            score += 100;
        }
    }
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(), 
                 [](const Zombie& z) { return z.IsDead(); }),
                 zombies.end());
    bossZombies.erase(std::remove_if(bossZombies.begin(), bossZombies.end(), 
                     [](const BossZombie& bz) { return bz.IsDead(); }),
                     bossZombies.end());
    }

//Checks and handles collisions between boss zombie bullets and the player
void GameController::CheckBossZombieBulletPlayerCollision() {
    if (currentState == GameState::PLAYING) {
    for (auto& bullet : bossZombieBullets) {
        if (Utility::CheckCollision(bullet.GetX(), bullet.GetY(), bullet.GetWidth(), bullet.GetHeight(),
                                    player->GetX(), player->GetY(), player->GetWidth(), player->GetHeight())) {
            player->TakeDamage(bullet.GetDamage());
            bullet.MarkForDeletion();

            // Check if the player is dead
            if (player->IsDead()) {
                score += currentWave * 10;
                UpdateLeaderboard();
                SaveLeaderboard(); 
                delete player;
                currentState = GameState::GAME_OVER;
                return;
            }
        }
    }

    bossZombieBullets.erase(std::remove_if(bossZombieBullets.begin(), bossZombieBullets.end(), 
                                           [](const Bullet& b) { return b.ShouldBeRemoved(); }), 
                                           bossZombieBullets.end());
}
}

//Handles player collisions with zombies
void GameController::HandlePlayerZombieCollision() {
    if (currentState == GameState::PLAYING) {
    float playerWidth = player->GetWidth();
    float playerHeight = player->GetHeight();

    for (auto& zombie : zombies) {
        float zombieWidth = zombie.GetWidth();
        float zombieHeight = zombie.GetHeight();

        if (Utility::CheckCollision(player->GetX(), player->GetY(), playerWidth, playerHeight,
                                    zombie.GetX(), zombie.GetY(), zombieWidth, zombieHeight)) {
            if (player->IsDamageable()) {
                player->TakeDamage(zombie.GetDamage());

                    if (player->IsDead()) {
                        score += currentWave * 10;
                        UpdateLeaderboard();
                        SaveLeaderboard();  // Save leaderboard when player dies
                        delete player;
                        currentState = GameState::GAME_OVER;
                        return;
                    }
            }
        }
    }
    }
}

//Updates zombie states and positions
void GameController::UpdateZombies() {
    if (currentState == GameState::PLAYING) {
    float deltaTime = 1.0f / 60.0f;
    timer += 1.0f / 60.0f;

    if (static_cast<int>(timer) % waveDuration == 0 && timer - (1.0f / 60.0f) < static_cast<int>(timer)) {
        IncrementWave();
    }

    for (auto& zombie : zombies) {
        zombie.Update(player->GetX(), player->GetY());
        zombie.UpdateCooldown(deltaTime); 
    }

    for (auto& bossZombie : bossZombies) {
        bossZombie.Update(player->GetX(), player->GetY());
        bossZombie.UpdateCooldown(deltaTime); 
        if (bossZombie.WantsToShoot()) {
            ShootFromBossZombie(bossZombie);
        }
    }

    //Checks Collisions for zombies.
    for (size_t i = 0; i < zombies.size(); ++i) {
        for (size_t j = i + 1; j < zombies.size(); ++j) {
            auto& zombie1 = zombies[i];
            auto& zombie2 = zombies[j];

            float zombie1Width = zombie1.GetWidth();
            float zombie1Height = zombie1.GetHeight();
            float zombie2Width = zombie2.GetWidth();
            float zombie2Height = zombie2.GetHeight();

            if (Utility::CheckCollision(zombie1.GetX(), zombie1.GetY(), zombie1Width, zombie1Height,
                                        zombie2.GetX(), zombie2.GetY(), zombie2Width, zombie2Height)) {
                float dx = zombie1.GetX() - zombie2.GetX();
                float dy = zombie1.GetY() - zombie2.GetY();
                float distance = std::sqrt(dx * dx + dy * dy);

                if (distance != 0) {
                    float overlap = (zombie1Width / 2 + zombie2Width / 2) - distance;
                    zombie1.SetX(zombie1.GetX() + (dx / distance) * overlap / 2);
                    zombie1.SetY(zombie1.GetY() + (dy / distance) * overlap / 2);
                    zombie2.SetX(zombie2.GetX() - (dx / distance) * overlap / 2);
                    zombie2.SetY(zombie2.GetY() - (dy / distance) * overlap / 2);
                }
            }
        }
    }

    //Checks Collisions for bossZombies.
       for (size_t i = 0; i < bossZombies.size(); ++i) {
        for (size_t j = i + 1; j < bossZombies.size(); ++j) {
            auto& bossZombie1 = bossZombies[i];
            auto& bossZombie2 = bossZombies[j];

            float bossZombie1Width = bossZombie1.GetWidth();
            float bossZombie1Height = bossZombie1.GetHeight();
            float bossZombie2Width = bossZombie2.GetWidth();
            float bossZombie2Height = bossZombie2.GetHeight();

            if (Utility::CheckCollision(bossZombie1.GetX(), bossZombie1.GetY(), bossZombie1Width, bossZombie1Height,
                                        bossZombie2.GetX(), bossZombie2.GetY(), bossZombie2Width, bossZombie2Height)) {
                float dx = bossZombie1.GetX() - bossZombie2.GetX();
                float dy = bossZombie1.GetY() - bossZombie2.GetY();
                float distance = std::sqrt(dx * dx + dy * dy);

                if (distance != 0) {
                    float overlap = (bossZombie1Width / 2 + bossZombie2Width / 2) - distance;
                    bossZombie1.SetX(bossZombie1.GetX() + (dx / distance) * overlap / 2);
                    bossZombie1.SetY(bossZombie1.GetY() + (dy / distance) * overlap / 2);
                    bossZombie2.SetX(bossZombie2.GetX() - (dx / distance) * overlap / 2);
                    bossZombie2.SetY(bossZombie2.GetY() - (dy / distance) * overlap / 2);
                }
            }
        }
    }
    spawnTimer += 1.0f / 60.0f;
    if (spawnTimer >= spawnRate) {
        SpawnZombie();
        spawnTimer = 0.0f;
    }

    zombies.erase(std::remove_if(zombies.begin(), zombies.end(), 
                 [](const Zombie& z) { return z.IsDead(); }),
                 zombies.end());
    }
    bossZombies.erase(std::remove_if(bossZombies.begin(), bossZombies.end(), 
                    [](const BossZombie& bz) { return bz.IsDead(); }),
                    bossZombies.end());
}
//Handles the shoot from the boss zombie.
void GameController::ShootFromBossZombie(const BossZombie& bossZombie) {
    float targetX = player->GetX();
    float targetY = player->GetY();
    bossZombieBullets.push_back(Bullet(bossZombie.GetX(), bossZombie.GetY(), targetX, targetY, Bullet::BulletType::BossZombie));
}
//Spawns a zombie.
void GameController::SpawnZombie() {
    if (currentState == GameState::PLAYING) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        float minDistance = 1.0f;
        float x, y;

        do {
            x = player->GetX() + dis(gen);
            y = player->GetY() + dis(gen);
        } while (std::sqrt(std::pow(x - player->GetX(), 2) + std::pow(y - player->GetY(), 2)) < minDistance);

        zombies.push_back(Zombie(x, y));
    }
}
//Spawns a boss zombie. 
void GameController::SpawnBossZombie() {
    if (currentState == GameState::PLAYING) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        float minDistance = 1.0f;
        float x, y;

        do {
            x = player->GetX() + dis(gen);
            y = player->GetY() + dis(gen);
        } while (std::sqrt(std::pow(x - player->GetX(), 2) + std::pow(y - player->GetY(), 2)) < minDistance);

        bossZombies.push_back(BossZombie(x, y));
    }
}

//Increment the wave and update game difficulty
void GameController::IncrementWave() {
    currentWave++;
    for (auto& zombie : zombies) {
        zombie.SetSpeed(zombie.GetSpeed() * 1.1f);
        zombie.SetDamage(zombie.GetDamage() * 1.1f);
        zombie.SetHealth(zombie.GetHealth() * 1.1f);
    }

    SpawnBossZombie();
    for (auto& bossZombie : bossZombies) {
        bossZombie.SetSpeed(bossZombie.GetSpeed() * 1.1f);
        bossZombie.SetDamage(bossZombie.GetDamage() * 1.1f);
        for (auto& bullet : bossZombieBullets) {
            bullet.setDamage(bullet.GetDamage() * 1.1f);
        }
        bossZombie.SetHealth(bossZombie.GetHealth() * 1.1f);
    }

    spawnRate *= 0.8f;

    // Ensure that spawnRate does not become too low
    if (spawnRate < 0.1) {
        spawnRate = 0.1;
    }
}

//Gets the currentWave.
int GameController::GetWave() {
    return currentWave;
}

//Gets the timer.
float GameController::GetTimer() {
    return timer;
}

//Gets the score.
int GameController::GetScore() {
    return score;
}

// Update the leaderboard with the current score
void GameController::UpdateLeaderboard() {
    int position = -1;
    for (int i = 0; i < LEADERBOARD_SIZE; ++i) {
        if (score > leaderboard[i]) {
            position = i;
            break;
        }
    }

    if (position != -1) {
        for (int i = LEADERBOARD_SIZE - 1; i > position; --i) {
            leaderboard[i] = leaderboard[i - 1];
        }
        leaderboard[position] = score;
    }
}

//Saves the leaderboard scores in a file. 
void GameController::SaveLeaderboard() {
    std::ofstream file("Zombie/src/data/leaderboard.txt");
    if (file.is_open()) {
        for (const auto& score : leaderboard) {
            file << score << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open leaderboard file for writing." << std::endl;
    }
}

//Loads the leaderboard scores from a a file. 
void GameController::LoadLeaderboard() {
    std::ifstream file("Zombie/src/data/leaderboard.txt");
    int score;
    int index = 0;
    if (file.is_open()) {
        while (file >> score && index < LEADERBOARD_SIZE) {
            leaderboard[index++] = score;
        }
        file.close();
    } else {
        std::cerr << "Unable to open leaderboard file for reading." << std::endl;
    }
}

