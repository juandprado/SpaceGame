#pragma once

#include <SFML/Graphics.hpp>

class GameManager;


class GameObject
{

public:

    GameObject(GameManager * ownerGame);
    virtual ~GameObject();

    void Destroy();

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

protected:

    GameManager * gameManager;

    sf::Sprite sprite;
    sf::Vector2f position;
    float orientation;
    float spriteRotation;

};
