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

    float speed; // Variable que contiene la velocidad de el proyectil
    float lifeTime; // Vida de el proyectil

    static sf::Image projectileImg;
};
