#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:

    Projectile(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation);
    virtual ~Projectile();

    virtual void Update(float deltaTime);

    static bool LoadImages();

    // Getters and Setters
    float GetSpeed();
    void SetSpeed(float speed);

    float GetLifeTime();
    void SetLifeTime(float lifeTime);

protected:

    static sf::Image projectileImg;

    float speed; // Variable que contiene la velocidad de el proyectil
    float lifeTime; // Vida de el proyectil
};
