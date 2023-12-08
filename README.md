# Zombie Survival Game

## Introduction
This project is a simple, arcade-style 2D game developed in C++ using OpenGL. In this game, players navigate a character through a field of zombies, avoiding them to survive as long as possible.

## How to Build:

### Prerequisites:
C++ Compiler (GCC MinGW or MSVC for Windows)
OpenGL and GLUT libraries installed

### Building the Project:
1. Open Terminal.
2. In the desired folder, download the zipped file
3. Cd into arcade-master aka repository folder.
4. Run the build command: Type make
<<<<<<< HEAD

=======
      
>>>>>>> master
### After building the project:
An executable named ZombieGame will be created. Run this executable to start the game:
- ./zombie_game

## Code Organization:
Source Folder:
- Assets:
   - Zombie.png
   - Player.png
   - BossZombie.png
   - Background.png
- Data:
   - Leaderboard
- Lib:
   - Renderer.h
   - GameController.h
   - Player.h
   - Bullet.h
   - Zombie.h
   - Utility.h
   - bossZombie.h
   - stb.h      
- main.cpp: Contains the main game loop and initialization code.
- Renderer.cpp: Contains the render functions for displays like score, time, health and leaderboard.
- GameController.cpp: Contains the main code the game such as input handling, game states, updating leaderboard, collision checks.
- Player.cpp: Contains the player code to move, shoot, take damage and render.
- Bullet.cpp: Contains the bullet code to move, inflict damage and render.
- Zombie.cpp: Contains the player code to move, inflict damage, take damage and render. Parent Class functions for BossZombie.
- Utility.cpp: Contains the function to check for Collisions.
- bossZombie.cpp: Contains the bossZombie code to follow basic code from zombie and shoot bullets.
- stb.cpp: Contains define functions for stb.h to render sprites.

## Instructions:
- Use WASD to move the block around in their respective directions.
- Use the mouse to shoot bullets.
