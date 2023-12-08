#include "lib/Renderer.h"
#include "lib/Bullet.h"
#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <string>

//  Render the player on the screen, as square for testing
void Renderer::RenderPlayer(float x, float y) {
    glColor3f(0.0f, 1.0f, 0.0f);
    glRectf(x - 0.05f, y - 0.05f, x + 0.05f, y + 0.05f);
}

// Render zombie on the screen, as square for testing
void Renderer::RenderZombie(float x, float y, float width, float height) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(x - width / 2.0f, y - height / 2.0f, x + width / 2.0f, y + height / 2.0f);
}

// Render a bullet on the screen for player and BossZombie
void Renderer::RenderBullet(float x, float y, float width, float height, Bullet::BulletType bulletType) {
    if (bulletType == Bullet::BulletType::Player) {
        glColor3f(1.0f, 0.0f, 0.0f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glRectf(x - width / 2.0f, y - height / 2.0f, x + width / 2.0f, y + height / 2.0f);
}

// Render the player's health on the screen
void Renderer::RenderHealth(float health) {
    std::string healthText = "Health: " + std::to_string(static_cast<int>(health));
    float scaleX = 0.0005f;
    float scaleY = 0.0005f;
    float offset = 1.0f;
    glPushMatrix();
    glTranslatef(-1.0f, 0.9f, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);

    glColor3f(1.0f, 0.0f, 0.0f);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            glPushMatrix();
            glTranslatef(i * offset, j * offset, 0);
            for (char c : healthText) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
            }
            glPopMatrix();
        }
    }

    glPopMatrix();
}

// Render the player's health on the screen
void Renderer::RenderWave(int wave) {
    std::string waveText = "Wave: " + std::to_string(wave);
    float scaleX = 0.0005f;
    float scaleY = 0.0005f;
    float offset = 1.0f;

    glPushMatrix();
    glTranslatef(-0.1f, 0.9f, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            glPushMatrix();
            glTranslatef(i * offset, j * offset, 0);
            for (char c : waveText) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
            }
            glPopMatrix();
        }
    }

    glPopMatrix();
}

// Render the elapsed time on the screen
void Renderer::RenderTimer(float timer) {
    int minutes = static_cast<int>(timer) / 60;
    int seconds = static_cast<int>(timer) % 60;
    std::string timerText = "Time: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
    float scaleX = 0.0005f;
    float scaleY = 0.0005f;
    float offset = 1.0f;

    glPushMatrix();
    glTranslatef(0.65f, 0.9f, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);

    glColor3f(0.0f, 1.0f, 0.0f);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            glPushMatrix();
            glTranslatef(i * offset, j * offset, 0);
            for (char c : timerText) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
            }
            glPopMatrix();
        }
    }

    glPopMatrix();
}

void Renderer::RenderScore(int score) {
    std::string scoreText = std::to_string(score);
    float scaleX = 0.0008f;
    float scaleY = 0.0008f;
    float offset = 1.0f;

    glPushMatrix();
    glTranslatef(0.55f, -0.44f, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);

    glColor3f(1.0f, 0.8f, 0.0f);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            glPushMatrix();
            glTranslatef(i * offset, j * offset, 0);
            for (char c : scoreText) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
            }
            glPopMatrix();
        }
    }

    glPopMatrix();
}

// Render the leaderboard on the screen
void Renderer::RenderLeaderboard(const std::array<int, GameController::LEADERBOARD_SIZE>& leaderboard) {
    // Adjust these values based on your screen layout and preferences
    float scaleX = 0.0005f;
    float scaleY = 0.0005f;
    float offset = 1.0f;  // Shadow/Outline offset
    float startX = -0.9f; // Starting X position of the leaderboard
    float startY = 0.8f;  // Starting Y position of the leaderboard

    // Set color for the leaderboard text
    glColor3f(1.0f, 1.0f, 1.0f);  // White color

    // Render the title "Leaderboard" with shadow effect
    glPushMatrix();
    glTranslatef(startX, startY, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            glPushMatrix();
            glTranslatef(i * offset, j * offset, 0);
            for (char c : "Leaderboard") {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
            }
            glPopMatrix();
        }
    }
    glPopMatrix();

    // Render each leaderboard entry with shadow effect
    for (size_t i = 0; i < leaderboard.size(); ++i) {
        glPushMatrix();
        glTranslatef(startX, startY - (i + 1) * 0.07f, 0.0f); // Adjust Y position for each line
        glScalef(scaleX, scaleY, 1.0f);

        std::string scoreText = std::to_string(i + 1) + ". " + std::to_string(leaderboard[i]);
        for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
                glPushMatrix();
                glTranslatef(k * offset, l * offset, 0);
                for (char c : scoreText) {
                    glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
                }
                glPopMatrix();
            }
        }
        glPopMatrix();
    }
}

void Renderer::ERenderLeaderboard(const std::array<int, GameController::LEADERBOARD_SIZE>& leaderboard) {
    // Adjust these values based on your screen layout and preferences
    float scaleX = 0.0005f;
    float scaleY = 0.0005f;
    float offset = 1.0f;  // Shadow/Outline offset
    float startX = -0.9f; // Starting X position of the leaderboard
    float startY = 0.5f;  // Starting Y position of the leaderboard

    // Set color for the leaderboard text
    glColor3f(1.0f, 1.0f, 1.0f);  // White color

    // Render the title "Leaderboard" with shadow effect
    glPushMatrix();
    glTranslatef(startX, startY, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            glPushMatrix();
            glTranslatef(i * offset, j * offset, 0);
            for (char c : "Leaderboard") {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
            }
            glPopMatrix();
        }
    }
    glPopMatrix();

    // Render each leaderboard entry with shadow effect
    for (size_t i = 0; i < leaderboard.size(); ++i) {
        glPushMatrix();
        glTranslatef(startX, startY - (i + 1) * 0.07f, 0.0f); // Adjust Y position for each line
        glScalef(scaleX, scaleY, 1.0f);

        std::string scoreText = std::to_string(i + 1) + ". " + std::to_string(leaderboard[i]);
        for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
                glPushMatrix();
                glTranslatef(k * offset, l * offset, 0);
                for (char c : scoreText) {
                    glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
                }
                glPopMatrix();
            }
        }
        glPopMatrix();
    }
}
