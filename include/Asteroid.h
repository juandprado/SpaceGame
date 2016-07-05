#pragma once

#include "GameObject.h"
#include <stdlib.h>

class Asteroid : public GameObject
{
public:

    Asteroid(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, int tipo);
    virtual ~Asteroid();

    virtual void Update(float deltaTime);

    static bool LoadImages();

    void Destroy();

    void Damage();

protected:

    float health;
    float size;
    float speed;
    int type;

    static sf::Image asteroidImg;
};
