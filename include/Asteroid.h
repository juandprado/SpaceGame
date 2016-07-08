#pragma once

#include "GameObject.h"


class Asteroid : public GameObject
{
public:
    typedef enum {
        SMALL, LARGE
    } TypeAsteroid;

    Asteroid(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, TypeAsteroid tipo);
    virtual ~Asteroid();

    virtual void Update(float deltaTime);
    static bool LoadImages();

    void Damage();
    void Damage(float orientation, bool boom);
    void Destroy(bool boom);

    // Getters and Setters
    float GetHealth();
    void SetHealth(float health);

    float GetSize();
    void SetSize(float size);

    float GetSpeed();
    void SetSpeed(float speed);

    TypeAsteroid GetTypeAsteroid();
    void SetTypeAsteroid(TypeAsteroid typeAsteroid);

protected:

    static sf::Image asteroidImg;

    float health;
    float size;
    float speed;
    TypeAsteroid typeAsteroid;

    bool checkBoom;


};
