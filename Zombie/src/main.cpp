#include <GL/glut.h>
#include "lib/Renderer.h"
#include "lib/GameController.h"
#include "lib/Utility.h"
#include <vector>
#include <cmath>
#include <iostream>

float cursorX = 0.0f, cursorY = 0.0f;

void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black
}
void renderStartingScreen() {
    // Set color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw placeholder for the starting screen
    // This is just a simple rectangle - replace this with actual rendering code
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

    // TODO: Render text "Press 'S' to Start" using a text rendering library like FreeType
}

void renderGameOverScreen() {
    // Set color to red
    glColor3f(1.0f, 0.0f, 0.0f);

    // Draw placeholder for the game over screen
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

    // TODO: Render text "Game Over. Press 'R' to Restart" using a text rendering library
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    switch (GameController::currentState) {
        case GameController::GameState::START:
            renderStartingScreen();
            break;
        case GameController::GameState::PLAYING:
            // Render the player
            GameController::player->Render();

            // Render each bullet
            for (auto& bullet : GameController::bullets) {
                bullet.Render();
            }

            // Render each zombie
            for (auto& zombie : GameController::zombies) {
                zombie.Render();
            }

            // Render the player's health
            Renderer::RenderHealth(GameController::player->GetHealth());

            break;
        case GameController::GameState::GAME_OVER:
            renderGameOverScreen();
            break;
    }

    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}

void mouseMotion(int x, int y) {
    cursorX = static_cast<float>(x) / 400.0f - 1.0f;
    cursorY = -static_cast<float>(y) / 300.0f + 1.0f;
}

// Timer callback to update game state
void timer(int value) {
    GameController::UpdatePlayer(); // Update player state based on key states
    GameController::Shoot(cursorX, cursorY); // Player shoots towards cursor position
    GameController::UpdateBullets(); // Update bullets
    GameController::UpdateZombies(); // Update zombies
    GameController::CheckBulletZombieCollisions(); // Check for bullet-zombie collisions
    GameController::HandlePlayerZombieCollision(); // Handle player-zombie collisions

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // 60 FPS
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Zombie Survival Game");

    initOpenGL();

    GameController::Initialize(); // Initialize the game controller and player
    glutDisplayFunc(display);
    glutKeyboardFunc(GameController::KeyboardHandler);
    glutKeyboardUpFunc(GameController::KeyboardUpHandler);
    glutPassiveMotionFunc(mouseMotion);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
