# Zombie Survival Game

## Introduction
This project is a simple, arcade-style 2D game developed in C++ using OpenGL. In this game, players navigate a character through a field of zombies, avoiding them to survive as long as possible.

## How to Build:

### Prerequisites:
C++ Compiler (GCC MinGW or MSVC for Windows)
OpenGL and GLUT libraries installed

### Building the Project:
1. Open Terminal.
2. In the desired folder, run: git clone git@github.com:Hungkhuu04/arcade.git
3. Cd into arcade (cd arcade) aka repository folder.
4. Run the build command (adjust paths to libraries if needed):
   - On CSIL computers:

      g++ zombieGame/arcade.cpp zombieGame/zombie.cpp -o zombie_game -lGL -lGLU -lglut

    - On Local Windows computers with C++ Complier Installed(MinGW or MSVC):

      g++ -m32 -o zombie_game zombieGame/arcade.cpp zombieGame/zombie.cpp -IDependencies/freeglut/include -LDependencies/freeglut/lib/Win32 -lfreeglut -lopengl32 -lglu32
      
### After building the project:
An executable named ZombieGame will be created. Run this executable to start the game:
- ./zombie_game

## Code Organization:
- arcade.cpp: Contains the main game loop and initialization code.
- zombie.cpp and zombie.h: Define the Zombie class, handling the behavior and rendering of zombies.

## Instructions:
- Use WASD to move the block around in their respective directions.
