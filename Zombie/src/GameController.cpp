#include "lib/GameController.h"
#include "lib/Utility.h"
#include "lib/Bullet.h"
#include "lib/Zombie.h"
#include "lib/Player.h"
#include <cstring> // For memset
#include <algorithm> // For std::remove_if
#include <random>
#include <cmath>
#include <iostream>
#include <cstdlib>

// Static member initializations
GameController::GameState GameController::currentState = GameController::GameState::START;
Player* GameController::player = nullptr;
bool GameController::keyStates[256];
std::vector<Bullet> GameController::bullets;
std::vector<Zombie> GameController::zombies;

void GameController::Initialize() {
    currentState = GameState::START;
    bullets.clear();
    zombies.clear();
    player = new Player(0.0f, 0.0f); // Initialize player at the center
    memset(keyStates, false, sizeof(keyStates)); // Initialize all key states to false
}

void GameController::KeyboardHandler(unsigned char key, int x, int y) {
    if (currentState == GameState::START) {
        if (key == 's') {
            Initialize(); // Initialize the game
            currentState = GameState::PLAYING;
        }
    } else if (currentState == GameState::PLAYING) {
        // Handle keyboard inputs for gameplay
        keyStates[key] = true;
        // ... (rest of your existing keyboard handling code for gameplay)
    } else if (currentState == GameState::GAME_OVER) {
        if (key == 'r') {
            // Restart the game when 'r' key is pressed
            Initialize(); // Re-initialize the game
            currentState = GameState::PLAYING;
        }
        if (key == 'x') {
            // Exit the game when 'x' key is pressed
            exit(0);
        }
        if (key == 's') {
            // Change to PLAYING state when 's' key is pressed
            currentState = GameState::START;
        }
    }
}

void GameController::KeyboardUpHandler(unsigned char key, int x, int y) {
    if (currentState == GameState::PLAYING) {
        keyStates[key] = false;
    }
}
void GameController::UpdatePlayer() {
    if (currentState == GameState::PLAYING) {
    if (keyStates['w'] || keyStates['W']) player->MoveUp();
    if (keyStates['s'] || keyStates['S']) player->MoveDown();
    if (keyStates['a'] || keyStates['A']) player->MoveLeft();
    if (keyStates['d'] || keyStates['D']) player->MoveRight();
    player->UpdateCooldown(1.0f / 60.0f); // Update cooldown timer
    }
}

void GameController::Shoot(float targetX, float targetY) {
    if (currentState == GameState::PLAYING) {
    if (player->GetShootTimer() >= player->GetShootCooldown()) {
        bullets.push_back(Bullet(player->GetX(), player->GetY(), targetX, targetY));
        player->SetShootTimer(0.0f);  // Reset timer after shooting
    }
    }
}


void GameController::UpdateBullets() {
    if (currentState == GameState::PLAYING) {
    float currentTimer = player->GetShootTimer();
    currentTimer += 1.0f / 60.0f; // Increment timer by 1/60th of a second
    player->SetShootTimer(currentTimer);
    // Update all bullets
    for (auto &bullet : bullets) {
        bullet.Update();
    }

    // Remove bullets that are off-screen
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.IsOffScreen(); }), bullets.end());
    }
}




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

    // Remove dead zombies
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(), 
                 [](const Zombie& z) { return z.IsDead(); }),
                 zombies.end());

    // Additionally, remove bullets that have been marked for deletion
    }
}

void GameController::HandlePlayerZombieCollision() {
    if (currentState == GameState::PLAYING) {
    float playerWidth = player->GetWidth();
    float playerHeight = player->GetHeight();

    for (auto& zombie : zombies) {
        float zombieWidth = zombie.GetWidth();
        float zombieHeight = zombie.GetHeight();

        // Check for collision
        if (Utility::CheckCollision(player->GetX(), player->GetY(), playerWidth, playerHeight,
                                    zombie.GetX(), zombie.GetY(), zombieWidth, zombieHeight)) {
            // Collision detected - if the player is damageable, take damage
            if (player->IsDamageable()) {
                player->TakeDamage(zombie.GetDamage());

                // Check if player is dead and handle it
                if (player->IsDead()) {
                    delete player;
                    currentState = GameState::GAME_OVER;
                    return; // Exit the function early as there's no need to check other zombies
                }
            }

            // Adjust position to prevent overlap (non-overlapping logic)
            // Calculate direction to move
            float dx = player->GetX() - zombie.GetX();
            float dy = player->GetY() - zombie.GetY();
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance != 0) {
                float overlap = (playerWidth / 2 + zombieWidth / 2) - distance;
                player->SetX(player->GetX() + (dx / distance) * overlap);
                player->SetY(player->GetY() + (dy / distance) * overlap);
            }
        }
    }
    }
}


void GameController::UpdateZombies() {
    if (currentState == GameState::PLAYING) {
    float deltaTime = 1.0f / 60.0f; // Assuming 60 FPS

    // Update zombies
    for (auto& zombie : zombies) {
        zombie.Update(player->GetX(), player->GetY());
        zombie.UpdateCooldown(deltaTime); // Update cooldown timer
    }

    // Check for zombie-zombie collisions
    for (size_t i = 0; i < zombies.size(); ++i) {
        for (size_t j = i + 1; j < zombies.size(); ++j) {
            auto& zombie1 = zombies[i];
            auto& zombie2 = zombies[j];

            float zombie1Width = zombie1.GetWidth();
            float zombie1Height = zombie1.GetHeight();
            float zombie2Width = zombie2.GetWidth();
            float zombie2Height = zombie2.GetHeight();

            // Check for collision between zombies
            if (Utility::CheckCollision(zombie1.GetX(), zombie1.GetY(), zombie1Width, zombie1Height,
                                        zombie2.GetX(), zombie2.GetY(), zombie2Width, zombie2Height)) {
                // Calculate direction to move each zombie to avoid overlap
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
    // Example spawning logic
    static float spawnTimer = 0.0f;
    spawnTimer += 1.0f / 60.0f; // Increment timer each frame (assuming 60 FPS)

    // Spawn a new zombie every 5 seconds
    if (spawnTimer >= 0.5f) {
        SpawnZombie();
        spawnTimer = 0.0f; // Reset timer
    }

    // Remove dead zombies
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(), 
                 [](const Zombie& z) { return z.IsDead(); }),
                 zombies.end());
    }
}


void GameController::SpawnZombie() {
    if (currentState == GameState::PLAYING) {
        // Static random device and generator for random number generation
        static std::random_device rd;
        static std::mt19937 gen(rd());
        // Uniform distribution for random positions
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        float minDistance = 1.0f;
        float x, y;

        do {
            x = player->GetX() + dis(gen); // Random position around the player's X
            y = player->GetY() + dis(gen); // Random position around the player's Y
        } while (std::sqrt(std::pow(x - player->GetX(), 2) + std::pow(y - player->GetY(), 2)) < minDistance);

        // Add the new zombie at the calculated position
        zombies.push_back(Zombie(x, y));
    }
}



