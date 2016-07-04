#pragma once

#include "GameObject.h"

class Asteroid : public GameObject
{
public:

    Asteroid(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation);
    virtual ~Asteroid();

    virtual void Update(float deltaTime);

    static bool LoadImages();

protected:

    float health;
    float size;
    float speed;
    float lifeTime;

    static sf::Image asteroidImg;
};
