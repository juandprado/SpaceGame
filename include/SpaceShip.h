#pragma once

#include "GameObject.h"

class SpaceShip : public GameObject
{
public:

    SpaceShip(GameManager * ownerGame, sf::Vector2f initialPosition);
    virtual ~SpaceShip();

    void SetRotationDirection(float direction);
    void EvalProjectile();

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

    static bool LoadImages();
    float GetSpaceWidth();
    float GetSpaceHeight();
    sf::Vector2f GetSpacePosition();

private:

    static sf::Image spaceShipImg;



    float rotationDir; // Direccion de rotacion de la nave
    float weaponTimer; // Variable encargada de almacenar el tiempo minimo entre cada disparo
};
