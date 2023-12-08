#ifndef RENDERER_H
#define RENDERER_H
#include "Bullet.h"
#include "GameController.h"
#include <array>

class Renderer {
public:
    static void RenderPlayer(float x, float y);
    static void RenderZombie(float x, float y, float width, float height);
    static void RenderBullet(float x, float y, float width, float height, Bullet::BulletType bulletType);
    static void RenderHealth(float health);
    static void RenderWave(int wave);
    static void RenderTimer(float timer);
    static void RenderScore(int score);
    static void RenderLeaderboard(const std::array<int, GameController::LEADERBOARD_SIZE>& leaderboard);
    static void ERenderLeaderboard(const std::array<int, GameController::LEADERBOARD_SIZE>& leaderboard);

private:
};

#endif
