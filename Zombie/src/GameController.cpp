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


// Static member initializations
Player* GameController::player = nullptr;
bool GameController::keyStates[256];
std::vector<Bullet> GameController::bullets;
std::vector<Zombie> GameController::zombies;


void GameController::Initialize() {
    player = new Player(0.0f, 0.0f); // Initialize player at the center
    memset(keyStates, false, sizeof(keyStates)); // Initialize all key states to false
}

void GameController::KeyboardHandler(unsigned char key, int x, int y) {
    keyStates[key] = true; // Set the state of the key to pressed
}

void GameController::KeyboardUpHandler(unsigned char key, int x, int y) {
    keyStates[key] = false; // Set the state of the key to not pressed
}

void GameController::UpdatePlayer() {
    if (keyStates['w'] || keyStates['W']) player->MoveUp();
    if (keyStates['s'] || keyStates['S']) player->MoveDown();
    if (keyStates['a'] || keyStates['A']) player->MoveLeft();
    if (keyStates['d'] || keyStates['D']) player->MoveRight();
}

void GameController::Shoot(float targetX, float targetY) {
    if (player->GetShootTimer() >= player->GetShootCooldown()) {
        bullets.push_back(Bullet(player->GetX(), player->GetY(), targetX, targetY));
        player->SetShootTimer(0.0f);  // Reset timer after shooting
    }
}


void GameController::UpdateBullets() {
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




void GameController::CheckBulletZombieCollisions() {
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

void GameController::HandlePlayerZombieCollision() {
    float playerWidth = player->GetWidth();
    float playerHeight = player->GetHeight();

    for (auto& zombie : zombies) {
        float zombieWidth = zombie.GetWidth();
        float zombieHeight = zombie.GetHeight();

        // Check for collision
        if (Utility::CheckCollision(player->GetX(), player->GetY(), playerWidth, playerHeight,
                                    zombie.GetX(), zombie.GetY(), zombieWidth, zombieHeight)) {
            // Collision detected - push the player back

            float pushBackStrength = 0.05f; // Adjust this value as needed for the desired effect

            // Calculate push back direction
            float dx = player->GetX() - zombie.GetX();
            float dy = player->GetY() - zombie.GetY();
            float distance = std::sqrt(dx * dx + dy * dy);

            // Normalize the direction and apply push back strength
            if (distance != 0) { // To prevent division by zero
                player->SetX(player->GetX() + (dx / distance) * pushBackStrength);
                player->SetY(player->GetY() + (dy / distance) * pushBackStrength);
            }
        }
    }
}


void GameController::UpdateZombies() {
    float deltaTime = 1.0f / 60.0f; // Assuming 60 FPS

    for (auto& zombie : zombies) {
        zombie.Update(player->GetX(), player->GetY());
        zombie.UpdateCooldown(deltaTime); // Update cooldown timer
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


void GameController::SpawnZombie() {
    // Randomly place the new zombie at the edge of the screen
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    float x = dis(gen);
    float y = dis(gen);

    // Assuming zombies spawn at the edges
    if (std::abs(x) > std::abs(y)) {
        y = (x > 0) ? 1.0f : -1.0f;
    } else {
        x = (y > 0) ? 1.0f : -1.0f;
    }

    zombies.push_back(Zombie(x, y));
}
