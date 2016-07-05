#pragma once

#include "GameObject.h"


class Asteroid : public GameObject
{
public:

    Asteroid(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, int tipo);
    virtual ~Asteroid();

    virtual void Update(float deltaTime);

    static bool LoadImages();

    void Damage();
    void Destroy();

protected:

    float health;
    float size;
    float speed;
    int typeAsteroid;

    static sf::Image asteroidImg;
};
