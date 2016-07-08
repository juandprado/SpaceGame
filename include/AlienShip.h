#pragma once

#include "GameObject.h"
#include "Projectile.h"

class AlienShip : public GameObject
{
public:

    AlienShip(GameManager * ownerGame, sf::Vector2f initialPosition, float initialOrientation);
    virtual ~AlienShip();

    void EvalProjectile(Projectile::TypeProjectile typeProjectile);

    virtual void Update(float deltaTime);
//    virtual void Draw(sf::RenderWindow & render);

    static bool LoadImages();

    void Accelerate(float deltaTime, float mode);

    float GetSpeed();
    void SetSpeed(float speed);

    float GetAcceleration();
    void SetAcceleration(float acceleration);
    void Destroy(bool boom);

private:

    static sf::Image alienShipImg;
    
    float speed; //Velocidad de la nave
    float acceleration; // Aceleracion de la nave
    float alienShootTimer; // Tiempo para que despara
};
