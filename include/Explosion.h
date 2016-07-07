#pragma once

#include "GameObject.h"


class Explosion : public GameObject
{
public:
    typedef enum {
        SMALL, LARGE
    } TypeExplosion;

    Explosion(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation, TypeExplosion tipo);
    virtual ~Explosion();

    virtual void Update(float deltaTime);
    static bool LoadImages();

    void Destroy();

    // Getters and Setters

    TypeExplosion GetTypeExplosion();
    void SetTypeExplosion(TypeExplosion typeExplosion);

protected:

    static sf::Image ExplosionImg;

    float size;
    TypeExplosion typeExplosion;

    int status;

};
