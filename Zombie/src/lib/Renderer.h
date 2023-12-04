#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
    static void RenderPlayer(float x, float y);
    static void RenderZombie(float x, float y, float width, float height);
    static void RenderBullet(float x, float y, float width, float height);

private:
    static void DrawCircle(float x, float y, float radius);
};

#endif // RENDERER_H
