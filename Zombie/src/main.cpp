#include <GL/glut.h>
#include "lib/Renderer.h"
#include "lib/GameController.h"
#include "lib/Utility.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "lib/stb_image.h"

float cursorX = 0.0f, cursorY = 0.0f;
GLuint backdropTexture;
GLuint gameOverScreen;
GLuint startScreen;

GLuint loadTexture(const char* filename);
void renderBackdrop(GLuint texture);

//Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    backdropTexture = loadTexture("Zombie/src/assets/GameBackgroud.png");
    gameOverScreen = loadTexture("Zombie/src/assets/EndScreen.png");
    startScreen = loadTexture("Zombie/src/assets/StartingScreen.png");
}

//Render starting screen elements
void renderStartingScreen() {
    glColor3f(1.0f, 1.0f, 1.0f);

}

//Render game over screen elements
void renderGameOverScreen() {
    glColor3f(1.0f, 0.0f, 1.0f);

    Renderer::RenderScore(GameController::GetScore());
}

//Display function to render the game scenes based on current game state
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    switch (GameController::currentState) {
        case GameController::GameState::START:
            renderBackdrop(startScreen);
            renderStartingScreen();
            Renderer::RenderLeaderboard(GameController::leaderboard);
            break;
        case GameController::GameState::PLAYING:
            renderBackdrop(backdropTexture);
            GameController::player->Render();

            for (auto& bullet : GameController::bullets) {
                bullet.Render();
            }

            for (auto& zombie : GameController::zombies) {
                zombie.Render();
            }

            for (auto& bossZombie : GameController::bossZombies) {
                bossZombie.Render();
            }

                for (auto& bullet : GameController::bossZombieBullets) {
                bullet.Render();
            }

            Renderer::RenderHealth(GameController::player->GetHealth());

            Renderer::RenderWave(GameController::GetWave());

            Renderer::RenderTimer(GameController::GetTimer());

            break;
        case GameController::GameState::GAME_OVER:
            renderBackdrop(gameOverScreen);
            renderGameOverScreen();
            Renderer::ERenderLeaderboard(GameController::leaderboard);
            break;
    }

    glutSwapBuffers(); 
}
//Tracks the motion mouse for the cursor.
void mouseMotion(int x, int y) {
    cursorX = static_cast<float>(x) / 514.0f - 1.0f;
    cursorY = -static_cast<float>(y) / 384.0f + 1.0f;
}

//A timer function so that other elements of the game can be upodated.
void timer(int value) {
    GameController::UpdatePlayer();
    GameController::Shoot(cursorX, cursorY);
    GameController::UpdateBullets();
    GameController::UpdateZombies();
    GameController::CheckBulletZombieCollisions();
    GameController::HandlePlayerZombieCollision();
    GameController::CheckBossZombieBulletPlayerCollision();


    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

//Main function to set up OpenGL and enter the main loop
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Zombie Survival Game");

    initOpenGL();

    GameController::Initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(GameController::KeyboardHandler);
    glutKeyboardUpFunc(GameController::KeyboardUpHandler);
    glutPassiveMotionFunc(mouseMotion);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}

//Function to load texture from file.
GLuint loadTexture(const char* filename) {
    stbi_set_flip_vertically_on_load(true); 
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return texture;
}

//Renders the backdrop based on a given texture.
void renderBackdrop(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f); 
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, -1.0f); 
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f,  1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
