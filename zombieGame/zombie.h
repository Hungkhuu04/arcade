#pragma once
// Zombie.h
#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie {
public:
    Zombie(float x, float y);
    void update(int playerX, int playerY);
    void draw();

private:
    float x, y, speed;
};

#endif

