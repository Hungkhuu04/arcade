#include <GL/glut.h>
#include <vector>
#include "zombie.h"
#include <cstdlib>  
#include <ctime>    
#include <cstring>  

// Player properties
float playerX = 400.0f; // Initial X position
float playerY = 300.0f; // Initial Y position
float playerSize = 50.0f; // Size of the player box

// Key state array
bool keyStates[256];

// Zombie properties
std::vector<Zombie> zombies;
void initializeZombies() {
    srand(static_cast<unsigned int>(time(0)));

    // Number of zombies to create
    const int numberOfZombies = 3;  

    for (int i = 0; i < numberOfZombies; ++i) {
        float randomX = static_cast<float>(rand() % 800); // Random X position between 0 and 799
        float randomY = static_cast<float>(rand() % 600); // Random Y position between 0 and 599

        zombies.push_back(Zombie(randomX, randomY));
    }
}

// Function prototypes
void update(int value);
void render(void);
void handleKeyboard(unsigned char key, int x, int y);
void handleKeyRelease(unsigned char key, int x, int y);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Zombie Survival Game");

    memset(keyStates, false, sizeof(keyStates));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
    glMatrixMode(GL_MODELVIEW);

    initializeZombies(); // Initialize zombies

    glutDisplayFunc(render);
    glutKeyboardFunc(handleKeyboard);
    glutKeyboardUpFunc(handleKeyRelease);
    glutTimerFunc(33, update, 0);

    glutMainLoop();

    return 0;
}

void update(int value) {
    float speed = 10.0f; // Adjust the speed as necessary

    if (keyStates['w']) playerY += speed;
    if (keyStates['s']) playerY -= speed;
    if (keyStates['a']) playerX -= speed;
    if (keyStates['d']) playerX += speed;

    // Boundary checks
    if (playerX < 0 + playerSize / 2) playerX = 0 + playerSize / 2;
    if (playerY < 0 + playerSize / 2) playerY = 0 + playerSize / 2;
    if (playerX > 800 - playerSize / 2) playerX = 800 - playerSize / 2;
    if (playerY > 600 - playerSize / 2) playerY = 600 - playerSize / 2;

    for (auto& zombie : zombies) {
        zombie.update();
    }

    glutPostRedisplay();
    glutTimerFunc(33, update, value);
}

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the player
    glLoadIdentity();
    glTranslatef(playerX, playerY, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
    glVertex2f(-playerSize / 2, -playerSize / 2);
    glVertex2f(playerSize / 2, -playerSize / 2);
    glVertex2f(playerSize / 2, playerSize / 2);
    glVertex2f(-playerSize / 2, playerSize / 2);
    glEnd();

    // Draw each zombie
    for (auto& zombie : zombies) {
        zombie.draw();
    }

    glutSwapBuffers();
}

void handleKeyboard(unsigned char key, int x, int y) {
    keyStates[key] = true; 
}

void handleKeyRelease(unsigned char key, int x, int y) {
    keyStates[key] = false;
}
