# Zombie Game
Description
This project is a 2D zombie survival game developed in C++, utilizing OpenGL for rendering. Players navigate through a field of zombies, aiming to survive as long as possible.

Getting Started
Prerequisites
To compile and run this game, you need to have the following installed:

A C++ compiler (MinGW or Microsoft Visual C++ for Windows)
OpenGL libraries
GLUT (OpenGL Utility Toolkit)
Installation
Linux/macOS
Install GCC (if not already installed):

macOS: Install Xcode from the App Store.
Linux: Use your distribution's package manager. For example, on Ubuntu: sudo apt-get install build-essential.
Install OpenGL and GLUT:

They are usually pre-installed on macOS.
On Linux: sudo apt-get install freeglut3 freeglut3-dev.
Windows
Install MinGW or Visual C++ Build Tools.
Download and set up the GLUT library:
Follow instructions from OpenGL's website to install GLUT.
Compilation
Open a terminal or command prompt.
Navigate to the directory containing the game's source files.
Use the following command to compile:
bash
Copy code
g++ -o ZombieGame main.cpp Zombie.cpp -lglut -lGL -lGLU
Replace main.cpp and Zombie.cpp with the actual names of your source files.
Running the Game
After compilation, run the executable:
Windows: ZombieGame.exe.
Linux/macOS: ./ZombieGame.