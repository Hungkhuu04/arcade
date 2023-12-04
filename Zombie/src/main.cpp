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

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    GameController::player->Render(); // Render the player

    // Render bullets
    for (auto& bullet : GameController::bullets) {
        bullet.Render();
    }

    // Render zombies
    for (auto& zombie : GameController::zombies) {
        zombie.Render();
    }

    glutSwapBuffers(); // Swap front and back buffers
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
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
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
