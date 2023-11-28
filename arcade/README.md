# Zombie Survival Game

## Introduction
This project is a simple, arcade-style 2D game developed in C++ using OpenGL. In this game, players navigate a character through a field of zombies, avoiding them to survive as long as possible.

## How to Build:

### Prerequisites:
C++ Compiler (GCC MinGW or MSVC for Windows)
OpenGL and GLUT libraries installed

### Building the Project:
1. Open Command Prompt or PowerShell in the project directory.
2. Run the build command (adjust paths to libraries if needed):
- g++ -o ZombieGame.exe main.cpp Zombie.cpp -lglut32 -lopengl32 -lglu32

### After building the project:

An executable named ZombieGame will be created. Run this executable to start the game:
- ZombieGame.exe

## Code Organization
- arcade.cpp: Contains the main game loop and initialization code.
- zombie.cpp and zombie.h: Define the Zombie class, handling the behavior and rendering of zombies.


