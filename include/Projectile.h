#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:

    Projectile(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation);
    virtual ~Projectile();

    virtual void Update(float deltaTime);

    static bool LoadImages();

protected:

    float speed;
    float lifeTime;

    static sf::Image projectileImg;
};
