#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    Entity(float x, float y, float health);

    virtual void Update() = 0;  // Pure virtual function for update logic
    virtual void Render() = 0;  // Pure virtual function for render logic
    void TakeDamage(float amount);
    bool IsAlive() const;

    // Getters for position
    float GetX() const;
    float GetY() const;

    // Setters for position
    void SetX(float x);
    void SetY(float y);

protected:
    float x, y;     // Position
    float health;   // Health
};

#endif // ENTITY_H
