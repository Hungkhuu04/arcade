#include "lib/Zombie.h"
#include "lib/Renderer.h"
#include <cmath>

// Constructor - Initialize member variables
Zombie::Zombie(float x, float y) 
    : x(x), y(y), 
      speed(0.005f), 
      health(20.0f), 
      width(0.1f), 
      height(0.1f), 
      damage(2.0f),
      damageCooldown(0.0f),        // Initialize cooldown timer to 0
      damageCooldownDuration(0.5f) // Set the duration of the cooldown
{}

void Zombie::Update(float playerX, float playerY) {
    // Simple AI to chase the player
    float dx = playerX - x;
    float dy = playerY - y;
    float length = std::sqrt(dx * dx + dy * dy);

    // Ensure that the zombie doesn't move if the player is exactly at the zombie's position
    if(length != 0) {
        x += speed * (dx / length);
        y += speed * (dy / length);
    }
    
    // Add any additional update logic here if needed
}

void Zombie::Render() {
    // Updated to use width and height
    Renderer::RenderZombie(x, y, width, height);
}

bool Zombie::IsAlive() const {
    return health > 0;
}

void Zombie::TakeDamage(float amount) {
    if (damageCooldown <= 0) {
        health -= amount;
        damageCooldown = damageCooldownDuration; // Reset cooldown
    }
}

void Zombie::UpdateCooldown(float deltaTime) {
    if (damageCooldown > 0) {
        damageCooldown -= deltaTime;
    }
}

bool Zombie::IsDamageable() const {
    return damageCooldown <= 0;
}

bool Zombie::IsDead() const {
    return health <= 0;
}


