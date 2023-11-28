#pragma once
// Zombie.h
#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie {
public:
    Zombie(float x, float y);
    void update();
    void draw();

private:
    float x, y;
    float speed;
};

#endif

