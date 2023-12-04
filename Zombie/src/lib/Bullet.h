#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet(float startX, float startY, float targetX, float targetY);

    void Update();  // Update the bullet's position
    void Render();  // Render the bullet
    bool IsOffScreen() const;  // Check if the bullet is off the screen
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetDamage() const { return damage; }
    void MarkForDeletion() { markedForDeletion = true; }
    bool ShouldBeRemoved() const { return markedForDeletion; }
private:
    float x, y;     // Current position
    float speed;    // Speed of the bullet
    float dirX, dirY; // Direction vector
    float width, height; // Dimensions of the bullet
    float damage;   // Damage the bullet does
    bool markedForDeletion; // Flag to mark the bullet for deletion
};

#endif // BULLET_H
