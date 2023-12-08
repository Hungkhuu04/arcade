#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    enum class BulletType {
        Player,
        BossZombie
    };
    Bullet(float startX, float startY, float targetX, float targetY, BulletType bulletType);

    //Rendering Stuff
    void Update();
    void Render();
    void MarkForDeletion() { markedForDeletion = true; }
    bool ShouldBeRemoved() const { return markedForDeletion; }
    bool IsOffScreen() const;

    //Getters
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetDamage() const { return damage; }
    BulletType GetType() const { return type; }
    
    //Setters
    void setDamage(float newDamage) { damage = newDamage; }
private:
    BulletType type;
    float x, y;
    float speed;
    float dirX, dirY;
    float width, height;
    float damage;
    bool markedForDeletion;
};

#endif
