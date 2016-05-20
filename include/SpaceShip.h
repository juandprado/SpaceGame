#pragma once

#include "GameObject.h"

class SpaceShip : public GameObject
{
public:

    SpaceShip(GameManager * ownerGame, sf::Vector2f initialPosition);
    virtual ~SpaceShip();

    void SetRotationDirection(float direction);

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

    static bool LoadImages();

private:

    static sf::Image spaceShipImg;

    float rotationDir;
    float weaponTimer;
};
